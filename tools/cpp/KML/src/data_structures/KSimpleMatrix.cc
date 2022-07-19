/*!
 * @file KSimpleMatrix.cc
 * @brief 
 */
#include <stdexcept>

#include "KSimpleMatrix.h"

namespace KML
{
    namespace DataStructures
    {
        KSimpleMatrix::KSimpleMatrix(const size_t numRows, const size_t numCols) :
            m_numRows(numRows), m_numCols(numCols)
        {
            throw std::runtime_error("KSimpleMatrix not written! Ensure BUILD_EIGEN ON");
        }
    } // DataStructures
} // KML
