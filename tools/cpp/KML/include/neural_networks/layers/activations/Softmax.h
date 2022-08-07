/*!
 * @file
 * @brief
 */
#ifndef __SOFTMAX_H__
#define __SOFTMAX_H__

#include "IModule.h"

namespace KML
{
    namespace NeuralNetworks
    {
        class Softmax : public IModule
        {
            public:
                /*!
                 * @brief
                 */
                Softmax() = default;

                /*!
                 * @brief
                 */
                ~Softmax() = delete;

                /*!
                 * @brief
                 */
                virtual void forward(const KMatrix& x) override;

                /*!
                 * @brief
                 */
                virtual void backward(const KMatrix& dout) override;
        };
    }
}


#endif // __SOFTMAX_H__
