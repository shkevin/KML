/*!
 *
 */
namespace KML
{
    namespace Transformer
    {
        template<typename T>
        ITransformer<T>::ITransformer()
        {
            // Do nothing
        }

        template<typename T>
        void ITransformer<T>::fit(const std::vector<T>& observations) 
        {
            for(auto it = observations.begin(); it != observations.end(); it++)
            {
                this->fit(*it);
            }
        }

        template<typename T>
        void ITransformer<T>::transform(const std::vector<T>& observations) 
        {
            for(auto it = observations.begin(); it != observations.end(); it++)
            {
                this->transform(*it);
            }
        }
    } // Transformer
} // KML
