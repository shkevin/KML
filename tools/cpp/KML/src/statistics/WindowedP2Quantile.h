/*!
 * @file  WindowedP2Quantile.h
 * @brief Windowed version of the p2 quantile data stream estimation.
 *        This algorithm is adapted from https://aakinshin.net/tags/research-p2qe/.
 */

#ifndef __WINDOWED_P2_QUANTILE_H__
#define __WINDOWED_P2_QUANTILE_H__

#include "IStreamingStatistic.h"
#include "StreamingP2Quantile.h"

namespace KML
{
    namespace Statistics
    {
        class WindowedP2Quantile : IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief
                 */
                WindowedP2Quantile(const double quantile, const uint64_t windowSize = 0); 

                /*!
                 * @brief
                 */
                ~WindowedP2Quantile(); 

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
                 * @brief Quantile estimator used to keep track of statistics.
                 */
                StreamingP2Quantile* m_p2;

                /*!
                 * @brief Previous quantile estimation.
                 */
                double m_previous;
        };
    }
}

#endif // __WINDOWED_P2_QUANTILE_H__

