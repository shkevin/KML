/*!
 * @file
 * @brief
 */
#include "Sequential.h"

#include <iostream>
#include <utility>  // pair

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Models
        {
            Sequential::Sequential(const std::vector<ILayer *> &layers, const ILoss *loss,
                                   const size_t &epochs)
                : IModel(layers, loss, epochs)
            {
                // Do nothing.
            }

            KMatrix Sequential::fit(const KMatrix &X, const KMatrix &y)
            {
                KMatrix l_predicted, l_error;
                size_t l_samples = X.rows();
                double err = 0.0;

                for (size_t i = 0; i < m_epochs; i++)
                {
                    for (size_t j = 0; j < l_samples; j++)
                    {
                        // Forward propagation.
                        l_predicted = X.row(j);
                        l_predicted = this->forward(l_predicted);

                        // Backward propagation.
                        l_error = m_loss->backward(y.row(j), l_predicted);
                        l_error = this->backward(l_error);

                        err += m_loss->forward(y.row(j), l_predicted);
                    }
                    err /= l_samples;
                    std::cout << "Epoch " << i+1 << "/" << m_epochs << "\terror = " << err << std::endl;
                }
                return X;
            }

            KMatrix Sequential::predict(const KMatrix &X)
            {
                std::pair<size_t, size_t> l_predictShape = m_layers.back()->shape();
                KMatrix l_predictions(X.rows(), 1);
                KMatrix l_output(1, l_predictShape.first);
                size_t l_samples = X.rows();

                for (size_t i = 0; i < l_samples; i++)
                {
                    l_output = X.row(i);
                    l_output = this->forward(l_output);
                    l_predictions.row(i) = l_output;
                }

                return l_predictions;
            }

            KMatrix Sequential::forward(const KMatrix &x)
            {
                KMatrix l_predicted = x;
                for (auto it = m_layers.begin(); it != m_layers.end(); it++)
                {
                    l_predicted = (*it)->forward(l_predicted);
                }
                return l_predicted;
            }

            KMatrix Sequential::backward(const KMatrix &out)
            {
                KMatrix l_error = out;
                for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
                {
                    l_error = (*it)->backward(l_error);
                }
                return l_error;
            }

        }  // namespace Models
    }      // namespace NeuralNetworks
}  // namespace KML
