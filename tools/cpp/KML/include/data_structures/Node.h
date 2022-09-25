/*!
 * @file Node.h
 * @brief Provides the declarations for the Node data structure.
 */
#ifndef __NODE_H__
#define __NODE_H__

#include <cstdint>

namespace KML
{
    namespace DataStructures
    {
        /*!
         * @brief Node delcaration for LinkedLists.
         */
        template<typename T = double>
        class Node
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param value The value the node holds.
                 */
                explicit Node(const T &value);

                /*!
                 * @brief The value of this node.
                 */
                T m_value;

                /*!
                 * @brief Pointer to next node in sequence.
                 */
                Node *m_next = nullptr;

                /*!
                 * @brief Pointer to previous node in sequence.
                 */
                Node *m_previous = nullptr;
        };
    }  // namespace DataStructures
}  // namespace KML

#include "Node.tcc"

#endif  // __NODE_H__
