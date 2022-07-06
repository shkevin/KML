// unittest_ring_buffer

#include <vector>
#include <gtest/gtest.h>
#include "data_structures/RingBuffer.h"

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

// Evaluate with no updates should return 0.0.
TEST_F(RingBufferTest, TestEmptyGet)
{
    EXPECT_FLOAT_EQ(0.0, rb->get());
}

TEST_F(RingBufferTest, TestCircularSize)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    /* rb->update(l_data); */
    for(auto i = l_data.begin(); i < l_data.end(); i++)
    {
        rb->update(*i);
    }
    EXPECT_EQ(2, rb->size());
}

TEST_F(RingBufferTest, TestCircularGet)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    /* rb->update(l_data); */
    for(auto i = l_data.begin(); i < l_data.end(); i++)
    {
        rb->update(*i);
    }
    // Should return 3 since 3 is now the tail with window size = 2.
    EXPECT_EQ(3, rb->get());
}
