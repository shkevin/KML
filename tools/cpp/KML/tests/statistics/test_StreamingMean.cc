// unittest_streaming_means

#include <gtest/gtest.h>
#include "statistics/StreamingMean.h"
#include <vector>

using KML::Statistics::StreamingMean;

class StreamingMeanTest : public ::testing::Test
{
    public:
        StreamingMean* sm;

        StreamingMeanTest()
        {
            sm = new StreamingMean(10);
        }
};

// Evaluate with no updates should return 0.0 for mean.
TEST_F(StreamingMeanTest, TestEmptyEvaluate)
{
    EXPECT_EQ(0.0, sm->evaluate());
}

// Window should be NULL when not initialized with valid size.
TEST_F(StreamingMeanTest, TestEmptyWindowSize)
{
    EXPECT_EQ(nullptr, sm->getWindow());
}

// Mean value should come out to 10 when all values are same.
TEST_F(StreamingMeanTest, TestMeanCalculation)
{
    std::vector<double> data{10, 10, 10};
    sm->update(data);
    EXPECT_EQ(10.0, sm->evaluate());
}
