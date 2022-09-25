/*!
 * @file
 * @brief
 */
#ifndef __RELU_H__
#define __RELU_H__

#include "ILayer.h"

namespace KML 
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            class ReLU : public ILayer
            {
                public:
                    /*!
                     * @brief
                     */
                    ReLU();

                    /*!
                     * @brief
                     */
                    ~ReLU();

                    /*!
                     * @brief
                     */
                    virtual KMatrix forward(const KMatrix& x) override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix backward(const KMatrix& dout) override;
            };
        } // Activations 
    } // NeuralNetworks
} // KML

#endif // __RELU_H__
