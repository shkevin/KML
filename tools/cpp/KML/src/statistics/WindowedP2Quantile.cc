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
            if(windowSize < 5)
            {
                throw std::invalid_argument("Need window size >= 5");
            }
            m_p2 = new StreamingP2Quantile(quantile);
            m_previous = nullptr;
        }

        WindowedP2Quantile::~WindowedP2Quantile() 
        {
            delete m_p2;
        }

        void WindowedP2Quantile::update(const double& observation)
        {
            m_historyCount += 1;
            if(m_window != nullptr)
            {
                if(m_historyCount % m_windowSize == 0)
                {
                    *m_previous = m_p2->evaluate();
                    m_p2->clear();
                }
            }
            m_p2->update(observation);
        }

        double WindowedP2Quantile::evaluate()
        {
            if(m_previous)
            {
                return m_p2->evaluate();
            }

            if(m_historyCount < m_windowSize)
            {
                return m_p2->evaluate();
            }

            double w2 = (m_historyCount % m_windowSize + 1) * 1.0 / m_windowSize;
            double w1 = 1.0 - w2;

            return w1 * (*m_previous) + w2 * m_p2->evaluate();
        }
    }
}
