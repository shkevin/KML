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

#include "Utils.h"  // Float comparison

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
        void IStreamingHistogram<T>::decayCounts()
        {
            if (DecayType::WINDOW == m_decay)
            {
                if (this->m_totalCount > this->m_windowSize)
                {
                    size_t l_delete = m_window->front();
                    m_window->pop_front();
                    if (m_bins[l_delete]->m_count > 0)
                    {
                        m_bins[l_delete]->m_count--;
                    }

                    // Remove the bin when it's no longer needed.
                    if (size() > getNumBins())
                    {
                        if (m_bins[l_delete]->m_count == 0)
                        {
                            m_bins.erase(m_bins.begin() + l_delete);
                        }
                    }

                    m_totalCount--;
                }
            }
        }

        template<typename T>
        std::vector<double> IStreamingHistogram<T>::pdf(const bool& normalize,
                                                        const bool& density) const
        {
            std::vector<double> l_normalized(size(), 0.0);
            double l_normalizer = getTotalCount();
            if (density)
            {
                for (size_t i = 0; i < m_bins.size(); i++)
                {
                    double l_width = m_bins[i]->m_right - m_bins[i]->m_left;
                    if (l_width <= 0) l_width = 1.0;  // Single item in bin.
                    l_normalized[i] = (m_bins[i]->m_count / (l_normalizer * l_width));
                }
            }
            else
            {
                if (!normalize) l_normalizer = 1.0;  // Just get counts.
                for (size_t i = 0; i < m_bins.size(); i++)
                {
                    l_normalized[i] = m_bins[i]->m_count / l_normalizer;
                }
            }

            return l_normalized;
        }

        template<typename T>
        std::vector<double> IStreamingHistogram<T>::cdf(const bool& normalize) const
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

            // Find the first bin smaller than the quantile in the cdf values.
            auto it = std::lower_bound(l_cdf.begin(), l_cdf.end(), qtile);
            if (it == l_cdf.end())
            {
                it = (l_cdf.rbegin() + 1).base();
            }
            else if (it != l_cdf.begin() && *it > qtile)
            {
                --it;
            }
            size_t l_index = (it - l_cdf.begin());

            // If exactly equal to left bin, return that quantile.
            if (Utils::essentiallyEqual(qtile, l_cdf[l_index]))
            {
                return this->m_bins[l_index]->m_left;
            }
            else
            {
                double l_p = 0.0;
                double l_width = 0.0;
                if (l_index >= l_cdf.size())
                {
                    l_index = l_cdf.size() - 1;
                    l_p = 1.0;
                }
                else
                {
                    l_p = l_cdf[l_index + 1] - l_cdf[l_index];
                    l_width = m_bins[l_index]->m_right - m_bins[l_index]->m_left;
                }

                // Otherwise, attempt to interpolate and approximate quantile.
                double l_totalCount = getTotalCount();
                if (l_width == 0) l_width = 1.0 / static_cast<double>(m_numBins);
                double l_quantile = m_bins[l_index]->m_left;

                return l_quantile + ((l_width * l_p * l_totalCount) / m_bins[l_index]->m_count);
            }
        }

        template<typename T>
        void IStreamingHistogram<T>::add(const T& item)
        {
            IBin<T>* l_bin = new IBin<T>(item, item, 1);
            // Get the bin index where the new bin should go.
            size_t l_index = binSearch(*l_bin);

            // Histogram is empty, just insert.
            if (0 == getTotalCount())
            {
                this->m_bins.push_back(l_bin);
            }
            else
            {
                // Item is past right-most bin. just push to end.
                if (l_index == getCurrentNumBins())
                {
                    m_bins.push_back(l_bin);
                }
                else
                {
                    // Increment the bin counter if item is at index bin.
                    if (item >= m_bins[l_index]->m_left)
                    {
                        m_bins[l_index]->m_count++;
                    }
                    else
                    {
                        // Found where to insert, insert at index.
                        m_bins.insert(m_bins.begin() + l_index, l_bin);
                    }
                }
            }

            // Update window index and counts.
            this->m_historyCount++;
            m_totalCount++;
            m_window->push_back(l_index);
            decayCounts();  // Call decay before potentially merging.
        }

        template<typename T>
        std::vector<size_t> IStreamingHistogram<T>::binCounts() const
        {
            size_t l_total = 0;
            std::vector<size_t> l_counts(m_bins.size(), 0);
            for (size_t i = 0; i < m_bins.size(); i++)
            {
                l_counts[i] = m_bins[i]->m_count;
                l_total += l_counts[i];
            }

            // Just a sanity check.
            if (l_total != m_totalCount)
            {
                throw std::runtime_error("Counts are somehow out of sync!");
            }

            return l_counts;
        }

        template<typename T>
        std::map<std::pair<double, double>, size_t> IStreamingHistogram<T>::report()
        {
            std::map<std::pair<double, double>, size_t> l_report;
            for (auto i = m_bins.begin(); i < m_bins.end(); i++)
            {
                l_report[std::make_pair((*i)->m_left, (*i)->m_right)] = (*i)->m_count;
            }

            return l_report;
        }

        template<typename T>
        double IStreamingHistogram<T>::coverage(IBin<T> lhs, IBin<T> rhs)
        {
            if (lhs.m_left == rhs.m_left)
            {
                return static_cast<double>(lhs.m_left <= rhs.m_left <= lhs.m_right);
            }

            double l_largest = std::min(lhs.m_right, rhs.m_right);
            double l_smallest = std::max(lhs.m_left, rhs.m_left);
            return std::max(0.0, l_largest - l_smallest) / (rhs.m_right - rhs.m_left);
        }

        template<typename T>
        void IStreamingHistogram<T>::reset()
        {
            m_bins.clear();
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
            return !empty();
        }

        template<typename T>
        size_t IStreamingHistogram<T>::size() const
        {
            return m_bins.size();
        }

        template<typename T>
        size_t IStreamingHistogram<T>::getTotalCount() const
        {
            return m_totalCount;
        }

        template<typename T>
        std::deque<size_t>* IStreamingHistogram<T>::getWindow() const
        {
            return m_window;
        }

        template<typename T>
        size_t IStreamingHistogram<T>::getCurrentNumBins() const
        {
            return m_bins.size();
        }

        template<typename T>
        IBin<T>* IStreamingHistogram<T>::getBin(size_t index) const
        {
            size_t currentBinCount = getCurrentNumBins();
            if (index > currentBinCount)
            {
                throw std::runtime_error("Can't get bin outside of histogram!");
            }

            return m_bins[index];
        }

        template<typename T>
        void IStreamingHistogram<T>::mergeBins(const size_t& lhs, const size_t& rhs)
        {
            // Get next right bin to merge into left.
            IBin<T> l_toMerge = *m_bins[rhs];
            m_bins.erase(m_bins.begin() + rhs);
            *m_bins[lhs] += l_toMerge;
        }

        template<typename T>
        size_t IStreamingHistogram<T>::getNumBins() const
        {
            return m_numBins;
        }

        template<typename T>
        DecayType IStreamingHistogram<T>::getDecayType() const
        {
            return m_decay;
        }
    }  // namespace DataStructures
}  // namespace KML
