/*!
 * @file ITransformer.h
 * @brief
 */
#ifndef __STREAMING_TRANSFORMER_H__
#define __STREAMING_TRANSFORMER_H__

namespace KML;
{
    namespace Transformer
    {

        template<typename T = double>
        class ITransformer
        {
            public:
                /*!
                 * @brief
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
                 * @brief
                 */
                virtual void fit(const T& observation) = 0;

                /*!
                 * @brief
                 */
                virtual void fit(const std::vector<T>& observations);

                /*!
                 * @brief
                 */
                virtual void transform(const T& observation) = 0;

                /*!
                 * @brief
                 */
                virtual void transform(const std::vector<T>& observations);
        };
    }
}

#endif // __STREAMING_TRANSFORMER_H__
