/*!
 * @file  IStreamingHistogram.h
 * @brief Provides an abstract interface for histograms.
 */
#ifndef __ABSTRACT_HISTOGRAM_H__
#define __ABSTRACT_HISTOGRAM_H__

#include <vector>

#include "IDataStructure.h"
#include "IBin.h"

namespace KML
{
    namespace DataStructures
    {
        /*! @brief An Abstract Histogram interface for streaming histograms.*/
        template<typename T = double>
        class IStreamingHistogram : public IDataStructure<T>
        {
            public:
                /*!
                 * Default Constructor.
                 * @param  numBins Number of bins the Histogram should maintain.
                 */
                explicit IStreamingHistogram(
                        const size_t& numBins, 
                        const size_t& windowSize=100);

                /*!
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

                /*!
                 * @brief Print Operator.
                 */
                template<typename F>
                friend std::ostream& operator<<(std::ostream& os, 
                        const IStreamingHistogram<F>& hist);

            protected:
                /*!
                 * @brief Vector of Bins in the Histogram.
                 */
                std::vector<IBin<T> *> m_bins;

                /*!
                 * @brief Number of bins maintained by this Histogram.
                 */
                const size_t m_numBins;
        }; // IStreamingHistogram
    } // DataStructures
} // KML

#include "IStreamingHistogram.tcc"

#endif // __ABSTRACT_HISTOGRAM_H__
