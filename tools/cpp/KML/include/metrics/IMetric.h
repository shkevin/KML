/*!
 * @file IMetric.h
 * @brief
 */
#ifndef __METRIC_H__
#define __METRIC_H__

namespace KML
{
    namespace Metrics
    {
        template<typename T = double>
        class IMetric
        {
            public:
                /*!
                 * @brief
                 */
                IMetric(const size_t& windowSize);

                /*!
                 * @brief
                 */
                virtual void update(const T& observation) = 0;

            protected:
                /*!
                 * @brief
                 */
                size_t m_windowSize = 0;

                /*!
                 * @brief
                 */
                size_t m_historyCount = 0;
        };
    } // Metrics
} // KML

#include "IMetric.tcc"

#endif // __METRIC_H__
