/*!
 * @file MSE.h
 * @brief
 */
#ifndef __MSE_LOSS_H__
#define __MSE_LOSS_H__

#include "ILoss.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Losses
        {
            class MSE : public ILoss
            {
                public:
                    /*!
                     * @brief
                     */
                    MSE();

                    /*!
                     * @brief
                     */
                    virtual ~MSE();

                protected:
                    /*!
                     * @brief
                     */
                    virtual double forward(const KMatrix &y_true, const KMatrix &y_pred) const override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix backward(const KMatrix &y_true, const KMatrix &y_pred) const override;
            };
        } // Losses
    } // NeuralNetworks
} // KML

#endif // __MSE_LOSS_H__
