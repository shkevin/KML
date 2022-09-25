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
        /*!
         * @brief Windowed implemented of the StreamingP2Quantile class.
         */
        class WindowedP2Quantile : IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param quantile Desired quantile to calculate.
                 * @param windowSize The window size to calculate the streaming quantile.
                 *        This window size defaults to a window size of 0, meaning
                 *        the quantile is over the entire data stream.
 
                 */
                explicit WindowedP2Quantile(const double& quantile, const size_t& windowSize = 0);

                /*!
                 * Copy Constructor.
                 */
                WindowedP2Quantile(const WindowedP2Quantile&) = delete;

                /*!
                 * Copy Assignment Operator.
                 */
                WindowedP2Quantile& operator=(const WindowedP2Quantile&) = delete;

                /*!
                 * @brief Move Constructor.
                 */
                WindowedP2Quantile(WindowedP2Quantile&& other);

                /*!
                 * @brief Move Assignment.
                 */
                WindowedP2Quantile& operator=(WindowedP2Quantile&& rhs);

                /*!
                 * @brief Destructor. 
                 */
                ~WindowedP2Quantile() override;

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
                 * @brief Quantile estimator used to keep track of statistics.
                 */
                StreamingP2Quantile* m_p2;

                /*!
                 * @brief Previous quantile estimation.
                 */
                double m_previous;
        };
    }  // namespace Statistics
}  // namespace KML

#endif  // __WINDOWED_P2_QUANTILE_H__

