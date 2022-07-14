/*!
 * @file IMetric.h
 * @brief
 */
#ifndef __METRIC_H__
#define __METRIC_H__

#include "IStreaming.h"

namespace KML
{
    namespace Metrics
    {
        template<typename T = double>
        class IMetric : public IStreaming<T>
        {
            public:
                /*!
                 * @brief
                 */
                IMetric(const size_t& windowSize);
        };
    } // Metrics
} // KML

#include "IMetric.tcc"

#endif // __METRIC_H__
