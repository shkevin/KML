/*!
 * @file ITransformer.h
 * @brief Provides the interface for the Transformers.
 */
#ifndef __STREAMING_TRANSFORMER_H__
#define __STREAMING_TRANSFORMER_H__

#include "vector"

namespace KML
{
    namespace Transformers
    {

        /*! @brief An Abstract interface for transformers*/
        template<typename T = double>
        class ITransformer
        {
            public:
                /*!
                 * @brief Default Constructor.
                 */
                ITransformer();

                /*!
                 * @brief Default Copy Constructor.
                 */
                ITransformer(const ITransformer& a_rhs) = delete;

                /*!
                 * @brief Default Assignment Constructor.
                 */
                ITransformer& operator=(const ITransformer& a_rhs) = delete;

                /*!
                 * @brief Fit transformer on a single observation.
                 */
                virtual void fit(const T& observation) = 0;

                /*!
                 * @brief Fit transformer on observations.
                 */
                virtual void fit(const std::vector<T>& observations);

                /*!
                 * @brief Transform the given observation.
                 */
                virtual T transform(const T& observation) = 0;

                /*!
                 * @brief Transform the given observations.
                 */
                virtual std::vector<T>& transform(const std::vector<T>& observations);
        };
    } // Transformers
} // KML

#endif // __STREAMING_TRANSFORMER_H__
