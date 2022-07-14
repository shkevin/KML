// unittest_windowed_fame

#include <gtest/gtest.h>
#include "WindowedFAME.h"
#include <vector>

using KML::Statistics::WindowedFAME;

class WindowedFAMETest : public ::testing::Test
{
    public:
        WindowedFAME* fm;

        WindowedFAMETest()
        {
            fm = new WindowedFAME(0.1, 0.3);
        }
};

TEST_F(WindowedFAMETest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, fm->evaluate());
}

TEST_F(WindowedFAMETest, TestMedianConstant)
{
    std::vector<double> data{10, 10, 10};
    fm->update(data);
    EXPECT_FLOAT_EQ(10.0, fm->evaluate());
}
