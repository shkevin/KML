/*!
 * @file
 * @brief
 */
#include <stdexcept>

#include "IModel.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Models
        {
            IModel::IModel(std::vector<ILayer *> &layers, const ILoss *loss,
                    const size_t &epochs) : m_layers(layers), m_loss(loss), m_epochs(epochs)
            {
                if(m_layers.size() < 2)
                {
                    throw std::runtime_error("Must have at least an input/output layer!");
                }
                if(m_epochs <= 0) 
                {
                    throw std::runtime_error("Number of Epochs must be strictly positive!");
                }
            }

            IModel::~IModel()
            {
                for(auto it = m_layers.begin(); it != m_layers.end(); it++)
                {
                    delete (*it);
                }
            }

            void IModel::add(ILayer &layer)
            {
                m_layers.push_back(&layer);
            }
        } // Models
    } // NeuralNetworks
} // KML
