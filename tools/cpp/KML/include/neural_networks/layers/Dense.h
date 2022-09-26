/*!
 * @file Dense.h
 * @brief
 */
#ifndef __DENSE_LAYER_H__
#define __DENSE_LAYER_H__

#include "ILayer.h"

namespace KML
{
    namespace NeuralNetworks
    {
        class Dense : public ILayer
        {
            public:
                /*!
                 * @brief
                 */
                Dense(const size_t inputSize, const size_t outputSize);

                /*!
                 * @brief
                 */
                virtual ~Dense();

                /*!
                 * @brief
                 */
                virtual KMatrix forward(const KMatrix& x) override;

                /*!
                 * @brief
                 */
                virtual KMatrix backward(const KMatrix& dout) override;

            protected:
                /*!
                 * @brief
                 */
                KMatrix m_weights;

                /*!
                 * @brief
                 */
                KMatrix m_bias;
 
                /*!
                 * @brief
                 */
                double m_learningRate = 1e-2;
        };
    } // NeuralNetworks
} // KML

#endif // __DENSE_LAYER_H__
