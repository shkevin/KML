/*!
 * @file IModel.h
 * @brief Provides the interface for Neural Network models.
 */
#ifndef __IMODEL_H__
#define __IMODEL_H__

#include <vector>

#include "ILayer.h"
#include "ILoss.h"
#include "IModule.h"

using KML::NeuralNetworks::IModule;
using KML::NeuralNetworks::Losses::ILoss;

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Models
        {
            /*!
             * @brief Abstract interface for Neural Network models.
             */
            class IModel : public IModule
            {
                public:
                    /*!
                     * @brief
                     */
                    IModel(const std::vector<ILayer *> &layers, const ILoss *loss,
                           const size_t &epochs);

                    /*!
                     * @brief Default Copy Constructor.
                     */
                    IModel(const IModel &a_rhs) = delete;

                    /*!
                     * @brief Default Assignment Constructor.
                     */
                    IModel &operator=(const IModel &a_rhs) = delete;

                    /*!
                     * @brief Move Constructor.
                     */
                    IModel(IModel &&other);

                    /*!
                     * @brief Move Assignment.
                     */
                    IModel &operator=(IModel &&rhs);

                    /*!
                     * @brief
                     */
                    virtual ~IModel();

                    /*!
                     * @brief
                     */
                    virtual KMatrix fit(const KMatrix &X, const KMatrix &y) = 0;

                    /*!
                     * @brief
                     */
                    virtual KMatrix predict(const KMatrix &X) = 0;

                    /*!
                     * @brief
                     */
                    KMatrix m_output;

                    /*!
                     * @brief
                     */
                    KMatrix m_error;

                    /*!
                     * @brief
                     */
                    std::vector<ILayer *> m_layers;

                    /*!
                     * @brief
                     */
                    const ILoss *m_loss;

                    /*!
                     * @brief
                     */
                    size_t m_epochs;

                    /*!
                     * @brief
                     */
                    size_t m_batchSize;
            };
        }  // namespace Models
    }      // namespace NeuralNetworks
}  // namespace KML

#endif  // __IMODEL_H__
