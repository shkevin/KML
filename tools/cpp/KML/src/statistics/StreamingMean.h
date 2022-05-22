/*!
 * @file  StreamingMean.h
 * @brief Provides the declarations for the StreamingMean calculation.
 *
 * The StreamingMean computes the mean of a data stream. This class
 * can work on all the data or a window of the data. Each update is
 * O(1), with at most O(window size) memory.
 */

#ifndef __STREAMING_MEAN_H__
#define __STREAMING_MEAN_H__

#include "IStreamingStatistic.h"

namespace KML
{
    namespace Statistics
    {
        /*! @brief A StreamingMean class for calculating the mean of
         *  a datastream.
         */
        class StreamingMean : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The window size to calculate the streaming mean.
                 *        This window size defaults to a window size of 0, meaning
                 *        the mean is over the entire data stream.
                 */
                StreamingMean(const uint64_t windowSize = 0);

                /*!
                 * @brief Destructor.
                 */
                ~StreamingMean();

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                using IStreamingStatistic<double>::update;
                virtual void update(const double& observation);

                /*!
                 * @copydoc IStreamingStatistic::evaluate()
                 */
                using IStreamingStatistic<double>::evaluate;
                virtual double evaluate();

            private:
                /*!
                 * @brief Sum of all elements within the window.
                 */
                double m_sum;
        };
    }
}

#endif // __STREAMING_MEAN_H__
