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
            std::cout << "input = (" << m_input.rows() << "," << m_input.cols() << ")" << std::endl;
            /* std::cout << " (" << m_weights.rows() << "," << m_weights.cols() << ")"; */
            return x * m_weights + m_bias;
        }

        KMatrix Dense::backward(const KMatrix &error)
        {
            /* std::cout << "input (" << m_input->rows() << "," << m_input->cols() << ")" << std::endl; */
            /* std::cout << " (" << m_weights.rows() << "," << m_weights.cols() << ")"; */
            /* std::cout << "input = (" << m_input.rows() << "," << m_input.cols() << ")" << std::endl; */
            KMatrix l_inputError = error * m_weights.transpose();
            /* KMatrix l_inputError = error * m_weights.transpose(); */
            KMatrix l_weightsError = m_input.transpose() * error;
            /* std::cout << "(" << m_input.rows() << ", " << m_input.cols() << ")"; */
            /* std::cout << " (" << m_weights.rows() << ", " << m_weights.cols() << ")"; */
            /* std::cout << " (" << l_inputError.rows() << ", " << l_inputError.cols() << ")"; */
            /* std::cout << " (" << l_weightsError.rows() << ", " << l_weightsError.cols() << ")" << std::endl; */
            m_weights -= m_learningRate * l_weightsError;
            /* std::cout << "weights update" << std::endl; */
            m_bias -= m_learningRate * error;

            return l_inputError;
        }
    }
}
