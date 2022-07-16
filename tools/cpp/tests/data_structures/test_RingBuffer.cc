// unittest_ring_buffer

#include <vector>
#include <gtest/gtest.h>
#include "RingBuffer.h"

using KML::DataStructures::RingBuffer;

class RingBufferTest : public::testing::Test
{
    public:
        RingBuffer<double> *rb;
        size_t m_windowSize = 2;

        RingBufferTest()
        {
            rb = new RingBuffer<double>(m_windowSize);
        }
};

TEST_F(RingBufferTest, TestEmptyPop)
{
    EXPECT_FLOAT_EQ(0.0, rb->pop());
}

TEST_F(RingBufferTest, TestCircularSize)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    rb->update(l_data);
    EXPECT_EQ(m_windowSize, rb->size());
}

TEST_F(RingBufferTest, TestCircularPop)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    rb->update(l_data);
    // Should return 3 since 3 is now the tail with window size = 2.
    EXPECT_EQ(3, rb->pop());
}
