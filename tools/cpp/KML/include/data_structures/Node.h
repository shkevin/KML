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
                /*!
                 * @brief
                 */
                explicit Node(const T& value);

                /*!
                 * @brief
                 */
                T m_value;

                /*!
                 * @brief
                 */
                Node *m_next = nullptr;

                /*!
                 * @brief
                 */
                Node *m_previous = nullptr;
        };
    } // DataStructures
} // KML

#include "Node.tcc"

#endif // __NODE_H__
