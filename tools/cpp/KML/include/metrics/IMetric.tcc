/*!
 * @file IMetric.tcc
 * @brief
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
    } // Metrics
} // KML
