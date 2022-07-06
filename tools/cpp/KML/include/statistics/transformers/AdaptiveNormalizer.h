/*!
 * https://arxiv.org/ftp/arxiv/papers/1910/1910.07696.pdf
 */
#ifndef __ADAPTIVE_TRANSFORMER_H__
#define __ADAPTIVE_TRANSFORMER_H__

#include "ITransformer.h"

namespace KML
{
    namespace Transformers
    {
        class AdaptiveNormalizer : public ITransformer<double>
        {
            public:
                /*!
                 * @brief
                 */
                AdaptiveNormalizer();

                /*!
                 * @brief
                 */
                virtual void fit(const double& observation) override;

                /*!
                 * @brief
                 */
                virtual double transform(const double& observation) override;
        };
    } // Transformer
} // KML


#endif // __ADAPTIVE_TRANSFORMER_H__
