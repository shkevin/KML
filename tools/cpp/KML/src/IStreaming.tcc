/**
 * @file IStreaming.tcc
 * @brief Contains the templated implementation for the abstract streaming class.
 */
namespace KML
{
    template<typename T>
    IStreaming<T>::IStreaming(const uint64_t& windowSize): 
        m_window(nullptr), m_windowSize(windowSize), m_historyCount(0)
    {
        if(m_windowSize > 0) 
        {
            m_window = new std::deque<T>(m_windowSize);
        }
    }

    template<typename T>
    IStreaming<T>::~IStreaming() 
    {
        delete m_window;
    }

    template<typename T>
    void IStreaming<T>::update(const T& observation) {}

    template<typename T>
    void IStreaming<T>::update(const std::vector<T>& observations) 
    {
        for(auto it = observations.begin(); it != observations.end(); it++)
        {
            this->update(*it);
        }
    }

    template<typename T>
    std::deque<T>* IStreaming<T>::getWindow()
    {
        return m_window;
    }
}
