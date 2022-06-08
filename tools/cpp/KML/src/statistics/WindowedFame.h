/*!
 * @brief Fast Algorithm for Median Estimation (FAME). Calculate the median
 *         of a data stream. This algorithm is adapted from
 *         https://ieeexplore.ieee.org/document/4261339
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
                 * @brief Default Constructor.
                 * @param stepSize The step size to take when calculating median.
                 * @param epsilon The exponential growth factor. This gives the 
                 *        median calculation a "windowing flavor".
                 */
                WindowedFame(const double& stepSize = 0.1, 
                             const double& epsilon = 0.0);

                /*!
                 * @brief Destructor.
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
                 * @brief Calculated median value.
                 */
                double m_median;

                /*!
                 * @brief Step size to take.
                 */
                double m_stepSize;

                /*!
                 * @brief Exponential growth factor.
                 */
                double m_epsilon;
        };
    }
}

#endif // __WINDOWED_FAME_H__
