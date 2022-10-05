/*!
 * @file  StreamingEntropy.cc
 * @brief Contains the implementation of the StreamingEntropy calculation.
 *
 * This implementation currently uses a variable width bin histogram. The 
 * entropy calculation would most likely be more accurate if this was 
 * changed.
 *
 * This class contains the Streaming Entropy calculation adapted from:
 * https://arxiv.org/pdf/1403.6348.pdf
 */
#include "StreamingEntropy.h"

#include <cmath>

#include "Utils.h"

namespace KML
{
    namespace Statistics
    {
        StreamingEntropy::StreamingEntropy(const size_t& windowSize, const size_t& numBins)
            : IStreamingStatistic(windowSize)
        {
            // Just apply the sturges rule to calculate number of bins.
            size_t l_bins = numBins;
            if (0 == numBins)
            {
                l_bins = std::max<size_t>(numBins, std::ceil(std::log2(windowSize)) + 1);
            }

            m_histogram = new StreamingHistogram<double>(l_bins, windowSize);
        }

        void StreamingEntropy::update(const double& observation)
        {
            size_t l_index = m_histogram->binSearch(observation);
            m_window->push_back(l_index);

            if (m_window->size() > m_windowSize)
            {
                decrement(m_window->front());
                m_window->pop_front();
            }

            m_histogram->update(observation);
            increment(l_index);
            m_historyCount++;
        }

        void StreamingEntropy::increment(const size_t& index)
        {
            auto l_n = static_cast<double>(m_histogram->getTotalCount());
            auto l_count = static_cast<double>(m_histogram->getBin(index)->m_count);

            double l_rhs = -Utils::xlogx(l_count / l_n) + Utils::xlogx(((l_count - 1.0) / l_n));
            if (1 == l_n)
            {
                m_entropy = l_rhs;
            }
            else
            {
                double l_lhs = ((l_n - 1.0) / l_n) * (m_entropy - std::log2((l_n - 1.0) / l_n));
                m_entropy = l_lhs + l_rhs;
            }
        }

        void StreamingEntropy::decrement(const size_t& index)
        {
            double l_n = static_cast<double>(m_histogram->getTotalCount()) - 1.0;
            double l_count = static_cast<double>(m_histogram->getBin(index)->m_count) - 1.0;

            m_entropy = (l_n + 1.0) / l_n *
                            (m_entropy + Utils::xlogx((l_count + 1.0) / (l_n + 1.0)) -
                             Utils::xlogx(l_count / (l_n + 1.0))) +
                        std::log2(l_n / (l_n + 1.0));
        }

        double StreamingEntropy::evaluate() const { return m_entropy; }
    }  // namespace Statistics
}  // namespace KML
