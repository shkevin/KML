/*!
 * @file  ITransformers.tcc
 * @brief Contains the templated implementation for the abstract transformer class.
 */
namespace KML
{
    namespace Transformers
    {
        template<typename T>
        ITransformers<T>::ITransformer()
        {
            // Do nothing
        }

        template<typename T>
        void ITransformers<T>::fit(const std::vector<T>& observations)
        {
            for (auto it = observations.begin(); it != observations.end(); it++)
            {
                this->fit(*it);
            }
        }

        template<typename T>
        std::vector<T>& observations
        ITransformers<T>::transform(const std::vector<T>& observations)
        {
            for (auto it = observations.begin(); it != observations.end(); it++)
            {
                this->transform(*it);
            }
        }
    }  // namespace Transformers
}  // namespace KML
