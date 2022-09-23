/*!
 * @file StreamingHistogram.tcc
 * @brief Contains the templated implementation for the abstract Histogram class.
 *
 * This histogram is based off of the Ben-Haim and Tom-Tov histogram in the provided reference.
 * 
 * @ Reference: https://jmlr.csail.mit.edu/papers/volume11/ben-haim10a/ben-haim10a.pdf
 */
#include <float.h>      // DBL_MAX
#include <limits>       // numeric_limits
#include <algorithm>    // std::replace

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        StreamingHistogram<T>::StreamingHistogram(const size_t& numBins, const size_t& windowSize, 
                const DecayType decay): IStreamingHistogram<T>(numBins, windowSize, decay)
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
            IBin<T> *l_bin = new IBin<T>(item, item, 1);
            size_t l_index = 0;

            // Histogram is empty, just insert.
            if(0 == this->m_historyCount) this->m_bins.push_back(l_bin);
            else
            {
                // Get the bin index where the new bin should go.
                l_index = this->binSearch(*l_bin);

                // Item is past right-most bin.
                if(l_index == this->m_bins.size()) this->m_bins.push_back(l_bin);
                else
                {
                    // Increment the bin counter if item is at index bin.
                    if(item >= this->m_bins[l_index]->m_left)
                    {
                        this->m_bins[l_index]->m_count++;
                    }
                    else
                    {
                        this->m_bins.insert(this->m_bins.begin() + l_index, l_bin);
                    }
                }
            }

            // Update window index and count normalizations.
            this->m_window->push_back(l_index);
            this->updateNormalizer();
            this->m_historyCount++;
            this->decayCounts(); // Call decay before merging.

            // Need to ensure that the number of bins is always at m_numBins.
            if (this->m_bins.size() > this->m_numBins) 
            {
                size_t l_mergedIndex = this->merge();

                // Need to re-update the window of indices with the merged index.
                // This will keep the window aligned with indices that have been merged.
                if(DecayType::WINDOW == this->m_decay)
                {
                    for(auto it = this->m_window->begin(); it < this->m_window->end(); it++)
                    {
                        if(*it == (l_mergedIndex + 1)) *it = l_mergedIndex;
                    }
                }
            }
        }

        template<typename T>
        size_t StreamingHistogram<T>::merge()
        {
            double l_minDiff = std::numeric_limits<double>::max();
            double l_minIndex = this->m_bins.size();
            size_t l_index = 0;

            // Get pair of bins that have the smallest bin width difference.
            // This assumes bins are sorted. This is O(m_numBins).
            for(auto it = this->m_bins.begin(); it < this->m_bins.end() - 1; it++)
            {
                double l_diff = (*it++)->m_right - (*it)->m_right;
                if(l_diff < l_minDiff)	
                {
                    l_minDiff = l_diff;
                    l_minIndex = l_index;
                }

                l_index++;
            }

            // Get next right bin to merge into left.
            IBin<T> l_toMerge = *this->m_bins[l_minIndex + 1];
            this->m_bins.erase(this->m_bins.begin() + l_minIndex + 1);
            *this->m_bins[l_minIndex] += l_toMerge;

            return l_minIndex;
        }
    } // DataStructures
} // KML
