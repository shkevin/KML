// unittest_linked_list

#include <vector>
#include <gtest/gtest.h>
#include "LinkedList.h"
#include <iostream>

using KML::DataStructures::LinkedList;

class LinkedListTest : public::testing::Test
{
    public:
        LinkedList<double> *ll;
        size_t m_windowSize = 2;

        LinkedListTest()
        {
            ll = new LinkedList<double>(m_windowSize);
        }
};

TEST_F(LinkedListTest, TestEmptyPop)
{
    EXPECT_FLOAT_EQ(0.0, ll->pop());
}

TEST_F(LinkedListTest, TestSize)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    /* ll->update(l_data); */
    for(auto i = l_data.begin(); i < l_data.end(); i++)
    {
        ll->update(*i);
    }
    EXPECT_EQ(m_windowSize, ll->size());
}

TEST_F(LinkedListTest, TestPop)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    /* ll->update(l_data); */
    for(auto i = l_data.begin(); i < l_data.end(); i++)
    {
        ll->update(*i);
    }
    // Should return 3 since 3 is now the head with window size = 2.
    EXPECT_EQ(3, ll->pop());

    // Should have 1 less value after pop.
    EXPECT_EQ(m_windowSize - 1, ll->size());
}

TEST_F(LinkedListTest, TestReset)
{
    std::vector<double> l_data = {1, 2, 3, 4};
    /* ll->update(l_data); */
    for(auto i = l_data.begin(); i < l_data.end(); i++)
    {
        ll->update(*i);
    }
    ll->reset();
    EXPECT_EQ(0, ll->size());
}
