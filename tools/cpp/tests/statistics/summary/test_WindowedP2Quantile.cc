// unittest_Windowed_P2Quantile

#include <gtest/gtest.h>
#include "WindowedP2Quantile.h"
#include <vector>

using KML::Statistics::WindowedP2Quantile;

class WindowedP2QuantileTest : public ::testing::Test
{
    public:
        WindowedP2Quantile* l_wp2;

        WindowedP2QuantileTest()
        {
            l_wp2 = new WindowedP2Quantile(0.5, 3);
        }
};

TEST_F(WindowedP2QuantileTest, TestEmptyEvaluate)
{
    EXPECT_EQ(0.0, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestConstantMedian)
{
    std::vector<double> data{10, 10, 10, 10, 10};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(10.0, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestSimpleWindowedMedian)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(1.0, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestSimpleMedian)
{
    l_wp2 = new WindowedP2Quantile(0.5, 10);
    std::vector<double> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(5, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestSimpleQ1)
{
    l_wp2 = new WindowedP2Quantile(0.25, 10);
    std::vector<double> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(3, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestSimpleQ3)
{
    l_wp2 = new WindowedP2Quantile(0.75, 10);
    std::vector<double> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(7, l_wp2->evaluate());
}

TEST_F(WindowedP2QuantileTest, TestWindowedMedian)
{
    l_wp2 = new WindowedP2Quantile(0.5, 5);
    std::vector<double> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    l_wp2->update(data);
    EXPECT_FLOAT_EQ(8, l_wp2->evaluate());
}

