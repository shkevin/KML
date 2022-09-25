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
                // Do nothing. 
            }

            KMatrix Sequential::fit(const KMatrix &X, const KMatrix &y)
            {
                KMatrix l_output;
                KMatrix l_error;
                double l_loss = 0.0;
                /* size_t l_numSamples = X.rows(); */
                size_t l_numSamples = 1;

                for(size_t i = 0; i < m_epochs; i++)
                {
                    for(size_t j = 0; j < l_numSamples; j++)
                    {
                        // Forward propagate
                        l_output = X.row(j);
                        l_output = this->forward(l_output);
                        /* std::cout << "output = (" << l_output.rows() << ", " << l_output.cols() << ")" << std::endl; */
                        /* std::cout << "output = " << l_output(0, 0)  << std::endl; */

                        // Calculate loss
                        l_loss += m_loss->forward(y.row(j), l_output);
                        /* std::cout << "loss = " << l_loss << std::endl; */

                        // Backward propagate
                        l_error = m_loss->backward(y.row(j), l_output);
                        l_error = this->backward(l_error);
                    }
                }
                // Calculate average loss on all samples
                l_loss /= l_numSamples;

                return X;
            }

            KMatrix Sequential::predict(const KMatrix &X)
            {
                // Get output layer shape
                std::cout << m_layers.size() << std::endl;
                std::pair<size_t, size_t> l_predictShape = m_layers.back()->shape();
                KMatrix l_predictions(X.rows(), l_predictShape.first);
                std::cout << "(" << l_predictions.rows() << ", " << l_predictions.cols() << ")" << std::endl;
                KMatrix l_output;
                size_t l_numSamples = X.rows();

                for(size_t j = 0; j < l_numSamples; j++)
                {
                    l_output = X.row(j);
                    l_output = this->forward(l_output);
                    std::cout << l_output << std::endl;
                    std::cout << "end" << std::endl;
                }
                return l_predictions;
            }

            KMatrix Sequential::forward(const KMatrix& x)
            {
                KMatrix l_output = x;
                for(auto it = m_layers.begin(); it != m_layers.end(); it++)
                {
                    std::cout << (*it)->name() << std::endl;
                    l_output = (*it)->forward(l_output);
                    /* std::cout << " (" << l_output.rows() << ", " << l_output.cols() << ")" << std::endl; */
                }
                return l_output;
            }

            KMatrix Sequential::backward(const KMatrix& out)
            {
                KMatrix l_error = out;
                for(auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
                {
                    std::cout << (*it)->name() << std::endl;
                    l_error = (*it)->backward(l_error);
                }
                return l_error;
            }
        } // Models
    } // NeuralNetworks
 } // KML
