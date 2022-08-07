/*!
 * @file
 * @brief
 */
#ifndef __SIGMOID_H__
#define __SIGMOID_H__

#include "IActivation.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            class Sigmoid : public IActivation
            {
                public:
                    /*!
                     * @brief
                     */
                    Sigmoid() = default;

                    /*!
                     * @brief
                     */
                    ~Sigmoid();

                    /*!
                     * @brief
                     */
                    virtual KMatrix forward(const KMatrix& x) override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix backward(const KMatrix& out) override;
            };
        } // Activations
    } // NeuralNetworks
} // KML

#endif // __SIGMOID_H__
