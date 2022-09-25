/*!
 * @file
 * @brief
 */
#ifndef __ILAYER_H__
#define __ILAYER_H__

#include <utility> // pair
#include <cstring>

#include "IModule.h"

namespace KML
{
    namespace NeuralNetworks
    {
        class ILayer : public IModule
        {
            public:
                /*!
                 * @brief Default Constructor.
                 */
                ILayer() = default;

                /*!
                 * @brief
                 */
                ILayer(const size_t inputSize, const size_t outputSize);

                /*!
                 * @brief Default Copy Constructor.
                 */
                ILayer(const ILayer& a_rhs) = delete;

                /*!
                 * @brief Default Assignment Constructor.
                 */
                ILayer& operator=(const ILayer& a_rhs) = delete;

                /*!
                 * @brief
                 */
                virtual ~ILayer();

                /*!
                 * @brief
                 */
                std::pair<size_t, size_t> shape();

                /*!
                 * @brief
                 */
                std::string name();
                
            protected:
                /*!
                 * @brief
                 */
                std::string m_name = "Not Set";

                /*!
                 * @brief
                 */
                KMatrix m_input;

                /*!
                 * @brief
                 */
                const size_t m_inputSize = 0;

                /*!
                 * @brief
                 */
                const size_t m_outputSize = 0;
        };
    }
}

#endif // __ILAYER_H__
