// unittest_streaming_P2Quantile

#include <gtest/gtest.h>
#include "statistics/StreamingP2Quantile.h"
#include <vector>
#include <iostream>

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
    std::vector<double> data{10, 10, 10, 10, 10};
    p2q->update(data);
    EXPECT_FLOAT_EQ(10.0, p2q->evaluate());
}

// Median should come out to 1.0 for this data.
TEST_F(StreamingP2QuantileTest, TestMedianBasic)
{
    std::vector<double> data{1, 1, 1, 2, 2};
    p2q->update(data);
    EXPECT_FLOAT_EQ(1.0, p2q->evaluate());
}

TEST_F(StreamingP2QuantileTest, TestMedianAdvancedUnsorted)
{
    // Unsorted chooses correct median observation.
    std::vector<double> data{5.3, 380.99, 72.3, 0, -5, -20.7, 500};
    p2q->update(data);
    EXPECT_FLOAT_EQ(5.3, p2q->evaluate());
}

TEST_F(StreamingP2QuantileTest, TestMedianAdvancedSorted)
{
    // Sorted chooses left most median observation.
    std::vector<double> data{-20.7, -5, 0, 5.3, 72.5, 380.99, 500};
    p2q->update(data);
    EXPECT_FLOAT_EQ(0, p2q->evaluate());
}
