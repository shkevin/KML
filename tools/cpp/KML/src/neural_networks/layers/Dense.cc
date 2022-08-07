#include "Dense.h"

#include <iostream>

namespace KML
{
    namespace NeuralNetworks
    {
        Dense::Dense(size_t inputSize, size_t outputSize) : ILayer(inputSize, outputSize),
            m_weights(inputSize, outputSize), m_bias(1, outputSize)
        {
            m_name = "Dense";
        }

        Dense::~Dense()
        {
            // Do nothing.
        }

        KMatrix Dense::forward(const KMatrix &x)
        {
            m_input = &x;
            m_output = x * m_weights + m_bias;
            return m_output;
        }

        KMatrix Dense::backward(const KMatrix &error)
        {
            std::cout << "start" << std::endl;
            KMatrix l_inputError = error * m_weights.transpose();
            std::cout << "input" << std::endl;
            std::cout << "input (" << m_input->rows() << "," << m_input->cols() << ")" << std::endl;
            std::cout << "error (" << error.rows() << "," << error.cols() << ")" << std::endl;
            KMatrix l_weightsError = m_input->transpose() * error.transpose();
            std::cout << "error (" << l_weightsError.rows() << "," << l_weightsError.cols() << ")" << std::endl;
            std::cout << "weights" << std::endl;
            std::cout << "weights (" << m_weights.rows() << "," << m_weights.cols() << ")" << std::endl;
            KMatrix blah = l_weightsError.array() * m_learningRate; 
            std::cout << "update (" << blah.rows() << "," << blah.cols() << ")" << std::endl;
            m_weights -= m_learningRate * l_weightsError;
            std::cout << "weights update" << std::endl;
            m_bias -= m_learningRate * error;

            return l_inputError;
        }
    }
}
