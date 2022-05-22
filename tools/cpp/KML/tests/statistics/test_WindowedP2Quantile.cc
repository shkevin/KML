// unittest_Windowed_P2Quantile

#include <gtest/gtest.h>
#include "statistics/WindowedP2Quantile.h"
#include <vector>

using KML::Statistics::WindowedP2Quantile;

class WindowedP2QuantileTest : public ::testing::Test
{
    public:
        WindowedP2Quantile* wp2;

        WindowedP2QuantileTest()
        {
            wp2 = new WindowedP2Quantile(0.5, 10);
        }
};

// Evaluate with no updates should return 0.0 for mean.
TEST_F(WindowedP2QuantileTest, TestEmptyEvaluate)
{
    EXPECT_EQ(0.0, wp2->evaluate());
}

// Median should come out to 1.0 for constant 1.
TEST_F(WindowedP2QuantileTest, TestConstantMedian)
{
    std::vector<double> data{10, 10, 10, 10, 10};
    wp2->update(data);
    EXPECT_FLOAT_EQ(10.0, wp2->evaluate());
}

// Variance should come out to 1.0 for this data.
TEST_F(WindowedP2QuantileTest, TestMedian)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    wp2->update(data);
    EXPECT_FLOAT_EQ(1.0, wp2->evaluate());
}
