/*!
 * @file StreamingHistogram.tcc
 * @brief Contains the templated implementation for the abstract Histogram class.
 *
 * This histogram is based off of the Ben-Haim and Tom-Tov histogram in the provided reference.
 * 
 * @ Reference: https://jmlr.csail.mit.edu/papers/volume11/ben-haim10a/ben-haim10a.pdf
 */
#include <float.h>  // DBL_MAX

#include <algorithm>  // std::replace
#include <limits>     // numeric_limits

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        StreamingHistogram<T>::StreamingHistogram(const size_t& numBins, const size_t& windowSize,
                                                  const DecayType& decay)
            : IStreamingHistogram<T>(numBins, windowSize, decay)
        {
            // Do nothing.
        }

        template<typename T>
        StreamingHistogram<T>::~StreamingHistogram()
        {
            this->reset();
        }

        template<typename T>
        void StreamingHistogram<T>::update(const T& item)
        {
            // Add the bin where it should belong.
            this->add(item);

            // Need to ensure that the number of bins is always <= m_numBins.
            if (this->getCurrentNumBins() > this->getNumBins())
            {
                size_t l_mergedIndex = merge();

                // Need to re-update the window of indices with the merged index.
                // This will keep the window aligned with indices that have been merged.
                if (DecayType::WINDOW == this->getDecayType())
                {
                    auto window = this->getWindow();
                    for (auto it = window->begin(); it < window->end(); it++)
                    {
                        if (*it == (l_mergedIndex + 1)) *it = l_mergedIndex;
                    }
                }
            }
        }

        template<typename T>
        size_t StreamingHistogram<T>::merge()
        {
            double l_minDiff = std::numeric_limits<double>::max();
            double l_minIndex = this->getCurrentNumBins();
            size_t l_index = 0;

            // Get pair of bins that have the smallest between bin width difference.
            // This assumes bins are sorted. This is O(m_numBins).
            for (size_t i = 0; i < this->getCurrentNumBins() - 1; i++)
            {
                double l_diff = this->getBin(i + 1)->m_right - this->getBin(i)->m_right;
                if (Utils::definitelyLessThan(l_diff, l_minDiff))
                {
                    l_minDiff = l_diff;
                    l_minIndex = l_index;
                }

                l_index++;
            }

            // Get next right bin to merge into left.
            this->mergeBins(l_minIndex, l_minIndex + 1);

            return l_minIndex;
        }
    }  // namespace DataStructures
}  // namespace KML
