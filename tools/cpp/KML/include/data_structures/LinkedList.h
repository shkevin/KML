/*!
 * @file DoublyLinkedList.h
 * @brief Provides the declarations for the Doubly Linked List data structure.
 */
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <mutex>  // Lock

#include "IDataStructure.h"
#include "Node.h"

namespace KML
{
    namespace DataStructures
    {

        template<typename T = double>
        class LinkedList : public IDataStructure<T>
        {
            public:
                /*!
				 * @brief Default Constructor.
				 * @param windowSize the Number of nodes to hold in linked list.
				 */
                explicit LinkedList(const size_t &windowSize);

                /*!
				 * @brief Destructor.
				 */
                virtual ~LinkedList();

                /*!
				 * Copy Constructor.
				 */
                LinkedList(const LinkedList &) = delete;  // No copy

                /*!
				 * Copy Assignment Operator.
				 */
                LinkedList &operator=(const LinkedList &) = delete;  // No copy

                /*!
				 * @copydoc IDataStructure::update()
				 */
                virtual void update(const T &item) override;

                /*!
				 * @copydoc IDataStructure::update()
				 */
                using IDataStructure<T>::update;

                /*!
				 * @brief Return the head value of the LinkedList.
				 */
                T pop();

                /*!
				 * @copydoc IDataStructure::full()
				 */
                virtual bool full() const override;

                /*!
				 * @copydoc IDataStructure::empty()
				 */
                virtual bool empty() const override;

                /*!
				 * @copydoc IDataStructure::size()
				 */
                virtual size_t size() const override;

                /*!
				 * @copydoc IDataStructure::reset()
				 */
                virtual void reset() override;

                /*!
				 * @brief Print out the node values to standard out.
				 */
                void display() const;

            private:
                /*!
				 * @brief Lock used to lock operations. This allows for
				 * threading the ring buffer.
				 */
                std::mutex m_mutex;

                /*!
				 * @brief Pointer to the current head of the linked list.
				 */
                Node<T> *m_head = nullptr;

                /*!
				 * @brief Pointer to the current tail of the linked list.
				 */
                Node<T> *m_tail = nullptr;

                /*!
				 * @brief Number of nodes in linked list.
				 */
                size_t m_size = 0;
        };
    }  // namespace DataStructures
}  // namespace KML

#include "LinkedList.tcc"

#endif  // __LINKED_LIST_H__
