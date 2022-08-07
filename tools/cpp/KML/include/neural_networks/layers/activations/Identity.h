/*!
 * @file
 * @brief
 */
#ifndef __IDENTITY_H__
#define __IDENTITY_H__

#include "IModule.h"

namespace KML
{
    namespace NeuralNetworks
    {
        class Identity : public IModule
        {
            public:
                /*!
                 * @brief
                 */
                Identity() = default;

                /*!
                 * @brief
                 */
                ~Identity() = delete;

                /*!
                 * @brief
                 */
                virtual void forward(const KMatrix& x) override;

                /*!
                 * @brief
                 */
                virtual void backward(const KMatrix& out) override;
        };
    }
}


#endif // __IDENTITY_H__
