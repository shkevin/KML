/*!
 * @file  StreamingIQR.h
 * @brief Provides the declarations for the Streaming IQR calculation.
 *
 * The StreamingIQR computes the interquartile range of a data stream. 
 */
#ifndef __STREAMING_IQR_H__
#define __STREAMING_IQR_H__

#include "IStreamingStatistic.h"
#include "WindowedP2Quantile.h"

namespace KML
{
    namespace Statistics
    {
        /*!
         * @brief A Streaming IQR class for calculating the interquartile
         *        range.
         */
        class StreamingIQR : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The window size to calculate the IQR.
                 *        This window size defaults to a window size of 0, meaning
                 *        the IQR is over the entire data stream.
                 */
                explicit StreamingIQR(const size_t& windowSize = 0);

                /*!
                 * @brief Constructor for setting quantile values.
                 * @param low Q1 quantile to estimate.
                 * @param high Q3 quantile to estimate.
                 * @param windowSize The window size to calculate the IQR.
                 *        This window size defaults to a window size of 0, meaning
                 *        the IQR is over the entire data stream.
                 */
                StreamingIQR(const double& low, const double& high, const size_t& windowSize = 0);

                /*!
                 * Copy Constructor.
                 */
                StreamingIQR(const StreamingIQR&) = delete;  // No copy

                /*!
                 * Copy Assignment Operator.
                 */
                StreamingIQR& operator=(const StreamingIQR&) = delete;  // No copy

                /*!
                 * @brief Move Constructor.
                 */
                StreamingIQR(StreamingIQR&& other);

                /*!
                 * @brief Move Assignment.
                 */
                StreamingIQR& operator=(StreamingIQR&& rhs);

                /*!
                 * @brief Destructor.
                 */
                ~StreamingIQR() override;

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
                 * @brief Q1 quantile to estimate.
                 */
                WindowedP2Quantile* m_low;  // Q1

                /*!
                 * @brief Q3 quantile to estimate.
                 */
                WindowedP2Quantile* m_high;  // Q3
        };
    }  // namespace Statistics
}  // namespace KML

#endif  // __STREAMING_IQR_H__
