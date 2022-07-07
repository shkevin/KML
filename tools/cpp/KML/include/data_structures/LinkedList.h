/*!
 * @file
 * @brief
 */
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <mutex> // Lock

#include "IDataStructure.h"
#include "Node.h"

namespace KML
{
    namespace DataStructures
    {

        template<typename T = double>
        class LinkedList : IDataStructure<T>
        {
            public:
                /*!
                 * @brief
                 */
                explicit LinkedList(const size_t& windowSize);

                /**
                 * @brief  Takes a single item and updates the deriving class.
                 * @param  item The item used to update deriving class.
                 */
                virtual void update(const T& item) override;

                /*!
                 * @brief
                 */
                virtual T pop() override;

                /*!
                 * @brief
                 */
                virtual bool full() const override;

                /*!
                 * @brief
                 */
                virtual bool empty() const override;

                /*!
                 * @brief
                 */
                virtual size_t size() const override;

                /*!
                 * @brief
                 */
                virtual void reset() override;

            private:
                /*!
                 * @brief Lock used to lock operations. This allows for threading the 
                 *        ring buffer.
                 */
                std::mutex m_mutex;

                /*!
                 * @brief
                 */
                Node<T> *m_head = nullptr;

                /*!
                 * @brief
                 */
                Node<T> *m_tail = nullptr;

                /*!
                 * @brief
                 */
                size_t m_size = 0;
        };
    } // DataStructures
} // KML

#include "LinkedList.tcc"

#endif // __LINKED_LIST_H__
