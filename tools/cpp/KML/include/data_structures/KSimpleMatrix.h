/*!
 * @file KSimpleMatrix.h
 * @brief
 */
#ifndef __KSIMPLE_MATRIX_H__
#define __KSIMPLE_MATRIX_H__

#include <vector>

namespace KML
{
    namespace DataStructures
    {
        class KSimpleMatrix
        {
            public:
                /*!
                 * @brief THIS CONSTRUCTOR NEEDS TO MIMIC EIGEN MATRIXXD CONSTRUCTOR!
                 * This class is simply a place holder for now.
                 */
                KSimpleMatrix(const size_t numRows, const size_t numCols);

                /*!
                 * @brief
                 */
                size_t rows() const;

                /*!
                 * @brief
                 */
                size_t cols() const;

            private:
                /*!
                 * @brief
                 */
                const size_t m_numRows;

                /*!
                 * @brief
                 */
                const size_t m_numCols;
        };
    }
}

#endif // __KSIMPLE_MATRIX_H__
