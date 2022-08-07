/*!
 * @file
 * @brief
 */
#include <utility> // pair
#include <iostream>

#include "Sequential.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Models
        {
            Sequential::Sequential(std::vector<ILayer *> &layers, const ILoss *loss,
                    const size_t &epochs) : IModel(layers, loss, epochs)
            {
            
            }

            KMatrix Sequential::fit(const KMatrix &X, const KMatrix &y)
            {
                std::pair<size_t, size_t> l_outputShape = m_layers[m_layers.size() - 1]->shape();
                KMatrix l_output;
                KMatrix l_error;
                double l_loss = 0.0;
                size_t l_numSamples = X.rows();

                for(size_t i = 0; i < m_epochs; i++)
                {
                    for(size_t j = 0; j < l_numSamples; j++)
                    {
                        // Forward propagate
                        l_output = X.row(j);
                        l_output = forward(l_output);

                        // Calculate loss
                        /* l_loss += m_loss->forward(y, l_output); */

                        // Backward propagate
                        l_error = m_loss->backward(y.row(j), l_output);
                        l_error = backward(l_error);
                    }
                }
                // Calculate average loss on all samples
                /* l_loss /= l_numSamples; */

                return X;
            }

            KMatrix Sequential::predict(const KMatrix &X)
            {
                // Get output layer shape
                std::pair<size_t, size_t> l_predictShape = m_layers[m_layers.size() - 1]->shape();
                KMatrix l_predictions(l_predictShape.first, l_predictShape.second);
                KMatrix l_output;
                size_t l_numSamples = X.rows();

                for(size_t j = 0; j < l_numSamples; j++)
                {
                    l_output = X.row(j);
                    l_predictions.row(j) = forward(l_output);
                    std::cout << l_predictions << std::endl;
                    std::cout << "end" << std::endl;
                }
                return l_predictions;
            }

            KMatrix Sequential::forward(const KMatrix& x)
            {
                KMatrix l_output = x;
                for(auto it = m_layers.begin(); it != m_layers.end(); it++)
                {
                    l_output = (*it)->forward(l_output);
                }
                return l_output;
            }

            KMatrix Sequential::backward(const KMatrix& out)
            {
                KMatrix l_error = out;
                std::cout << "backward start" << std::endl;
                for(auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
                {
                    std::cout << (*it)->name() << std::endl;
                    /* std::cout << "R = " << l_error.rows() << ", C = " << l_error.cols() << std::endl; */
                    l_error = (*it)->backward(l_error);
                }
                std::cout << "backward done" << std::endl;
                return l_error;
            }
        } // Models
    } // NeuralNetworks
 } // KML
