/*!
 * @file IDataStructure.tcc
 * @brief Contains the templated implementation for the abstract data structure class.
 */
#include <stdexcept>

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        IDataStructure<T>::IDataStructure(const size_t& windowSize)
            : m_windowSize(windowSize)
        {
            // Do nothing.
        }

        template<typename T>
        void IDataStructure<T>::update(const std::vector<T>& items)
        {
            for (auto it = items.begin(); it != items.end(); it++)
            {
                this->update(*it);
            }
        }
    }  // namespace DataStructures
}  // namespace KML
