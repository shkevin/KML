/*!
 * @file StreamingP2Quantile.cc
 * @brief Contains the implementation for the P2 streaming quantile approximation.
 *        This implementation uses the patches mentioned by aakinshin.
 *        https://aakinshin.net/tags/research-p2qe/
 */
#include "StreamingP2Quantile.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

#include <iostream>

namespace KML 
{
    namespace Statistics
    {
        StreamingP2Quantile::StreamingP2Quantile(const double quantile) : IStreamingStatistic(0)
        {
            // Ensure that the quantile range is appropriate.
            if((quantile <= 0) || (quantile >= 1))
            {
                throw std::invalid_argument("Quantile must be in closed interval (0, 1)");
            }

            // Need to create markers/heights.
            m_desiredMarkerPosition = std::vector<double>{0, 0, 0, 0, 0};
            m_markerPosition = std::vector<int>{0, 0, 0, 0, 0};
            m_heights = std::vector<double>{0, 0, 0, 0, 0};
            m_quantile = quantile;
        }

        StreamingP2Quantile::~StreamingP2Quantile()
        {
            // Do nothing.
        }

        void StreamingP2Quantile::update(const double& observation)
        {
            if(m_historyCount < 5)
            {
                m_heights[m_historyCount++] = observation;

                if(m_historyCount == 5)
                {
                    sort(m_heights.begin(), m_heights.end());
                    m_desiredMarkerPosition = m_heights;
                    std::vector<double> l_heights = {0.0, 2.0 * m_quantile, 4.0 * m_quantile,
                        2.0 + 2.0 * m_quantile, 4.0};
                    m_markerPosition[1] = (int)std::round(l_heights[1]);
                    m_markerPosition[2] = (int)std::round(l_heights[2]);
                    m_markerPosition[3] = (int)std::round(l_heights[3]);

                    for(auto i = 1; i < 4; i++)
                    {
                        m_heights[i] = m_desiredMarkerPosition[m_markerPosition[i]];
                    }

                    m_desiredMarkerPosition = l_heights;
                }
                return;
            }

            // Once first 5 observations have been seen, calculate new quantile.
            int k = findK(observation);
            for(int i = k + 1; i < 5; i++)
            {
                m_markerPosition[i] += 1;
            }
            m_desiredMarkerPosition[1] = (double)m_historyCount * m_quantile / 2;
            m_desiredMarkerPosition[2] = (double)m_historyCount * m_quantile;
            m_desiredMarkerPosition[3] = (double)m_historyCount * (1 + m_quantile) / 2;
            m_desiredMarkerPosition[4] = (double)m_historyCount;

            // Apply patch where quantile <= 0.5 can cause collissions.
            if(m_quantile >= 0.5)
            {
                for(auto i = 1; i <= 3; i++) adjustHeights(i);
            }
            else 
            {
                for(auto i = 3; i > 0; i--) adjustHeights(i);
            }

            m_historyCount += 1;
        }

        double StreamingP2Quantile::evaluate()
        {
            if(m_historyCount <= 5)
            {
                // Ensure the heights are sorted before returning.
                sort(m_heights.begin(), m_heights.end());
                int l_index = (int)std::floor(std::abs((double)m_historyCount - 1) * m_quantile);
                return m_heights[l_index];
            }

            return m_heights[2];
        }

        uint8_t StreamingP2Quantile::findK(const double& observation)
        {
            uint8_t k = 0;
            // q0
            if(observation < m_heights[0])
            {
                m_heights[0] = observation;
                k = 0;
            }
            else 
            {
                // q1-q4
                for(auto i = 1; i <= 4; i++)
                {
                    if(observation < m_heights[i])
                    {
                        k = i - 1;
                        return k;
                    }
                }
                //q5 < observation
                m_heights[4] = observation;
                k = 3;
            }

            return k;
        }

        void StreamingP2Quantile::adjustHeights(uint8_t i)
        {
            double d_pos = m_desiredMarkerPosition[i] - m_markerPosition[i];

            if(((d_pos >= 1) && (m_markerPosition[i+1] - m_markerPosition[i] > 1)) || 
                    ((d_pos <= -1) && (m_markerPosition[i-1] - m_markerPosition[i] < -1)))
            {
                d_pos = std::signbit(d_pos);
                double p2 = parabolic(i, d_pos);

                if((m_heights[i - 1] < p2) && (p2 < m_heights[i + 1]))
                {
                    m_heights[i] = p2;
                }
                else m_heights[i] = linear(i, d_pos);
            }

        }

        double StreamingP2Quantile::parabolic(uint8_t i, bool d_pos) 
        {
            double eps = 1e-9;  // For some reason division by zero happens.
            double l_leftHand = m_heights[i] + d_pos / 
                (m_markerPosition[i + 1] - m_markerPosition[i - 1] + eps);
            double l_innerLeft = (m_markerPosition[i] - m_markerPosition[i - 1] + d_pos) * 
                (m_heights[i + 1] - m_heights[i]) / (m_markerPosition[i + 1] - m_markerPosition[i] + eps);
            double l_innerRight = (m_markerPosition[i + 1] - m_markerPosition[i] - d_pos) * 
                (m_heights[i] - m_heights[i - 1]) / (m_markerPosition[i] - m_markerPosition[i - 1] + eps);

            return l_leftHand * (l_innerLeft + l_innerRight);
        }

        double StreamingP2Quantile::linear(uint8_t i, bool d_pos)
        {
            return m_heights[i] + d_pos * (m_heights[i + d_pos] - m_heights[i]) / 
                (m_markerPosition[i + d_pos] - m_markerPosition[i]);
        }

        void StreamingP2Quantile::clear()
        {
            m_historyCount = 0;
        }
    }
}
