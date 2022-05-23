/*!
 * @brief
 * @file WindowedFame.cc
 */
#include "WindowedFame.h"
#include <cmath>

namespace KML
{
    namespace Statistics
    {
        WindowedFame::WindowedFame(const double& stepSize, const uint64_t& windowSize) : 
            IStreamingStatistic(windowSize), m_stepSize(stepSize)
        {
            /* m_median = nullptr; */
            m_median = 0.0; 
        }

        WindowedFame::~WindowedFame() 
        {
            // Do nothing
        }

        void WindowedFame::update(const double& observation)
        {
            if(m_historyCount == 0)
            {
                m_median = observation;
                m_stepSize = std::max(observation/2, m_stepSize);
                return;
            }

            if(m_median > observation)
            {
                m_median = m_median - m_stepSize;
            }
            else if(m_median < observation)
            {
                m_median = m_median + m_stepSize;
            }

            if(std::abs(observation - m_median) < m_stepSize)
            {
                m_stepSize = m_stepSize / 2;
            }

            m_historyCount += 1;
        }

        double WindowedFame::evaluate() const
        {
            return m_median;
        }
    }
}
