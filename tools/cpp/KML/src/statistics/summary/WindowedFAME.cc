/*!
 * @brief 
 * @file WindowedFAME.cc
 */
#include "WindowedFAME.h"
#include <cmath>

#include <iostream>

namespace KML
{
    namespace Statistics
    {
        WindowedFAME::WindowedFAME(const double& stepSize, const double& epsilon) : 
            IStreamingStatistic(0), m_median(0.0), m_stepSize(stepSize), m_epsilon(epsilon)
        {
            // Ensure that the quantile range is appropriate.
            if((m_epsilon < 0) || (m_epsilon >= 1))
            {
                throw std::invalid_argument("Epsilon must be in half closed interval [0, 1)");
            }
        }

        WindowedFAME::~WindowedFAME() 
        {
            // Do nothing
        }

        void WindowedFAME::update(const double& observation)
        {
            if(m_historyCount == 0)
            {
                m_median = observation;
                m_stepSize = std::max(std::abs(observation)/2.0, m_stepSize);
            }

            if(m_median > observation)
            {
                m_median = m_median - m_stepSize;
            }
            else if(m_median < observation)
            {
                m_median = m_median + m_stepSize;
            }

            if((m_historyCount != 0) && (std::abs(observation - m_median) < m_stepSize))
            {
                m_stepSize = m_stepSize / 2.0;
            }

            // Change suggested for "windowing flavor".
            m_stepSize = m_stepSize * (1 + m_epsilon);
            m_historyCount += 1;
        }

        double WindowedFAME::evaluate() const
        {
            return m_median;
        }
    }
}
