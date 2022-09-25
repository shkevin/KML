/*!
 * @file  IStreamingStatistic.h
 * @brief Provides interface for streaming statistics.
 *
 * The streaming statistic interface is supposed to represent any
 * KML streaming statitic. Every statistic should inherit from this
 * interface.
 */
#ifndef __ISTREAMING_STATISTIC_H__
#define __ISTREAMING_STATISTIC_H__

#include <cstdint>
#include <vector>

#include "IStreaming.h"

namespace KML
{
    namespace Statistics
    {
        /*! @brief An Abstract interface for streaming statistics. */
        template<typename T = double>
        class IStreamingStatistic : public IStreaming<T>
        {
            public:
                /*!
                 * @brief   IStreamingStatistic Constructor.
                 * @details Constructor for every Streaming Statistic.
                 * @param   windowSize Window size of number of items held in memory (range [0,..)).
                 */
                explicit IStreamingStatistic(const size_t& windowSize = 0);
        };
    }  // namespace Statistics
}  // namespace KML

#include "IStreamingStatistic.tcc"

#endif // __ISTREAMING_STATISTIC_H__
