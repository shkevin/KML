// unittest_k_matrix

#include <vector>
#include <gtest/gtest.h>
#include <iostream>

#include "KMatrix.h"

using KML::DataStructures::KMatrix;

class KMatrixTest : public::testing::Test
{
    public:
        KMatrix km;
        size_t m_numRows = 2;
        size_t m_numCols = 3;

        KMatrixTest()
        {
            /* km = KMatrix(m_numRows, m_numCols); */
            /* km->setOnes(); */
            km = KMatrix::Ones(m_numRows, m_numCols);
        }
};

TEST_F(KMatrixTest, TestSize)
{
    EXPECT_EQ(m_numRows, km.rows());
    EXPECT_EQ(m_numCols, km.cols());
}

TEST_F(KMatrixTest, TestMult)
{
    km * km.transpose();
}

TEST_F(KMatrixTest, TestAdd)
{
    km + km;
}
