// unittest_streaming_variance

#include <gtest/gtest.h>
#include "statistics/StreamingVariance.h"
#include <vector>
#include <iostream>

using KML::Statistics::StreamingVariance;

class StreamingVarianceTest : public ::testing::Test
{
    public:
        StreamingVariance* sv;

        StreamingVarianceTest()
        {
            sv = new StreamingVariance();
        }
};

// Evaluate with no updates should return 0.0 for mean.
TEST_F(StreamingVarianceTest, TestEmptyEvaluate)
{
    EXPECT_EQ(0.0, sv->evaluate());
}

// Window should be NULL when not initialized with valid size.
TEST_F(StreamingVarianceTest, TestEmptyWindowSize)
{
    EXPECT_EQ(nullptr, sv->getWindow());
}

// Variance should come out to 0.0 when all values are same.
TEST_F(StreamingVarianceTest, TestZeroVarianceCalculation)
{
    std::vector<double> data{1, 1, 1, 1, 1};
    sv->update(data);
    EXPECT_EQ(0.0, sv->evaluate());
}

// Variance should come out to 0.3 for this data.
TEST_F(StreamingVarianceTest, TestVarianceCalculation)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    sv->update(data);
    EXPECT_EQ(0.3, sv->evaluate());
}
