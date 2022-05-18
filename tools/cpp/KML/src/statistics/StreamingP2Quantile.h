/*!
 * @file  StreamingP2Quantile.h
 * @brief Provides the declarations for the P2 quantile calculation.
 *        Reference: https://www.cs.wustl.edu/~jain/papers/ftp/psqr.pdf 
 *
 * The StreamingP2Quantile computes quantile statistics of a data stream. This class
 * can work on all the data or a window of the data. Each update is
 * O(1), with low memory complexity.
 */

#ifndef __STREAMING_P2QUANTILE_H__
#define __STREAMING_P2QUANTILE_H__

#include "IStreamingStatistic.h"
#include <vector>

namespace KML
{
    namespace Statistics
    {
        /*! @brief A StreamingP2Quantile class for calculating the quantile of
         *  a datastream.
         */
        class StreamingP2Quantile : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param quantile The desired quantile to compute.
                 * @param windowSize The window size to calculate the streaming quantile.
                 *        This window size defaults to a window size of 0, meaning
                 *        the quantile is over the entire data stream.
                 */
                StreamingP2Quantile(const double quantile, const uint64_t windowSize = 0);

                /*!
                 * @brief Destructor.
                 */
                ~StreamingP2Quantile();

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

                /*!
                 * @brief Clear the current window history.
                 */
                virtual void clear();

            private:
                /*!
                 * @brief Find the position k where the observation falls within quantiles.
                 * @param observation The observation used to find position for.
                 */
                virtual uint8_t findK(const double& observation);

                /*!
                 * @brief Parabolic quantile interpolation.
                 * @param pos Position to interpolate.
                 * @param desired_pos Sign of desired position (-1, 0, 1);
                 */
                virtual double parabolic(uint8_t pos, bool desired_pos);

                /*!
                 * @brief Linear quantile interpolation.
                 * @param pos Position to interpolate.
                 * @param desired_pos Sign of desired position (-1, 0, 1);
                 */
                virtual double linear(uint8_t i, bool d_pos);

                /*!
                 * @brief Adjust the quantile height at the given position.
                 * @param position Position of quantile to adjust.
                 */
                virtual void adjustHeights(uint8_t position);

            protected:
                /*!
                 * @brief Integer valued marker locations.
                 */
                std::vector<uint8_t> m_markerPosition;

                /*!
                 * @brief Real valued desired locations to move markers.
                 */
                std::vector<double> m_desireMarkerPosition;

                /*!
                 * @brief Quantile heights approximated by interpolation.
                 */
                std::vector<double> m_heights;

                /*!
                 * @brief Desired quantile to compute.
                 */
                double m_quantile;
        };
    }
}

#endif // __STREAMING_P2QUANTILE_H__

