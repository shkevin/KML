/**
 * @file IStreamingStatistic.tcc
 * @brief Contains the templated implementation for the abstract streaming
 *        statistic class.
 */
namespace KML
{
    namespace Statistics
    {
        template<typename T>
        IStreamingStatistic<T>::IStreamingStatistic(const uint64_t& windowSize): 
            IStreaming<T>(windowSize)
        {
            // Do nothing.
        }

        template<typename T>
        IStreamingStatistic<T>::~IStreamingStatistic() 
        {
            // Do nothing.
        }
    } // Statistics
} // KML
