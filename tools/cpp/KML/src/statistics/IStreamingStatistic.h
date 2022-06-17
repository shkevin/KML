/*!
 * @file    IStreamingStatistic.h
 * @brief   Provides interface for streaming statistics.
 *
 * The streaming statistic interface is supposed to represent any
 * KML streaming statitic. Every statistic should inherit from this
 * interface.
 */
#ifndef __STREAMING_STATISTIC_H__
#define __STREAMING_STATISTIC_H__

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
                /**
                 * @brief   IStreamingStatistic Constructor.
                 * @details Constructor for every Streaming Statistic.
                 * @param   windowSize Window size of number of items held in memory (range [0,..)).
                 */
                IStreamingStatistic(const uint64_t& windowSize = 0);

                /*!
                 * @brief Default Copy Constructor.
                 */
                IStreamingStatistic(const IStreamingStatistic& a_rhs) = delete;

                /*!
                 * @brief Default Assignment Constructor.
                 */
                IStreamingStatistic& operator=(const IStreamingStatistic& a_rhs) = delete;

                /**
                 * @brief Destructor.
                 */
                virtual ~IStreamingStatistic();
        };
    } // Statistics
} // KML

#include "IStreamingStatistic.tcc"

#endif // __STREAMING_STATISTIC_H__
