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
            wp2 = new WindowedP2Quantile(0.5, 5);
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

// Median should come out to 1.0 for this data.
TEST_F(WindowedP2QuantileTest, TestMedian)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    wp2->update(data);
    EXPECT_FLOAT_EQ(1.0, wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestMedianAdvancedUnsorted)
{
    // Unsorted chooses correct median observation.
    std::vector<double> data{5.3, 380.99, 72.3, 0, -5, -20.7, 500};
    wp2->update(data);
    EXPECT_FLOAT_EQ(-3, wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestMedianAdvancedSorted)
{
    // Sorted chooses left most median observation.
    std::vector<double> data{-20.7, -5, 0, 5.3, 72.5, 380.99, 500};
    wp2->update(data);
    EXPECT_NEAR(1.179, wp2->evaluate(), 0.001);
}
