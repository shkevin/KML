// unittest_streaming_histogram

#include <vector>
#include <gtest/gtest.h>
#include "StreamingHistogram.h"
#include <iostream>

using KML::DataStructures::StreamingHistogram;

class StreamingHistogramTest : public::testing::Test
{
    public:
        StreamingHistogram<double> *sh;
        size_t m_numBins = 5;
        size_t m_windowSize = 2;

        StreamingHistogramTest()
        {
            sh = new StreamingHistogram<double>(m_numBins, m_windowSize);
        }
};

TEST_F(StreamingHistogramTest, TestSize)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh->update(l_data);
    EXPECT_EQ(m_numBins, sh->size());
}

TEST_F(StreamingHistogramTest, TestReset)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    sh->update(l_data);
    sh->reset();
    EXPECT_EQ(0, sh->size());
}
