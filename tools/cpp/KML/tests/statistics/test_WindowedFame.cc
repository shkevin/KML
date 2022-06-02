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
            fm = new WindowedFame(0.1, 0.3);
        }
};

TEST_F(WindowedFameTest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, fm->evaluate());
}

TEST_F(WindowedFameTest, TestMedianConstant)
{
    std::vector<double> data{10, 10, 10};
    fm->update(data);
    EXPECT_FLOAT_EQ(10.0, fm->evaluate());
}
