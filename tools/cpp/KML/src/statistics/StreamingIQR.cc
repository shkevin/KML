/*!
 * @file StreamingIQR.cc
 * @brief Contains the implementation of the StreamingIQR calculation.
 */

#include "StreamingIQR.h"

#include <iostream>

namespace KML
{
    namespace Statistics
    {
        StreamingIQR::StreamingIQR(const uint64_t windowSize) : IStreamingStatistic(0) 
        {
            m_low = new WindowedP2Quantile(0.25, windowSize);   // Q1
            m_high = new WindowedP2Quantile(0.75, windowSize);  // Q3
        }

        StreamingIQR::StreamingIQR(const double low, const double high, 
                const uint64_t windowSize) : IStreamingStatistic(0) 
        {
            m_low = new WindowedP2Quantile(low, windowSize);   // Q1
            m_high = new WindowedP2Quantile(high, windowSize); // Q3
        }

        StreamingIQR::~StreamingIQR()
        {
            delete m_low;
            delete m_high;
        }

        void StreamingIQR::update(const double& observation)
        {
            m_low->update(observation);
            m_high->update(observation);
            m_historyCount += 1;
        }

        double StreamingIQR::evaluate()
        {
            return m_high->evaluate() - m_low->evaluate();
        }
    }
}
