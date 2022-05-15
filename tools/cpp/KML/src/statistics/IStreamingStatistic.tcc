/**
 * @file IStreamingStatistic.tcc
 * @brief Contains the templated implementation for the abstract streaming
 *        statistic class.
 */
#include <stdexcept>

namespace KML
{
    namespace Statistics
    {
        template<typename T>
            IStreamingStatistic<T>::IStreamingStatistic(const uint64_t windowSize): m_windowSize(windowSize) {
                if(m_windowSize <= 0) m_window = nullptr;
            }

        template<typename T>
        IStreamingStatistic<T>::~IStreamingStatistic() 
        {
            delete m_window;
        }

        template<typename T>
        void IStreamingStatistic<T>::update(const T& observation) {}

        template<typename T>
        void IStreamingStatistic<T>::update(const std::vector<T>& observations) 
        {
            for(auto it = observations.begin(); it != observations.end(); it++)
            {
                this->update(*it);
            }
        }

        template<typename T>
        std::deque<T>* IStreamingStatistic<T>::getWindow()
        {
            return m_window;
        }
    }
}
