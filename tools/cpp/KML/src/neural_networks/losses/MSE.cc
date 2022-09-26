/*!
 * @file
 * @brief
 */
#include "MSE.h"

#include <iostream>

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Losses
        {
            MSE::MSE() {}

            MSE::~MSE() {}

            double MSE::forward(const KMatrix &y_true, const KMatrix &y_pred) const
            {
                std::cout << "true = " << y_true << std::endl;
                std::cout << "pred = " << y_pred << std::endl;
                std::cout << "error = " << (y_pred - y_true).squaredNorm() / y_true.rows()
                          << std::endl;
                return (y_pred - y_true).squaredNorm() / y_true.rows();
            }

            KMatrix MSE::backward(const KMatrix &y_true, const KMatrix &y_pred) const
            {
                return 2.0 * (y_pred - y_true) / y_true.rows();
            }
        }  // namespace Losses
    }      // namespace NeuralNetworks
}  // namespace KML
