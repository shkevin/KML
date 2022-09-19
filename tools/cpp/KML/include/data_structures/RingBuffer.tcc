/*!
 * @file RingBuffer.tcc
 * @brief Contains the templated implementation for the abstract ring buffer
 *        data structure..
 * Reference: https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 */
namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        RingBuffer<T>::RingBuffer(const size_t& windowSize) : IDataStructure<T>(windowSize),
            m_buffer(std::unique_ptr<T[]>(new T[windowSize]))
        {
            // Do nothing.
        }

        template<typename T>
        void RingBuffer<T>::update(const T& item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            // Add latest item to buffer.
            m_buffer[m_head] = item;

            // Remove last item if buffer is full.
            if(m_full) m_tail = (m_tail + 1) % this->m_windowSize;

            // Increment the head.
            m_head = (m_head + 1) % this->m_windowSize;

            // Check if buffer is full.
            m_full = m_head == m_tail;

            this->m_historyCount++;
        }

        template<typename T>
        void RingBuffer<T>::reset()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_head = m_tail;
            m_full = false;
        }

        template<typename T>
        bool RingBuffer<T>::empty() const
        {
            return (!m_full && (m_head == m_tail));
        }

        template<typename T>
        bool RingBuffer<T>::full() const
        {
            return m_full;
        }

        template<typename T>
        size_t RingBuffer<T>::size() const
        {
            size_t l_size = this->m_windowSize;
            if(!m_full)
            {
                if(m_head >= m_tail)
                {
                    l_size = m_head - m_tail;
                }
                else
                {
                    l_size = this->m_windowSize + m_head - m_tail;
                }
            }
            return l_size;
        }

        template<typename T>
        T RingBuffer<T>::pop()
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            // If empty return data type.
            if(empty()) return T();

            // Get the earliest item in the buffer.
            auto l_item = m_buffer[m_tail];

            // Pulled last item, can't be full then.
            m_full = false;
            
            // Update tail position.
            m_tail = (m_tail + 1) % this->m_windowSize;

            return l_item;
        }
    } // DataStructure
} // KML
