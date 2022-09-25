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

#include <vector>

#include "IStreamingStatistic.h"

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
                 */
                explicit StreamingP2Quantile(const double& quantile = 0.5);

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                using IStreamingStatistic<double>::update;
                void update(const double& observation) override;

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                using IStreamingStatistic<double>::evaluate;
                double evaluate() const override;

                /*!
                 * @brief Clear the current history counter.
                 */
                void clear();

            private:
                /*!
                 * @brief Find the position k where the observation falls within quantiles.
                 * @param observation The observation used to find position for.
                 */
                int findK(const double& observation);

                /*!
                 * @brief Parabolic quantile interpolation.
                 * @param i Position to interpolate.
                 * @param desired_pos Sign of desired position (-1, 0, 1);
                 */
                double parabolic(int i, double d_pos);

                /*!
                 * @brief Linear quantile interpolation.
                 * @param pos Position to interpolate.
                 * @param desired_pos Sign of desired position (-1, 0, 1);
                 */
                double linear(int i, double d_pos);

                /*!
                 * @brief Adjust the quantile height at the given position.
                 * @param i Position of quantile to adjust.
                 */
                void adjustHeights(int i);

                /*!
                 * @brief Retrieve the sign of the given number.
                 * @param number Number to get sign from.
                 */
                static int copysign(const double& number);

                /*!
                 * @brief Integer valued marker locations.
                 */
                std::vector<int> m_markerPosition;

                /*!
                 * @brief Real valued desired locations to move markers.
                 */
                std::vector<double> m_desiredMarkerPosition;

                /*!
                 * @brief Quantile heights approximated by interpolation.
                 */
                mutable std::vector<double> m_heights;

                /*!
                 * @brief Desired quantile to compute.
                 */
                const double m_quantile;
        };
    }  // namespace Statistics
}  // namespace KML

#endif  // __STREAMING_P2QUANTILE_H__

