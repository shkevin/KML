/*!
 * @file
 * @brief
 */
#include <cmath>

#include "StreamingMAD.h"

namespace KML
{
    namespace Metrics
    {
        StreamingMAD::StreamingMAD(const size_t& windowSize) : IMetric(windowSize)
        {
            m_scoreMedian = new WindowedFAME();
            m_errorMedian = new WindowedFAME();
        }

        StreamingMAD::~StreamingMAD()
        {
            delete m_scoreMedian;
            delete m_errorMedian;
        }

        void StreamingMAD::update(const double& observation)
        {
            m_scoreMedian->update(observation);
            m_errorMedian->update(std::abs(observation - m_scoreMedian->evaluate()));
        }
    } // Metrics
} // KML
