/*!
 * @file  WindowedP2Quantile.cc
 * @brief Implemenation of the windowed quantile estimation.
 *
 * @reference https://aakinshin.net/tags/research-p2qe/
 */
#include "WindowedP2Quantile.h"

#include <iostream>
#include <stdexcept>

namespace KML
{
    namespace Statistics
    {
        WindowedP2Quantile::WindowedP2Quantile(const double& quantile, const size_t& windowSize)
            : IStreamingStatistic(windowSize), m_previous(0.0)
        {
            m_p2 = new StreamingP2Quantile(quantile);
        }

        WindowedP2Quantile::~WindowedP2Quantile() { delete m_p2; }

        void WindowedP2Quantile::update(const double& observation)
        {
            m_historyCount++;
            m_p2->update(observation);
            if (m_window != nullptr)
            {
                if (m_historyCount % (m_windowSize + 1) == 0)
                {
                    m_previous = m_p2->evaluate();
                    m_p2->clear();
                }
            }
        }

        double WindowedP2Quantile::evaluate() const
        {
            if (m_historyCount < m_windowSize)
            {
                return m_p2->evaluate();
            }

            size_t w2 = (m_historyCount % m_windowSize + 1);
            double w1 = 1.0 - w2;
            return w1 * m_previous + w2 * m_p2->evaluate();
        }
    }  // namespace Statistics
}  // namespace KML
