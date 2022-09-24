/*!
 * @file  ITransformer.h
 * @brief Provides interface for Streaming Transformers.
 */
#ifndef __STREAMING_TRANSFORMER_H__
#define __STREAMING_TRANSFORMER_H__

#include "vector"

namespace KML
{
    namespace Transformers
    {

        /*! @brief An Abstract interface for streaming transformers. */
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
                ITransformer<T>& operator=(const ITransformer& a_rhs) = delete;

                /*!
                 * @brief Move Constructor.
                 */
                ITransformer(ITransformer<T>&& other);

                /*!
                 * @brief Move Assignment.
                 */
                ITransformer<T>& operator=(ITransformer<T>&& rhs);

                /*!
                 * @brief Destructor.
                 */
                virtual ~ITransformer();

                /*!
                 * @brief Fit the transformer on a single observation.
                 * @param observation Observation to fit transformer on.
                 */
                virtual void fit(const T& observation) = 0;

                /*!
                 * @brief Fit the transformer on a vector of observations.
                 * @param observations Vector of observations to fit transformer on.
                 */
                virtual void fit(const std::vector<T>& observations);

                /*!
                 * @brief Transform the given observation based on previous fitted points.
                 * @param observation Single observation to transform.
                 */
                virtual T transform(const T& observation) = 0;

                /*!
                 * @brief Transform the given vector of observation based on previous fitted points.
                 * @param observations Vector of observations to transform. 
                 */
                virtual std::vector<T>& transform(const std::vector<T>& observations);
        };
    }  // namespace Transformers
}  // namespace KML

#endif  // __STREAMING_TRANSFORMER_H__
