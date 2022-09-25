/*!
 * @file  Bin.h
 * @brief Provides an interface for bins used in Histograms.
 */
#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include <iostream>  // For printing

#include "IBin.h"
#include "IDataStructure.h"

namespace KML
{
    namespace DataStructures
    {
        /*! @brief A Bin interface for histograms. */
        template<typename T = double>
        class IBin
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param left The left most edge of the Bin boundary.
                 * @param right the right most edge of the Bin boundary.
                 * @param count The count of items in this Bin.
                 */
                IBin(T left, T right, size_t count);

                /*!
                 * @brief Destructor.
                 */
                virtual ~IBin();

                /*!
                 * @brief Copy Constructor.
                 */
                IBin(const IBin<T>& other);

                /*!
                 * @brief Copy Assignment.
                 */
                IBin<T>& operator=(const IBin<T>& rhs);

                /*!
                 * @brief Move Constructor.
                 */
                IBin(IBin<T>&& other);

                /*!
                 * @brief Move Assignment.
                 */
                IBin<T>& operator=(IBin<T>&& rhs);

                /*!
                 * @brief Addition Operator.
                 */
                IBin<T> operator+(const IBin<T>& other) const;

                /*!
                 * @brief Addition Assignmnet Operator.
                 */
                IBin<T> operator+=(const IBin<T>& other);

                /*!
                 * @brief Less than Operator.
                 */
                bool operator<(const IBin<T>& rhs) const;

                /*!
                 * @brief Equal Operator.
                 */
                bool operator==(const IBin<T>& rhs) const;

                /*!
                 * @brief Print Operator.
                 */
                template<typename F>
                friend std::ostream& operator<<(std::ostream& os,
                                                const IBin<F>& bin);

                /*!
                 * @brief Get the bin count.
                 */
                size_t getCount() const;

                /*!
                 * @brief Left most Bin boundary.
                 */
                T m_left;

                /*!
                 * @brief Right most Bin boundary.
                 */
                T m_right;

                /*!
                 * @brief The count of items in this Bin.
                 */
                size_t m_count;
        };  // IBin
    }       // namespace DataStructures
}  // namespace KML

#include "IBin.tcc"

#endif  // __HISTOGRAM_H__
