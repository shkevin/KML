/*!
 * @file
 * @brief
 */
#ifndef __SEQUENTIAL_H__
#define __SEQUENTIAL_H__

#include "ILayer.h"
#include "IModel.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Models
        {
            class Sequential : public IModel
            {
                public:
                    /*!
                     * @brief
                     */
                    Sequential(const std::vector<ILayer *> &layers, const ILoss *loss,
                               const size_t &epochs);

                    /*!
                     * @brief
                     */
                    virtual KMatrix fit(const KMatrix &X, const KMatrix &y) override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix predict(const KMatrix &X) override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix forward(const KMatrix &x) override;

                    /*!
                     * @brief
                     */
                    virtual KMatrix backward(const KMatrix &out) override;
            };
        }  // namespace Models
    }      // namespace NeuralNetworks
}  // namespace KML

#endif  // __SEQUENTIAL_H__
