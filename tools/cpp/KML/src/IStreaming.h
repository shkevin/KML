/*!
 * @file  IStreaming.h
 * @brief Provides interface for streaming algorithms.
 *
 * The streaming interface is supposed to represent any
 * KML streaming algorithm. Every streaming algorithm should 
 * inherit from this interface.
 */
#ifndef __STREAMING_H__
#define __STREAMING_H__

#include <cstdint>
#include <vector>
#include <deque>

namespace KML 
{
    /*! @brief An Abstract interface for streaming statistics. */
    template<typename T = double>
    class IStreaming
    {
        public:
            /**
             * @brief   IStreaming Constructor.
             * @details Constructor for every Streaming .
             * @param   windowSize Window size of number of items held in memory (range [0,..)).
             */
            IStreaming(const uint64_t& windowSize = 0);

            /*!
             * @brief Default Copy Constructor.
             */
            IStreaming(const IStreaming& a_rhs) = delete;

            /*!
             * @brief Default Assignment Constructor.
             */
            IStreaming& operator=(const IStreaming& a_rhs) = delete;

            /**
             * @brief Destructor.
             */
            virtual ~IStreaming();

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
} // KML

#include "IStreaming.tcc"

#endif // __STREAMING_H__
