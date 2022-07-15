/*!
 * @brief Fast Algorithm for Median Estimation (FAME). Calculate the median
 *         of a data stream. This algorithm is adapted from
 *         https://ieeexplore.ieee.org/document/4261339
 * @file WindowedFAME.h
 */
#ifndef __WINDOWED_FAME_H__
#define __WINDOWED_FAME_H__

#include "IStreamingStatistic.h"

namespace KML
{
    namespace Statistics
    {
        class WindowedFAME : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param stepSize The step size to take when calculating median.
                 * @param epsilon The exponential growth factor. This gives the 
                 *        median calculation a "windowing flavor".
                 */
                WindowedFAME(const double& stepSize = 0.1, 
                             const double& epsilon = 0.0);

                /*!
                 * @brief Destructor.
                 */
                ~WindowedFAME();

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                using IStreamingStatistic<double>::update;
                virtual void update(const double& observation) override;

                /*!
                 * @copydoc IStreamingStatistic::evaluate()
                 */
                using IStreamingStatistic<double>::evaluate;
                virtual double evaluate() const override;

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
