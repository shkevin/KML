/*!
 * @file Node.cc
 * @brief Contains the templated implementation for the Node data structure class.
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
    }  // namespace DataStructures
}  // namespace KML
