/*!
 * @file StreamingHistogram.tcc
 * @brief Contains the templated implementation for the abstract Histogram class.
 * 
 * @ Reference: https://jmlr.csail.mit.edu/papers/volume11/ben-haim10a/ben-haim10a.pdf
 */
#include <float.h>      // DBL_MAX
#include <limits>       // numeric_limits

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        StreamingHistogram<T>::StreamingHistogram(const size_t& numBins, const size_t& windowSize):
            IStreamingHistogram<T>(numBins, windowSize)
        {
            // Do nothing.
        }

        template<typename T>
        StreamingHistogram<T>::~StreamingHistogram() 
        {
            reset();
        }

        template<typename T>
        void StreamingHistogram<T>::update(const T& item)
        {
            IBin<T> *l_bin = new IBin<T>(item, item, 1);

            // Histogram is empty, just insert.
            if(0 == this->m_historyCount)
            {
                std::cout << "First item = " << item << std::endl;
                this->m_bins.push_back(l_bin);
                this->m_historyCount++;
                return;
            }

            // Binary search to find insert index.
            size_t l_low = 0;
            size_t l_high = this->m_bins.size();
            size_t l_index = (l_low + l_high) / 2;

            while(l_low < l_high)
            {
                if(*this->m_bins[l_index] < *l_bin) l_low = l_index + 1;
                else l_high = l_index;
                l_index = (l_low + l_high) / 2;
            }

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

            // Need to ensure that the number of bins is always at m_numBins.
            if (this->m_bins.size() > this->m_numBins) this->merge();

            this->m_historyCount++;
        }

        template<typename T>
        void StreamingHistogram<T>::merge()
        {
            double l_minDiff = std::numeric_limits<double>::max();
            double l_minIndex = this->m_bins.size();
            double l_diff = 0.0;
            size_t l_index = 0;

            // Get pair of bins that have the smallest bin width difference.
            // This assumes bins are sorted. This is O(m_numBins).
            for(auto it = this->m_bins.begin(); it < this->m_bins.end() - 1; it++)
            {
                l_diff = (*it++)->m_right - (*it)->m_right;
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
        }

        template<typename T>
        void StreamingHistogram<T>::reset()
        {
            this->m_bins.clear();
            this->m_historyCount = 0;
        }

        template<typename T>
        bool StreamingHistogram<T>::empty() const
        {
            return this->m_bins.size() == 0;
        }

        template<typename T>
        bool StreamingHistogram<T>::full() const
        {
            return !this->empty();
        }

        template<typename T>
        size_t StreamingHistogram<T>::size() const
        {
            return this->m_bins.size();
        }
    } // DataStructures
} // KML
