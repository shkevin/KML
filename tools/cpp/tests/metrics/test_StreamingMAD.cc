// unittest_streaming_mad

#include <gtest/gtest.h>
#include "StreamingMAD.h"
#include <vector>

using KML::Metrics::StreamingMAD;

class StreamingMADTest : public ::testing::Test
{
    public:
        StreamingMAD* sm;

        StreamingMADTest()
        {
            sm = new StreamingMAD();
        }
};

TEST_F(StreamingMADTest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, sm->evaluate());
}

TEST_F(StreamingMADTest, TestMADCalculationSimple1)
{
    std::vector<double> data{10, 10};
    sm->update(data);
    EXPECT_FLOAT_EQ(0.0, sm->evaluate());
}

TEST_F(StreamingMADTest, TestMADCalculationSimple2)
{
    std::vector<double> data{2, 1, 1};
    sm->update(data);
    EXPECT_FLOAT_EQ(0.0, sm->evaluate());
}
