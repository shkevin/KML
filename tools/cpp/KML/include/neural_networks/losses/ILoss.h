/*!
 * @file ILoss.h
 * @brief
 */
#ifndef __ILOSS_H__
#define __ILOSS_H__

#include "KMatrix.h"

using KML::DataStructures::KMatrix;

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Losses
        {
            class ILoss
            {
                public:
                    /*!
                     * @brief
                     */
                    ILoss();

                    /*!
                     * @brief Default Copy Constructor.
                     */
                    ILoss(const ILoss& a_rhs) = delete;

                    /*!
                     * @brief Default Assignment Constructor.
                     */
                    ILoss& operator=(const ILoss& a_rhs) = delete;

                    /*!
                     * @brief
                     */
                    virtual ~ILoss();

                    /*!
                     * @brief
                     */
                    virtual double forward(const KMatrix &y_true, const KMatrix &y_pred) const = 0;
    
                    /*!
                     * @brief
                     */
                    virtual KMatrix backward(const KMatrix &y_true, const KMatrix &y_pred) const = 0;
            };
        } // Losses
    } // NeuralNetworks
} // KML

#endif // __ILOSS_H__
