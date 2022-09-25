/*!
 * @file
 * @brief
 */
#include <math.h>

#include "ReLU.h"
#include <iostream>

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            ReLU::ReLU() 
            {
                m_name = "ReLU";
            }

            ReLU::~ReLU() {}

            KMatrix ReLU::forward(const KMatrix &x)
            {
                m_input = x;
                return (x.array() < 0.f).select(0.f, x);
            }

            KMatrix ReLU::backward(const KMatrix& out)
            {
                KMatrix blah = (m_input.array() < 0.f).select(0.f, out);
                std::cout << "(" << m_input.rows() << ", " << m_input.cols() << ")";
                std::cout << " (" << out.rows() << ", " << out.cols() << ")";
                std::cout << " (" << blah.rows() << ", " << blah.cols() << ")" << std::endl;;
                return (m_input.array() < 0.f).select(0.f, out);
            }
        } // Activations
    } // NeuralNetworks
} // KML
