/*!
 * @file StreamingMAD.cc
 * @brief Contains the implementation of the StreamingMAD calculation.
 */
#include "StreamingMAD.h"

#include <cmath>

namespace KML
{
    namespace Metrics
    {
        StreamingMAD::StreamingMAD() : IMetric(0)
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
            m_historyCount += 1;
        }

        double StreamingMAD::evaluate() const { return m_errorMedian->evaluate(); }
    }  // namespace Metrics
}  // namespace KML
