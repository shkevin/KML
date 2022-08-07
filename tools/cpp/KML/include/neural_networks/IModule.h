/*!
 * @file IModule.h
 * @brief
 */
#ifndef __IMODULE_H__
#define __IMODULE_H__

#include "KMatrix.h"

using KML::DataStructures::KMatrix;

namespace KML
{
    namespace NeuralNetworks
    {
        class IModule
        {
            public:
                IModule() = default;

                /*!
                 * @brief
                 */
                virtual ~IModule();

                /*!
                 * @brief
                 */
                virtual KMatrix forward(const KMatrix& x) = 0;

                /*!
                 * @brief
                 */
                virtual KMatrix backward(const KMatrix& out) = 0;
        };
    } // NeuralNetworks
} // KML

#endif // __IMODULE_H__
