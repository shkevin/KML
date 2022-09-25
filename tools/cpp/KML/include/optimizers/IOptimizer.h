/*!
 * @file  IOptimizer.h
 * @brief Provides interface for gradient descent optimizers.
 */
#ifndef __IOPTIMIZER_H__
#define __IOPTIMIZER_H__

#include <iostream>

namespace KML
{
    namespace Optimizers
    {
        /*!
         * @brief Optimizer Interface class declaration.
         */
        template<typename T = double>
        class IOptimizer
        {
            public:
                /*!
                 * @brief   IOptimizer Constructor.
                 * @details Constructor for every optimizer.
                 */
                IOptimizer();

                /*!
                 * @brief  Takes a single observation and updates the deriving class.
                 * @param  observation The observation used to update deriving class.
                 */
                virtual void update(const T& observation) = 0;
        };
    }  // namespace Optimizers
}  // namespace KML

#endif  // __IOPTIMIZER_H__
