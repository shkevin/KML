/*!
 * @file KSimpleMatrix.cc
 * @brief 
 */
#include "KSimpleMatrix.h"

#include <stdexcept>

namespace KML
{
    namespace DataStructures
    {
        KSimpleMatrix::KSimpleMatrix(const size_t& numRows, const size_t& numCols)
            : m_numRows(numRows), m_numCols(numCols)
        {
            throw std::runtime_error("KSimpleMatrix not written! Ensure BUILD_EIGEN ON");
        }

        size_t KSimpleMatrix::rows() const { return m_numRows; }

        size_t KSimpleMatrix::cols() const { return m_numCols; }
    }  // namespace DataStructures
}  // namespace KML
