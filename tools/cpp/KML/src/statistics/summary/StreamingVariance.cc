/*!
 * @file  StreamingVariance.cc
 * @brief Provides the implementation for the StreamingVariance calculation.
 */
#include "StreamingVariance.h"

namespace KML
{
    namespace Statistics
    {
        StreamingVariance::StreamingVariance(const uint64_t& windowSize)
            : IStreamingStatistic(windowSize)
        {
            m_sumSquared = new StreamingMean(windowSize);
            m_mean = new StreamingMean(windowSize);
        }

        StreamingVariance::~StreamingVariance()
        {
            delete m_sumSquared;
            delete m_mean;
        }

        void StreamingVariance::update(const double& observation)
        {
            m_mean->update(observation);
            m_sumSquared->update(observation * observation);
        }

        double StreamingVariance::evaluate() const
        {
            double mean = m_mean->evaluate();
            return m_sumSquared->evaluate() - (mean * mean);
        }
    }  // namespace Statistics
}  // namespace KML
