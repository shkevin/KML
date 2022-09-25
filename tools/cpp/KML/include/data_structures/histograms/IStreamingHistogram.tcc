/*!
 * @file IStreamingHistogram.tcc
 * @brief Contains the templated implementation for the abstract streaming histogram class.
 *
 * @References: https://jmlr.csail.mit.edu/papers/volume11/ben-haim10a/ben-haim10a.pdf
 *              https://arxiv.org/pdf/1712.02476.pdf
 *              https://randorithms.com/2022/01/31/streaming-histograms.html
 */
#include <algorithm>  // std::min
#include <iostream>   // For printing
#include <numeric>    // std::partial_sum
#include <stdexcept>  // Throwing errors

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        IStreamingHistogram<T>::IStreamingHistogram(const size_t& numBins, const size_t& windowSize,
                                                    const DecayType& decay)
            : IDataStructure<T>(windowSize), m_numBins(numBins), m_decay(decay)
        {
            if (decay == DecayType::WINDOW)
            {
                m_window = new std::deque<size_t>(this->m_windowSize);
            }
        }

        template<typename T>
        std::ostream& operator<<(std::ostream& os, const IStreamingHistogram<T>& hist)
        {
            os << "(";
            for (int i = 0; i < hist.m_bins.size(); ++i)
            {
                os << *hist.m_bins[i];
                if (i != hist.m_bins.size() - 1) os << ", ";
            }
            os << ")\n";
            return os;
        }

        template<typename T>
        void IStreamingHistogram<T>::updateNormalizer()
        {
            if (DecayType::WINDOW == m_decay)
            {
                if (m_normalizer < this->m_windowSize) m_normalizer++;
            }
            else
                m_normalizer++;  // Option for none.
        }

        template<typename T>
        void IStreamingHistogram<T>::decayCounts()
        {
            if (DecayType::WINDOW == m_decay)
            {
                if (this->m_historyCount > this->m_windowSize)
                {
                    size_t l_delete = m_window->front();
                    m_window->pop_front();
                    if (m_bins[l_delete]->m_count > 0)
                    {
                        m_bins[l_delete]->m_count--;

                        // Remove the bin when it's no longer needed.
                        if (m_bins[l_delete]->m_count == 0)
                        {
                            m_bins.erase(m_bins.begin() + l_delete);
                        }
                    }
                }
            }
        }

        template<typename T>
        std::vector<double> IStreamingHistogram<T>::pdf(const bool normalize,
                                                        const bool density) const
        {
            std::vector<double> l_normalized(m_numBins, 0.0);
            double l_normalizer = m_normalizer;
            if (density)
            {
                double l_min = 1.0 / (double)m_numBins;
                for (size_t i = 0; i < m_numBins; i++)
                {
                    double l_width = m_bins[i]->m_left - m_bins[i]->m_right;
                    if (l_width == 0) l_width = l_min;
                    l_normalized[i] =
                        (l_normalizer / this->m_windowSize) * (m_bins[i]->m_count * l_width);
                }
            }
            else
            {
                if (!normalize) l_normalizer = 1.0;
                for (size_t i = 0; i < m_bins.size(); i++)
                {
                    l_normalized[i] = m_bins[i]->m_count / l_normalizer;
                }
            }

            return l_normalized;
        }

        template<typename T>
        std::vector<double> IStreamingHistogram<T>::cdf(const bool normalize) const
        {
            std::vector<T> l_counts = pdf(normalize, false);
            std::vector<T> l_cdf(l_counts.size());
            std::partial_sum(l_counts.begin(), l_counts.end(), l_cdf.begin());
            return l_cdf;
        }

        template<typename T>
        size_t IStreamingHistogram<T>::binSearch(const IBin<T>& bin) const
        {
            // Binary search to find insert index for bin.
            size_t l_low = 0;
            size_t l_high = m_bins.size();
            size_t l_index = (l_low + l_high) / 2;

            while (l_low < l_high)
            {
                if (*m_bins[l_index] < bin)
                    l_low = l_index + 1;
                else
                    l_high = l_index;
                l_index = (l_low + l_high) / 2;
            }

            return l_index;
        }

        template<typename T>
        T IStreamingHistogram<T>::quantile(const double& qtile) const
        {
            if ((qtile < 0) || (qtile > 1))
            {
                throw std::runtime_error("Percentile must be in closed range [0, 1]!");
            }

            std::vector<double> l_cdf = cdf();
            std::vector<double>::iterator l_lower;
            l_lower = std::lower_bound(l_cdf.begin(), l_cdf.end(), qtile);

            size_t l_index = (l_lower - l_cdf.begin());
            double l_p = 0.0;
            if (l_index >= l_cdf.size())
            {
                l_index = l_cdf.size() - 1;
                l_p = 1.0;
            }
            else
                l_p = l_cdf[l_index + 1] - l_cdf[l_index];

            double l_totalCount = 0.0;
            for (auto it = m_bins.begin(); it != m_bins.end(); it++)
            {
                l_totalCount += (*it)->m_count;
            }

            double l_width = m_bins[l_index]->m_right - m_bins[l_index]->m_left;
            if (l_width == 0) l_width = 1.0 / (double)m_numBins;
            double l_quantile = m_bins[l_index]->m_left;
            return l_quantile + ((l_width * l_p * l_totalCount) / m_bins[l_index]->m_count);
        }

        template<typename T>
        std::vector<size_t> IStreamingHistogram<T>::binCounts() const
        {
            std::vector<size_t> l_counts(m_bins.size(), 0);
            for (size_t i = 0; i < m_bins.size(); i++)
            {
                l_counts[i] = m_bins[i]->m_count;
            }
            return l_counts;
        }

        template<typename T>
        void IStreamingHistogram<T>::reset()
        {
            m_bins.clear();
            m_normalizer = 0;
            this->m_historyCount = 0;
            if (nullptr != m_window) m_window->clear();
        }

        template<typename T>
        bool IStreamingHistogram<T>::empty() const
        {
            return m_bins.size() == 0;
        }

        template<typename T>
        bool IStreamingHistogram<T>::full() const
        {
            return !this->empty();
        }

        template<typename T>
        size_t IStreamingHistogram<T>::size() const
        {
            return m_bins.size();
        }
    }  // namespace DataStructures
}  // namespace KML
