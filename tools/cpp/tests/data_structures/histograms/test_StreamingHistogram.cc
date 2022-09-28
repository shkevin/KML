// unittest_streaming_histogram

#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "IBin.h"
#include "StreamingHistogram.h"

using KML::DataStructures::IBin;
using KML::DataStructures::StreamingHistogram;

class StreamingHistogramTest : public ::testing::Test
{
    public:
        StreamingHistogram<double> *sh;
        size_t m_numBins = 5;
        size_t m_windowSize = 10;

        StreamingHistogramTest() { sh = new StreamingHistogram<double>(m_numBins, m_windowSize); }
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

TEST_F(StreamingHistogramTest, TestCoverageXofY)
{
    IBin<double> l_lhs = IBin<double>(0, 4, 1);
    IBin<double> l_rhs = IBin<double>(1, 3, 1);

    double l_cov = sh->coverage(l_lhs, l_rhs);
    EXPECT_FLOAT_EQ(1.0, l_cov);
}

TEST_F(StreamingHistogramTest, TestCoverageYofX)
{
    IBin<double> l_lhs = IBin<double>(1, 3, 1);
    IBin<double> l_rhs = IBin<double>(0, 4, 1);

    double l_cov = sh->coverage(l_lhs, l_rhs);
    EXPECT_FLOAT_EQ(0.5, l_cov);
}

TEST_F(StreamingHistogramTest, TestDensity)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> l_density = {0.12, 0.1, 0.1, 0.1, 0.1};
    sh->update(l_data);

    size_t i = 0;
    std::vector<double> l_pdf = sh->pdf(true, true);
    for (auto it = l_pdf.begin(); it < l_pdf.end(); it++)
    {
        EXPECT_FLOAT_EQ(*it, l_density[i]);
        i++;
    }
}

TEST_F(StreamingHistogramTest, TestNorm)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> l_norms = {0.6, 0.1, 0.1, 0.1, 0.1};
    sh->update(l_data);

    std::vector<double> l_pdf = sh->pdf(true, false);
    for (size_t i = 0; i < l_pdf.size(); i++)
    {
        EXPECT_FLOAT_EQ(l_pdf[i], l_norms[i]);
    }
}

TEST_F(StreamingHistogramTest, TestCDF)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> l_values = {0.6, 0.7, 0.8, 0.9, 1.0};
    sh->update(l_data);

    std::vector<double> l_cdf = sh->cdf();
    for (size_t i = 0; i < l_cdf.size(); i++)
    {
        EXPECT_FLOAT_EQ(l_cdf[i], l_values[i]);
    }
}

TEST_F(StreamingHistogramTest, TestFullWindowedQuantile)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh = new StreamingHistogram<double>(m_numBins, l_data.size());
    sh->update(l_data);

    double l_expected = 9.2;
    double l_quantile = sh->quantile(l_expected / 10);
    EXPECT_FLOAT_EQ(l_quantile, l_expected);
}

TEST_F(StreamingHistogramTest, TestHalfWindowedQuantile)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh = new StreamingHistogram<double>(m_numBins, l_data.size() / 2);
    sh->update(l_data);

    double l_quantile = sh->quantile(0.8);
    EXPECT_FLOAT_EQ(l_quantile, 9.0);
}

TEST_F(StreamingHistogramTest, TestCounts)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> l_expectedCounts = {6, 1, 1, 1, 1};
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(l_expectedCounts[i], l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestWindowedCounts)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sh = new StreamingHistogram<double>(m_numBins, l_data.size() / 2);
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(1, l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestZeroCenteredCounts)
{
    std::vector<double> l_data = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    sh = new StreamingHistogram<double>(l_data.size(), l_data.size());
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(1, l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestCountsUniformBinnedData)
{
    std::vector<double> l_data = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(2, l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestCountsUniformBinnedFloating)
{
    std::vector<double> l_data = {0.1, 0.1, 0.2, 0.2, 0.3, 0.3, 0.4, 0.4, 0.5, 0.5};
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(2, l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestCountsNormallyBinnedData)
{
    std::vector<double> l_data = {1, 2, 2, 3, 3, 3, 4, 4, 5};
    std::vector<double> l_expectedCounts = {1, 2, 3, 2, 1};
    sh->update(l_data);

    std::vector<size_t> l_counts = sh->binCounts();
    for (size_t i = 0; i < l_counts.size(); i++)
    {
        EXPECT_EQ(l_expectedCounts[i], l_counts[i]);
    }
}

TEST_F(StreamingHistogramTest, TestReport)
{
    std::vector<double> l_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> l_expectedCounts = {6, 1, 1, 1, 1};
    sh->update(l_data);

    std::map<std::pair<double, double>, size_t> l_report = sh->report();
    size_t l_index = 0;
    for (auto i = l_report.begin(); i != l_report.end(); i++)
    {
        EXPECT_EQ(l_expectedCounts[l_index], (*i).second);
        /* std::cout << "(" << (*i).first.first << ", " << (*i).first.second << ") = " << (*i).second << std::endl; */
        l_index++;
    }
}
