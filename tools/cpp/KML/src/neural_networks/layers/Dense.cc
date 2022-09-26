#include "Dense.h"

#include <iostream>

namespace KML
{
    namespace NeuralNetworks
    {
        Dense::Dense(size_t inputSize, size_t outputSize) : ILayer(inputSize, outputSize)
        {
            m_name = "Dense";
            m_weights = KMatrix::Random(inputSize, outputSize);
            m_bias = KMatrix::Random(1, outputSize);
        }

        Dense::~Dense()
        {
            // Do nothing.
        }

        KMatrix Dense::forward(const KMatrix &x)
        {
            m_input = x;
            return x * m_weights + m_bias;
        }

        KMatrix Dense::backward(const KMatrix &error)
        {
            KMatrix l_inputError = error * m_weights.transpose();
            KMatrix l_gradient = m_input.transpose() * error;
            m_weights -= m_learningRate * l_gradient;
            m_bias -= m_learningRate * error;

            return l_inputError;
        }
    }  // namespace NeuralNetworks
}  // namespace KML
