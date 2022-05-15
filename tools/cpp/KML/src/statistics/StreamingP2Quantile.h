/*!
 * @file  StreamingP2Quantile.h
 * @brief Provides the declarations for the P2 quantile calculation.
 * @ref   https://www.cs.wustl.edu/~jain/papers/ftp/psqr.pdf 
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
        /*! @brief A StreamingP2Quantile class for calculating the qunatile of
         *  a datastream.
         */
        class StreamingP2Quantile : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The window size to calculate the streaming quantile.
                 *        This window size defaults to a window size of 0, meaning
                 *        the quantile is over the entire data stream.
                 */
                StreamingP2Quantile(const uint64_t windowSize = 0);

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

            protected:
                /*!
                 * @brief
                 */
                vector<double> m_markerPosition;

                /*!
                 * @brief
                 */
                vector<double> m_desireMarkerPosition;

                /*!
                 * @brief
                 */
                vector<uint64_t> m_position;

                /*!
                 * @brief
                 */
                vector<double> m_heights;

                /*!
                 * @brief Desired quantile to compute.
                 */
                double m_quantile;
        };
    }
}

#endif // __STREAMING_P2QUANTILE_H__

