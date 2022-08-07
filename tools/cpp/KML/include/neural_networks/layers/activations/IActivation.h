/*!
 * @file
 * @brief
 */
#ifndef __IACTIVATION_H__
#define __IACTIVATION_H__

#include "ILayer.h"

namespace KML
{
    namespace NeuralNetworks
    {
        namespace Activations
        {
            class IActivation : public ILayer
            {
                public:
                    /*!
                     * @brief
                     */
                    IActivation() = default;

                    /*!
                     * @brief Default Copy Constructor.
                     */
                    IActivation(const IActivation& a_rhs) = delete;

                    /*!
                     * @brief Default Assignment Constructor.
                     */
                    IActivation& operator=(const IActivation& a_rhs) = delete;

                    /*!
                     * @brief
                     */
                    virtual ~IActivation();
            };
        } // Activations
    } // NeuralNetworks
} // KML

#endif // __IACTIVATION_H__
