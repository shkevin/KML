/*!
 * @file
 * @brief
 */
#include "Tanh.h"

#include <cmath>
#include <iostream>

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            Tanh::Tanh() { m_name = "Tanh"; }

            Tanh::~Tanh() {}

            KMatrix Tanh::forward(const KMatrix& x)
            {
                m_input = x;
                /* return 0.5 * (1 + (0.5 * x).array().tanh()); */
                return x.array().tanh();
            }

            KMatrix Tanh::backward(const KMatrix& out)
            {
                // Derivative of tanh is sec^2. Can make this more efficient.
                KMatrix t = out.array().tanh();
                return 1 - t.array().pow(2);
            }
        }  // namespace Activations
    }      // namespace NeuralNetworks
}  // namespace KML
