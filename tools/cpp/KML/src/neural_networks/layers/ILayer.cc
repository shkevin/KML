/*!
 *
 */
#include "ILayer.h"

namespace KML
{
    namespace NeuralNetworks
    {
        ILayer::ILayer(const size_t inputSize, const size_t outputSize) : IModule(),
            m_inputSize(inputSize), m_outputSize(outputSize)
        {
            // Do nothing
        }

        ILayer::~ILayer()
        {
            // Do nothing
        }

        std::pair<size_t, size_t> ILayer::shape()
        {
            return std::make_pair(m_inputSize, m_outputSize);
        }

        std::string ILayer::name()
        {
            return m_name;
        }
    }
}
