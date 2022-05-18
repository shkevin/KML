/*!
 * @file StreamingP2Quantile.cc
 * @brief Contains the implementation for the P2 streaming quantile approximation.
 *        This implementation uses the patches mentioned by aakinshin.
 * @ref https://aakinshin.net/tags/research-p2qe/
 */
#include "StreamingP2Quantile.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

namespace KML 
{
    namespace Statistics
    {
        StreamingP2Quantile::StreamingP2Quantile(const double quantile, 
                const uint64_t windowSize) : IStreamingStatistic(windowSize)
        {
            // Ensure that the quantile and window size are appropriate.
            if((quantile <= 0) || (quantile >= 100))
            {
                throw std::invalid_argument("Quantile must be in closed interval (0, 100)");
            }

            if((windowSize != 0) && (windowSize < 5))
            {
                throw std::invalid_argument("Window Size must be in [[0], [5, inf)]");
            }

            // Need to create markers/heights.
            m_desireMarkerPosition = std::vector<double>{0, 0, 0, 0, 0};
            m_markerPosition = std::vector<uint8_t>{0, 0, 0, 0, 0};
            m_heights = std::vector<double>{0, 0, 0, 0, 0};
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
                    m_desireMarkerPosition = m_heights;
                    std::vector<double> l_heights = {0, 2 * m_quantile, 4 * m_quantile,
                        2 + 2 * m_quantile, 4};
                    m_markerPosition[1] = (uint8_t)std::round(l_heights[1]);
                    m_markerPosition[2] = (uint8_t)std::round(l_heights[2]);
                    m_markerPosition[3] = (uint8_t)std::round(l_heights[3]);

                    for(auto i = 1; i < 5; i++)
                    {
                        m_heights[i] = m_desireMarkerPosition[m_markerPosition[i]];
                    }

                    for(auto i = 0; i < 5; i++)
                    {
                        m_desireMarkerPosition[i] = l_heights[i];
                    }
                }
            }

            // Once first 5 observations have been seen, calculate new quantile.
            uint8_t k = findK(observation);
            for(auto i = k + 1; i < 5; i++)
            {
                m_markerPosition[k]++;
            }
            // Verify this.
            m_desireMarkerPosition[1] = m_historyCount * m_quantile / 2;
            m_desireMarkerPosition[2] = m_historyCount * m_quantile;
            m_desireMarkerPosition[3] = m_historyCount * (1 + m_quantile) / 2;
            m_desireMarkerPosition[4] = m_historyCount;

            // Apply patch where quantile <= 0.5 can cause collissions.
            if(m_quantile >= 0.5) for(auto i = 1; i < 5; i++) adjustHeights(i);
            else for(auto i = 3; i > 0; i--) adjustHeights(i);
        }

        double StreamingP2Quantile::evaluate()
        {
            if(m_historyCount <= 5)
            {
                // Ensure the heights are sorted before returning.
                sort(m_heights.begin(), m_heights.end());
                uint8_t index = (int)std::round((m_historyCount - 1) * m_quantile);
                return m_heights[index];
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
                for(auto i = 1; i < 5; i++)
                {
                    if(observation < m_heights[i])
                    {
                        k = i - 1;
                        return k;
                    }
                }
                //q5 < observation
                k = 3;
            }

            return k;
        }

        void StreamingP2Quantile::adjustHeights(uint8_t i)
        {
            double d_pos = m_desireMarkerPosition[i] - m_markerPosition[i];

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
