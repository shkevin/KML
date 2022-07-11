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
        LinkedList<T>::LinkedList(const size_t& windowSize) : IDataStructure<T>(windowSize),
            m_head(nullptr), m_tail(nullptr)
        {
            // Do nothing
        }

        template<typename T>
        LinkedList<T>::~LinkedList() 
        {
            reset();
        }

        template<typename T>
        void LinkedList<T>::update(const T& item)
        {
            Node<T> *l_node = new Node<T>(item);

            if(empty())
            {
                m_head = l_node;
                m_tail = l_node;
            }
            else
            {
                // Update tail with new node.
                m_tail->m_next = l_node;
                l_node->m_previous = m_tail;
                m_tail = l_node;

                // Need to ensure window doesn't overflow.
                if(m_size == this->m_windowSize) pop();
            }

            m_size++;
            this->m_historyCount++;
        }

        template<typename T>
        void LinkedList<T>::reset()
        {
            Node<T> *l_next = m_head->m_next;
            while(l_next)
            {
                l_next->m_previous = nullptr;
                delete l_next->m_previous;
                l_next = l_next->m_next;
            }

            m_size = 0;
            m_head = nullptr;
            m_tail = nullptr;
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
        void LinkedList<T>::display() const
        {
            Node<T> *l_next = m_head;
            while(l_next)
            {
                std::cout << l_next->m_value << " ";
                l_next = l_next->m_next;
            }
            std::cout << "" << std::endl;
        }

        template<typename T>
        T LinkedList<T>::pop()
        {
            // If empty return data type.
            if(empty() | m_size <= 0) return T();
            
            // Pop head and update reference.
            Node<T> *l_next = m_head->m_next;
            T l_value = m_head->m_value;
            delete m_head;
            m_head = l_next;

            m_size--;
            return l_value;
        }
    } // DataStructures
} // KML
