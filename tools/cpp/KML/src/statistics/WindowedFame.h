/*!
 * @brief Fast Algorithm for Median Estimation (FAME). Calculate the median
 *         of a data stream.
 * @file WindowedFame.cc
 */
#ifndef __WINDOWED_FAME_H__
#define __WINDOWED_FAME_H__

#include "IStreamingStatistic.h"

namespace KML
{
    namespace Statistics
    {
        class WindowedFame : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief
                 */
                WindowedFame(const double& stepSize = 0.0, const uint64_t& windowSize = 0);

                /*!
                 * @brief
                 */
                ~WindowedFame();

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
                 * @brief
                 */
                double m_median;

                /*!
                 * @brief
                 */
                double m_stepSize;
        };
    }
}

#endif // __WINDOWED_FAME_H__
