/*!
 * @file  StreamingVariance.h
 * @brief Provides the declarations for the StreamingVariance calculation.
 *
 * The StreamingVariance computes the variance of a data stream. This class
 * can work on all the data or a window of the data. Each update is
 * O(1), with at most O(window size) memory.
 */

#ifndef __STREAMING_VARIANCE_H__
#define __STREAMING_VARIANCE_H__

#include "IStreamingStatistic.h"
#include "StreamingMean.h"

namespace KML
{
    namespace Statistics
    {
        /*! @brief A StreamingVariance class for calculating the mean of
         *  a datastream.
         */
        class StreamingVariance : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The window size to calculate the streaming variance.
                 *        This window size defaults to a window size of 0, meaning
                 *        the variance is over the entire data stream.
                 */
                StreamingVariance(const uint64_t windowSize = 0);

                /*!
                 * @brief Destructor.
                 */
                ~StreamingVariance();

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

            protected:
                /*!
                 * @brief Mean of all elements within the window.
                 */
                StreamingMean* m_mean;

                /*!
                 * @brief Mean of squared sum of all elements within the window.
                 */
                StreamingMean* m_sumSquared;
        };
    }
}

#endif // __STREAMING_VARIANCE_H__
