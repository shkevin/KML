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
                /* std::cout << "true = (" << y_true.rows() << "," << y_true.cols() << ")" << std::endl; */
                /* std::cout << "pred = (" << y_pred.rows() << "," << y_pred.cols() << ")" << std::endl; */
                return (y_pred - y_true).squaredNorm() / y_true.rows();
            }

            KMatrix MSE::backward(const KMatrix &y_true, const KMatrix &y_pred) const
            {
                return 2.0 * (y_pred - y_true) / y_true.rows();
            }
        } // Losses
    } // NeuralNetworks
} // KML
