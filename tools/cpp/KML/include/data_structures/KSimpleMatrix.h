/*!
 * @file  KSimpleMatrix.h
 * @brief Provides the declarations for the simple matrix implementation.
 */
#ifndef __KSIMPLE_MATRIX_H__
#define __KSIMPLE_MATRIX_H__

#include <vector>

namespace KML
{
    namespace DataStructures
    {
        /*! @brief Class containing the simple matrix implementation.*/
        class KSimpleMatrix
        {
            public:
                /*!
                 * @brief Default Constructor.
                 */
                KSimpleMatrix();

                /*!
                 * @brief THIS CONSTRUCTOR NEEDS TO MIMIC EIGEN MATRIXXD CONSTRUCTOR!
                 * This class is simply a place holder for now.
                 */
                KSimpleMatrix(const size_t& numRows, const size_t& numCols);

                /*!
                 * @brief Retrieve the number of rows in KMatrix.
                 */
                size_t rows() const;

                /*!
                 * @brief Retrieve the number of columns in KMatrix.
                 */
                size_t cols() const;

            private:
                /*!
                 * @brief Internal variable to keep track of number of rows.
                 */
                const size_t m_numRows;

                /*!
                 * @brief Internal variable to keep track of number of columns.
                 */
                const size_t m_numCols;
        };
    }  // namespace DataStructures
}  // namespace KML

#endif  // __KSIMPLE_MATRIX_H__
