// unittest_streaming_entropy

#include <gtest/gtest.h>
#include "StreamingEntropy.h"
#include <vector>
#include <cmath>

using KML::Statistics::StreamingEntropy;

class StreamingEntropyTest : public ::testing::Test
{
    public:
        StreamingEntropy* se;
        size_t m_windowSize = 10;
        size_t m_numBins = 10;

        StreamingEntropyTest()
        {
            se = new StreamingEntropy(m_windowSize, m_numBins);
        }
};

TEST_F(StreamingEntropyTest, TestEmptyEvaluate)
{
    EXPECT_FLOAT_EQ(0.0, se->evaluate());
}

TEST_F(StreamingEntropyTest, TestUniformEntropyWithDecrement)
{
    std::vector<double> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    se->update(data);
    EXPECT_FLOAT_EQ(std::log2(m_numBins), se->evaluate());
}

TEST_F(StreamingEntropyTest, TestUniformEntropyWithoutDecrement)
{
    se = new StreamingEntropy(m_windowSize, 5);
    std::vector<double> data = {1, 2, 3, 4, 5};
    se->update(data);
    EXPECT_FLOAT_EQ(std::log2(5), se->evaluate());
}

TEST_F(StreamingEntropyTest, TestUniformEntropyDoubleBins)
{
    // This should be binned with 5 bins.
    std::vector<double> data = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    se->update(data);
    EXPECT_FLOAT_EQ(std::log2(5), se->evaluate());
}

