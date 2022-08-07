/*!
 * @file
 * @brief
 */
#include "MSE.h"

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
                return (y_pred - y_true).squaredNorm() / y_true.rows();
            }

            KMatrix MSE::backward(const KMatrix &y_true, const KMatrix &y_pred) const
            {
                return 2.0 * (y_pred - y_true) / y_true.rows();
            }
        } // Losses
    } // NeuralNetworks
} // KML
