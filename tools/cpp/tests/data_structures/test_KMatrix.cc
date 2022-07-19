// unittest_k_matrix

#include <vector>
#include <gtest/gtest.h>
#include "KMatrix.h"
#include <iostream>

using KML::DataStructures::KMatrix;

class KMatrixTest : public::testing::Test
{
    public:
        KMatrix *km;
        size_t m_numRows = 2;
        size_t m_numCols = 3;

        KMatrixTest()
        {
            km = new KMatrix(m_numRows, m_numCols);
            /* KMatrix v = KMatrix::Ones(4, 4); */
        }
};

TEST_F(KMatrixTest, TestSize)
{
    EXPECT_EQ(m_numRows, km->rows());
    EXPECT_EQ(m_numCols, km->cols());
}
