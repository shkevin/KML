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
                explicit StreamingMean(const uint64_t& windowSize = 0);

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                void update(const double& observation) override;
                using IStreamingStatistic<double>::update;

                /*!
                 * @copydoc IStreamingStatistic::evaluate()
                 */
                double evaluate() const override;
                using IStreamingStatistic<double>::evaluate;

            private:
                /*!
                 * @brief Sum of all elements within the window.
                 */
                double m_sum = 0.0;
        };
    }  // namespace Statistics
}  // namespace KML

#endif  // __STREAMING_MEAN_H__
