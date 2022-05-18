/*!
 * @file  StreamingMean.cc
 * @brief Contains the implementation of the StreamingMean calculation.
 */

#include "StreamingMean.h"

namespace KML
{
    namespace Statistics
    {
        StreamingMean::StreamingMean(const uint64_t windowSize): IStreamingStatistic(windowSize)
        {
            m_historyCount = 0;
            m_sum = 0.0;
        }

        StreamingMean::~StreamingMean() 
        {
            // Do nothing.
        }

        void StreamingMean::update(const double& observation)
        {
            if(m_window != nullptr)
            {
                if(m_historyCount > m_window->size())
                {
                    m_sum += m_window->front();
                    m_window->pop_front();
                }
                m_window->push_back(observation);
            }

            m_historyCount += 1;
            m_sum += observation;
        }

        double StreamingMean::evaluate()
        {
            if(m_historyCount == 0) return 0.0;
            if(m_window != nullptr)
            {
                return m_sum / m_window->size();
            }
            else
            {
                return m_sum / m_historyCount;
            }

        }
    }
}
