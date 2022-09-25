/*!
 * @file StreamingP2Quantile.cc
 * @brief Contains the implementation for the P2 streaming quantile approximation.
 *        This implementation uses the patches mentioned by aakinshin.
 *        https://aakinshin.net/tags/research-p2qe/
 */
#include "StreamingP2Quantile.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace KML
{
    namespace Statistics
    {
        StreamingP2Quantile::StreamingP2Quantile(const double& quantile)
            : IStreamingStatistic(0), m_quantile(quantile)
        {
            // Ensure that the quantile range is appropriate.
            if ((quantile <= 0) || (quantile >= 1))
            {
                throw std::invalid_argument("Quantile must be in closed interval (0, 1)");
            }

            // Need to create markers/heights.
            m_desiredMarkerPosition = std::vector<double>{0, 0, 0, 0, 0};
            m_markerPosition = std::vector<int>{0, 1, 2, 3, 4};
            m_heights = std::vector<double>{0, 0, 0, 0, 0};
        }

        void StreamingP2Quantile::update(const double& observation)
        {
            if (m_historyCount < 5)
            {
                m_heights[m_historyCount++] = observation;

                if (m_historyCount == 5)
                {
                    // Need to sort heights to correcty index right "quantile".
                    sort(m_heights.begin(), m_heights.end());

                    // Set the desired marker positions.
                    m_desiredMarkerPosition[0] = 0;
                    m_desiredMarkerPosition[1] = 2.0 * m_quantile;
                    m_desiredMarkerPosition[2] = 4.0 * m_quantile;
                    m_desiredMarkerPosition[3] = 2.0 + 2.0 * m_quantile;
                    m_desiredMarkerPosition[4] = 4.0;
                }
                return;
            }

            // Once first 5 observations have been seen, calculate new quantile.
            int l_k = findK(observation);
            for (int i = l_k + 1; i < 5; i++) m_markerPosition[i]++;
            m_desiredMarkerPosition[1] = static_cast<double>(m_historyCount) * m_quantile / 2.0;
            m_desiredMarkerPosition[2] = static_cast<double>(m_historyCount) * m_quantile;
            m_desiredMarkerPosition[3] =
                static_cast<double>(m_historyCount) * (1.0 + m_quantile) / 2.0;
            m_desiredMarkerPosition[4] = static_cast<double>(m_historyCount);

            // Apply patch where quantile <= 0.5 can cause collissions.
            // Update everything except Min/Max.
            if (m_quantile >= 0.5)
            {
                for (int i = 1; i <= 3; i++) adjustHeights(i);
            }
            else
            {
                for (int i = 3; i > 0; i--) adjustHeights(i);
            }

            m_historyCount++;
        }

        double StreamingP2Quantile::evaluate() const
        {
            if (m_historyCount <= 5)
            {
                // Ensure the heights are sorted before returning.
                sort(m_heights.begin(), m_heights.end());
                int l_index = static_cast<int>(
                    std::round(std::abs(static_cast<double>(m_historyCount) - 1) * m_quantile));
                return m_heights[l_index];
            }

            return m_heights[2];
        }

        int StreamingP2Quantile::findK(const double& observation)
        {
            int k = 0;
            // Check Minimum
            if (observation < m_heights[0])
            {
                // Update minimum.
                m_heights[0] = observation;
                k = 0;
            }
            else if (observation < m_heights[1])
            {
                k = 0;
            }
            else if (observation < m_heights[2])
            {
                k = 1;
            }
            else if (observation < m_heights[3])
            {
                k = 2;
            }
            else if (observation < m_heights[4])
            {
                k = 3;
            }
            else
            {
                // Update maximum.
                m_heights[4] = observation;
                k = 3;
            }

            return k;
        }

        void StreamingP2Quantile::adjustHeights(int i)
        {
            double d_pos = m_desiredMarkerPosition[i] - static_cast<double>(m_markerPosition[i]);

            if ((d_pos >= 1 && m_markerPosition[i + 1] - m_markerPosition[i] > 1) ||
                (d_pos <= -1 && m_markerPosition[i - 1] - m_markerPosition[i] < -1))
            {
                double d = copysign(d_pos);
                double p2 = parabolic(i, d);

                if (m_heights[i - 1] < p2 && p2 < m_heights[i + 1])
                {
                    m_heights[i] = p2;
                }
                else
                {
                    m_heights[i] = linear(i, d);
                }
                m_markerPosition[i] += d;
            }
        }

        int StreamingP2Quantile::copysign(const double& number)
        {
            if (number > 0) return 1;
            if (number < 0) return -1;
            return 0;
        }

        double StreamingP2Quantile::parabolic(int i, double d_pos)
        {
            return m_heights[i] + d_pos / (m_markerPosition[i + 1] - m_markerPosition[i - 1]) *
                                      ((m_markerPosition[i] - m_markerPosition[i - 1] + d_pos) *
                                           (m_heights[i + 1] - m_heights[i]) /
                                           (m_markerPosition[i + 1] - m_markerPosition[i]) +
                                       (m_markerPosition[i + 1] - m_markerPosition[i] - d_pos) *
                                           (m_heights[i] - m_heights[i - 1]) /
                                           (m_markerPosition[i] - m_markerPosition[i - 1]));
        }

        double StreamingP2Quantile::linear(int i, double d_pos)
        {
            return m_heights[i] + d_pos * (m_heights[i + d_pos] - m_heights[i]) /
                                      (m_markerPosition[i + d_pos] - m_markerPosition[i]);
        }

        void StreamingP2Quantile::clear() { m_historyCount = 0; }
    }  // namespace Statistics
}  // namespace KML
