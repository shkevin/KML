/*!
 * @file LinkedList.tcc
 * @brief
 */
#include <iostream>
namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        LinkedList<T>::LinkedList(const size_t& windowSize) : IDataStructure<T>(windowSize)
        {
            // Do nothing
        }

        template<typename T>
        void LinkedList<T>::update(const T& item)
        {
            /* std::lock_guard<std::mutex> lock(m_mutex); */

            std::cout << "Item = " << item << std::endl;
            Node<T> l_node = Node<T>(item);
            if(nullptr == m_head)
            {
                m_head = &l_node;
                m_tail = &l_node;
            }
            else
            {
                if(nullptr == m_tail)
                {
                    l_node.m_previous = m_head;
                    m_tail = &l_node;
                }
                else
                {
                    m_tail->m_next = &l_node;
                    l_node.m_previous = m_tail;
                    m_tail = &l_node;
                }

                if(m_size == this->m_windowSize) pop();
            }

            m_size++;
            this->m_historyCount++;
        }

        template<typename T>
        void LinkedList<T>::reset()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
        }

        template<typename T>
        bool LinkedList<T>::empty() const
        {
            return nullptr == m_head;
        }

        template<typename T>
        bool LinkedList<T>::full() const
        {
            return nullptr != m_head;
        }

        template<typename T>
        size_t LinkedList<T>::size() const
        {
            return m_size;
        }

        template<typename T>
        T LinkedList<T>::pop()
        {
            /* std::lock_guard<std::mutex> lock(m_mutex); */

            // If empty return data type.
            std::cout << "Size = " << size() << std::endl;
            if(empty())
            {
                std::cout << "EMPTY" << std::endl;
                return T();
            }

            if(!m_head) std::cout << "BAD" << std::endl;
            T l_value = (*m_head).m_value;
            std::cout << "ValueP = " << l_value << std::endl;
            m_head = m_head->m_next;
            m_head->m_previous = nullptr;
            std::cout << "ValueA = " << l_value << std::endl;

            m_size--;
            return l_value;
        }
    } // DataStructures
} // KML
