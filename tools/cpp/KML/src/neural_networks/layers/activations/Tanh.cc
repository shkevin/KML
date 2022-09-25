/*!
 * @file
 * @brief
 */
#include <math.h>
#include <iostream>

#include "Tanh.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            Tanh::Tanh() 
            {
                m_name = "Tanh";
            }

            Tanh::~Tanh() {}

            KMatrix Tanh::forward(const KMatrix &x)
            {
                m_input = x;
                /* return 0.5 * (1 + (0.5 * x).array().tanh()); */
                return x.array().tanh();
            }

            KMatrix Tanh::backward(const KMatrix& out)
            {
                // Derivative of tanh is sec^2. Can make this more efficient.
                /* return 1 - out.array().tanh().pow(2); */
                return (1 - m_input.array().tanh().pow(2)) * out.array();
            }
        } // Activations
    } // NeuralNetworks
} // KML
