/*!
 * @file  IMetric.h
 * @brief Provides interface for streaming metrics.
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
                explicit IMetric(const size_t& windowSize);
        };
    }  // namespace Metrics
}  // namespace KML

#include "IMetric.tcc"

#endif  // __METRIC_H__
