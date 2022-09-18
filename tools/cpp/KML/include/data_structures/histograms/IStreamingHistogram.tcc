/*!
 * @file IStreamingHistogram.tcc
 * @brief Contains the templated implementation for the abstract streaming histogram class.
 */
#include <iostream> // For printing

namespace KML
{
    namespace DataStructures
    {
        template<typename T>
        IStreamingHistogram<T>::IStreamingHistogram(const size_t& numBins, 
                const size_t& windowSize): IDataStructure<T>(windowSize), m_numBins(numBins)
        {
            // Do nothing.
        }

        template<typename T>
        std::ostream& operator<<(std::ostream& os, const IStreamingHistogram<T>& hist)
        {
            os << "[";
		    for (int i = 0; i < hist.m_bins.size(); ++i) {
		        os << *hist.m_bins[i];
		        if (i != hist.m_bins.size() - 1)
		            os << ", ";
		    }
		    os << "]\n";
		    return os;
        }
    } // DataStructures
} // KML
