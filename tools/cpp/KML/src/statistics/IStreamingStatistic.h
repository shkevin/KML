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
#include <deque>

namespace KML 
{
    namespace Statistics
    {
        /*! @brief An Abstract interface for streaming statistics. */
        template<typename T = double>
        class IStreamingStatistic
        {
            public:
                /**
                 * @brief   IStreamingStatistic Constructor.
                 * @details Constructor for every Streaming Statistic.
                 * @param   windowSize Window size of number of items held in memory (range [0,..)).
                 */
                IStreamingStatistic(const uint64_t windowSize = 0);

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

                /**
                 * @brief  Takes a single observation and updates the deriving class.
                 * @param  observation The observation used to update deriving class.
                 */
                virtual void update(const T& observation) = 0;

                /**
                 * @brief  Takes in a list of one or more observations to update 
                 *         the deriving class.
                 * @param  observations List of observations to update deriving class.
                 */
                virtual void update(const std::vector<T>& observations);

                /**
                 * @brief  Evaluate everything in the current window.
                 * @return The deriving class evaluate. 
                 */
                virtual double evaluate() const = 0;

                /**
                 * @brief Retrive the current window.
                 * @return Pointer to current window.
                 */
                virtual std::deque<T>* getWindow();

            protected:
                /**
                 * @brief Pointer to current window of observations.
                 */
                std::deque<T>* m_window;

                /**
                 * @brief The current window size.
                 */
                const uint64_t m_windowSize;

                /**
                 * @brief The number of observations seen by deriving class.
                 */
                uint64_t m_historyCount;
        };
    }
}

#include "IStreamingStatistic.tcc"

#endif // __STREAMING_STATISTIC_H__
