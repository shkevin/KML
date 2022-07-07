/*!
 * @file Node.cc
 * @brief
 */
#include "Node.h"

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        Node<T>::Node(const T& value) : m_value(value)
        {
            // Do nothing
        }
    }
}
