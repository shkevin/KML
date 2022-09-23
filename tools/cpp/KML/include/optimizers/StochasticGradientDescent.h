#ifndef __STOCHASTIC_GRADIENT_DESCENT_H__
#define __STOCHASTIC_GRADIENT_DESCENT_H__

#include "IOptimizer.h"

namespace KML
{
    namespace Optimizers
    {
        template<typename T = double>
        class StochasticGradientDescent : public IOptimizer<T>
        {
            public:
                /*!
                 * @brief   Default Constructor.
                 */
                StochasticGradientDescent();

                /*!
                 * @brief  Takes a single observation and updates the gradient.
                 * @param  observation The observation used to update gradient.
                 */
                virtual void update(const T& observation) override;
        };
    }
}


#endif //__STOCHASTIC_GRADIENT_DESCENT_H__
