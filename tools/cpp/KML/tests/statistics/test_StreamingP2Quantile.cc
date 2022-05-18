// unittest_streaming_P2Quantile

#include <gtest/gtest.h>
#include "statistics/StreamingP2Quantile.h"
#include <vector>

using KML::Statistics::StreamingP2Quantile;

class StreamingP2QuantileTest : public ::testing::Test
{
    public:
        StreamingP2Quantile* p2q;

        StreamingP2QuantileTest()
        {
            p2q = new StreamingP2Quantile(0.5);
        }
};

// Evaluate with no updates should return 0.0 for mean.
TEST_F(StreamingP2QuantileTest, TestEmptyEvaluate)
{
    EXPECT_EQ(0.0, p2q->evaluate());
}

// Window should be NULL when not initialized with valid size.
TEST_F(StreamingP2QuantileTest, TestEmptyWindowSize)
{
    EXPECT_EQ(nullptr, p2q->getWindow());
}

// Median should come out to 1.0 for constant 1.
TEST_F(StreamingP2QuantileTest, TestConstantMedian)
{
    std::vector<double> data{1, 1, 1, 1, 1};
    p2q->update(data);
    EXPECT_EQ(1.0, p2q->evaluate());
}

// Variance should come out to 1.0 for this data.
TEST_F(StreamingP2QuantileTest, TestMedian)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    p2q->update(data);
    EXPECT_FLOAT_EQ(1.0, p2q->evaluate());
}
