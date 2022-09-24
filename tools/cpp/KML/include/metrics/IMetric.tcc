/*!
 * @file IMetric.tcc
 * @brief Contains the templated implementation for the abstract streaming 
 *        metric class.
 */
namespace KML
{
    namespace Metrics
    {
        template<typename T>
        IMetric<T>::IMetric(const size_t& windowSize) : IStreaming<T>(windowSize)
        {
            // Do nothing.
        }
    }  // namespace Metrics
}  // namespace KML
