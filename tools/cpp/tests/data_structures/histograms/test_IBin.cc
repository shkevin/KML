// unittest_histogram_bin

#include <vector>
#include <gtest/gtest.h>
#include "IBin.h"
#include <iostream>

using KML::DataStructures::IBin;

class IBinTest : public::testing::Test
{
    public:
        IBin<double> *sh;
        size_t m_numBins = 5;
        size_t m_windowSize = 2;
};

TEST_F(IBinTest, TestConstruction)
{
    sh = new IBin<double>(0, 1, 1);
}

TEST_F(IBinTest, TestEqual)
{
    sh = new IBin<double>(0, 1, 1);
    IBin<double> *other = new IBin<double>(0, 1, 1);
    EXPECT_EQ(*sh, *other);
}

TEST_F(IBinTest, TestPlusSorted)
{
    IBin<double> add = IBin<double>(0, 1, 1) + IBin<double>(0, 2, 1);

    // Test the counts added.
    EXPECT_EQ(add.m_count, 2);

    // Test that the bin edges were correctly set.
    EXPECT_EQ(add.m_left, 0);
    EXPECT_EQ(add.m_right, 2);
}

TEST_F(IBinTest, TestPlusUnsorted)
{
    IBin<double> add = IBin<double>(1, 2, 1) + IBin<double>(0, 1, 1);

    // Test the counts added.
    EXPECT_EQ(add.m_count, 2);

    // Test that the bin edges were correctly set.
    EXPECT_EQ(add.m_left, 0);
    EXPECT_EQ(add.m_right, 2);
}

TEST_F(IBinTest, TestLessThan)
{
    IBin<double> lhs = IBin<double>(0, 1, 1);
    IBin<double> rhs = IBin<double>(1, 2, 1);
    EXPECT_TRUE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
}
