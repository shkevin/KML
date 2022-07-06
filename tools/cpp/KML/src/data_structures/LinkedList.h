/*!
 * @file
 * @brief
 */
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "IDataStructure.h"

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
                virtual void put(const T& item) override;

                /*!
                 * @brief
                 */
                virtual T get() override;

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

        };
    } // DataStructures
} // KML


#endif // __LINKED_LIST_H__
