/*!
 * @file  AdaptiveNormalizer.h
 * @brief Provides declarations for adaptive normalization.
 *
 * @reference https://arxiv.org/ftp/arxiv/papers/1910/1910.07696.pdf
 */
#ifndef __ADAPTIVE_TRANSFORMER_H__
#define __ADAPTIVE_TRANSFORMER_H__

#include "ITransformer.h"

namespace KML
{
    namespace Transformers
    {
        /*! @brief Declarations for the AdaptiveNormalizer class. */
        class AdaptiveNormalizer : public ITransformer<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 */
                AdaptiveNormalizer();

                /*!
                 * @copydoc ITransformer::fit()
                 */
                void fit(const double& observation) override;

                /*!
                 * @copydoc ITransformer::transform()
                 */
                double transform(const double& observation) override;
        };
    }  // namespace Transformers
}  // namespace KML

#endif  // __ADAPTIVE_TRANSFORMER_H__
