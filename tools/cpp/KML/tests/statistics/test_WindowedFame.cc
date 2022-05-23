// unittest_windowed_fame

#include <gtest/gtest.h>
#include "statistics/WindowedFame.h"
#include <vector>

using KML::Statistics::WindowedFame;

class WindowedFameTest : public ::testing::Test
{
    public:
        WindowedFame* fm;

        WindowedFameTest()
        {
            fm = new WindowedFame(0.0, 2);
        }
};

// Evaluate with no updates should return 0.0 for median.
TEST_F(WindowedFameTest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, fm->evaluate());
}

// Median value should come out to 10 when all values are same.
TEST_F(WindowedFameTest, TestMedianCalculation)
{
    std::vector<double> data{10, 10, 10};
    fm->update(data);
    EXPECT_FLOAT_EQ(10.0, fm->evaluate());
}

// Median value should come out to 10 when all values are same.
TEST_F(WindowedFameTest, TestMedianDriftCalculation)
{
    std::vector<double> data{2, 1, 1};
    fm->update(data);
    EXPECT_FLOAT_EQ(1.0, fm->evaluate());
}
