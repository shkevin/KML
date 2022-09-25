/*!
 * @file
 * @brief
 */
#include "Sigmoid.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            KMatrix Sigmoid::forward(const KMatrix &x)
            {
                m_input = x;
                return x;
            }

            KMatrix Sigmoid::backward(const KMatrix& out)
            {
                // Derivative of tanh is sec^2
                return out;
            }
        } // Activations
    } // NeuralNetworks
} // KML
