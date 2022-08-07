/*!
 * @file
 * @brief
 */
#ifndef __TANH_H__
#define __TANH_H__

#include "ILayer.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            class Tanh : public ILayer
            {
                public:
                    /*!
                     * @brief
                     */
                    Tanh();

                    /*!
                     * @brief
                     */
                    ~Tanh();

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

#endif // __TANH_H__
