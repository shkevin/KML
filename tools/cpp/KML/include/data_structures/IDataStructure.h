/*!
 * @file  IDataStructure.h
 * @brief Provides interface for common data structures.
 *
 * The data structure interface is supposed to represent any
 * KML common data structure. Every data structure algorithm should 
 * inherit from this interface.
 */
#ifndef __DATA_STRUCTURE_H__
#define __DATA_STRUCTURE_H__

#include <cstdint>
#include <vector>

namespace KML
{
    namespace DataStructures
    {
        /*! @brief An Abstract interface for data structures. */
        template<typename T = double>
        class IDataStructure
        {
            public:
                /*!
                 * @brief   IDataStructure Constructor.
                 * @details Constructor for every data structure.
                 * @param   windowSize Window size of number of items held in memory (range [0,..)).
                 */
                explicit IDataStructure(const size_t& windowSize);

                /*!
                 * @brief  Takes a single item and updates the deriving class.
                 * @param  item The item used to update deriving class.
                 */
                virtual void update(const T& item) = 0;

                /*!
                 * @brief  Takes in a list of one or more items to update 
                 *         the deriving class.
                 * @param  items List of items to update deriving class.
                 */
                virtual void update(const std::vector<T>& items);

                /*!
                 * @brief Determine if the Linked List is full.
                 */
                virtual bool full() const = 0;

                /*!
                 * @brief Determine if the Linked List is empty.
                 */
                virtual bool empty() const = 0;

                /*!
                 * @brief Retrieve the current number of nodes in the list.
                 */
                virtual size_t size() const = 0;

                /*!
                 * @brief Completely reset the linked list.
                 */
                virtual void reset() = 0;

                /*!
                 * @brief The current window size.
                 */
                size_t m_windowSize;

                /*!
                 * @brief The number of items seen by deriving class.
                 */
                size_t m_historyCount = 0;
        };
    }  // namespace DataStructures
}  // namespace KML

#include "IDataStructure.tcc"

#endif  // __DATA_STRUCTURE_H__
