#ifndef __IOPTIMIZER_H__
#define __IOPTIMIZER_H__

#include <iostream>

namespace KML
{
    namespace Optimizers
    {

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
                 * @brief Default Copy Constructor.
                 */
                IOptimizer(const IOptimizer& a_rhs) = delete;

                /*!
                 * @brief Default Assignment Constructor.
                 */
                IOptimizer& operator=(const IOptimizer& a_rhs) = delete;

                /*!
                 * @brief Destructor.
                 */
                virtual ~IOptimizer();

                /*!
                 * @brief  Takes a single observation and updates the deriving class.
                 * @param  observation The observation used to update deriving class.
                 */
                virtual void update(const T& observation) = 0;

            protected:

            private:
        };
    } // Optimizers
} // KML

#endif // __IOPTIMIZER_H__
