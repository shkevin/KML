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
            sm = new StreamingMean(2);
        }
};

// Evaluate with no updates should return 0.0 for mean.
TEST_F(StreamingMeanTest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, sm->evaluate());
}

// Mean value should come out to 10 when all values are same.
TEST_F(StreamingMeanTest, TestMeanCalculation)
{
    std::vector<double> data{10, 10};
    sm->update(data);
    EXPECT_FLOAT_EQ(10.0, sm->evaluate());
}

// Mean value should come out to 10 when all values are same.
TEST_F(StreamingMeanTest, TestMeanDriftCalculation)
{
    std::vector<double> data{2, 1, 1};
    sm->update(data);
    EXPECT_FLOAT_EQ(1.0, sm->evaluate());
}
