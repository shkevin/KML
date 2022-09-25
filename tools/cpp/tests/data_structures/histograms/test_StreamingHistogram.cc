// unittest_streaming_histogram

#include <vector>
#include <gtest/gtest.h>
#include "StreamingHistogram.h"
#include "IBin.h"

#include <iostream>

using KML::DataStructures::StreamingHistogram;

class StreamingHistogramTest : public::testing::Test
{
    public:
        StreamingHistogram<double> *sh;
        size_t m_numBins = 5;
        size_t m_windowSize = 5;

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

TEST_F(StreamingHistogramTest, TestPDF)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh->update(l_data);

    std::vector<double> l_pdf = sh->pdf(true, true);
    double l_evenWidth = 1.0 / (double)m_numBins;
    for(auto it = l_pdf.begin(); it < l_pdf.end(); it++)
    {
        EXPECT_FLOAT_EQ(*it, l_evenWidth);
    }
}

TEST_F(StreamingHistogramTest, TestCDF)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh->update(l_data);

    std::vector<double> l_cdf = sh->cdf();
    double l_evenWidth = 1.0 / (double)m_numBins;
    for(size_t i = 0; i < l_cdf.size(); i++)
    {
        EXPECT_FLOAT_EQ(l_cdf[i], (i + 1) * l_evenWidth);
    }
}

TEST_F(StreamingHistogramTest, TestWindowedQuantile)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh = new StreamingHistogram<double>(m_numBins, l_data.size());
    sh->update(l_data);

    double l_quantile = sh->quantile(0.8);
    EXPECT_FLOAT_EQ(l_quantile, 9.2);
}

TEST_F(StreamingHistogramTest, TestCounts)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for(size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(1, l_counts[i]);
    }
}
