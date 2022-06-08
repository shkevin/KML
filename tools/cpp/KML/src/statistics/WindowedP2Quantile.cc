/*!
 * @file  WindowedP2Quantile.cc
 * @brief Implemenation of the windowed quantile estimation.
 *        This algorithm is adapted from https://aakinshin.net/tags/research-p2qe/.
 */
#include "WindowedP2Quantile.h"
#include <stdexcept>

#include <iostream>

namespace KML
{
    namespace Statistics
    {
        WindowedP2Quantile::WindowedP2Quantile(const double quantile,
                const uint64_t windowSize) : IStreamingStatistic(windowSize)
        {
            m_p2 = new StreamingP2Quantile(quantile);
            m_previous = 0.0;
            m_historyCount = 0;
        }

        WindowedP2Quantile::~WindowedP2Quantile() 
        {
            delete m_p2;
        }

        void WindowedP2Quantile::update(const double& observation)
        {
            m_historyCount++;
            m_p2->update(observation);
            if(m_window != nullptr)
            {
                if(m_historyCount % (m_windowSize + 1) == 0) 
                {
                    m_previous = m_p2->evaluate();
                    m_p2->clear();
                }
            }
        }

        double WindowedP2Quantile::evaluate()
        {
            if(m_historyCount < m_windowSize)
            {
                return m_p2->evaluate();
            }

            double w2 = (m_historyCount % m_windowSize + 1.0);
            double w1 = 1.0 - w2;
            return w1 * m_previous + w2 * m_p2->evaluate();
        }
    }
}
