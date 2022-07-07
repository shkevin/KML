/*!
 * @file
 * @brief
 */
#ifndef __NODE_H__
#define __NODE_H__

#include <cstdint>

namespace KML
{
    namespace DataStructures
    {
        template<typename T = double>
        class Node
        {
            public:
                explicit Node(const T& value);
                T m_value;
                Node *m_next = nullptr;
                Node *m_previous = nullptr;
        };
    } // DataStructures
} // KML

#include "Node.tcc"

#endif // __NODE_H__
