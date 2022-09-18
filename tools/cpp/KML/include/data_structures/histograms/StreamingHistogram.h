/*!
 * @file StreamingHistogram.h
 * @brief Provides an implementation to the histogram interface.
 */
#ifndef __STREAMING_HISTOGRAM_H__
#define __STREAMING_HISTOGRAM_H__

#include <vector>

#include "IStreamingHistogram.h"

namespace KML
{
    namespace DataStructures
    {
        /*! @brief A Ben-Haim implementation to the Streaming Histogram problem. */
        template<typename T = double>
        class StreamingHistogram : public IStreamingHistogram<T>
        {
            public:
                /*!
                 * Default Default Constructor.
                 * @param  numBins Number of bins to use in histogram.
                 * @param  windowSize Number of items to maintain in history.
                 */
                explicit StreamingHistogram(
                        const size_t& numBins, 
                        const size_t& windowSize);

                /*!
                 * @brief Destructor.
                 */
                virtual ~StreamingHistogram();

                /*!
                 * @brief  Takes a single item and updates the deriving class.
                 * @param  item The item used to update deriving class.
                 */
                virtual void update(const T& item) override;

                /*!
                 * @brief Merge the two closest bins based off of bin width.
                 */
                void merge();

                /*!
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

                /*!
                 * @brief Determine if the Linked List is full.
                 */
                virtual bool full() const override;

                /*!
                 * @brief Determine if the Linked List is empty.
                 */
                virtual bool empty() const override;

                /*!
                 * @brief Retrieve the current number of nodes in the list.
                 */
                virtual size_t size() const override;

                /*!
                 * @brief Completely reset the linked list.
                 */
                virtual void reset() override;
        }; // StreamingHistogram
    } // DataStructures
} // KML

#include "StreamingHistogram.tcc"

#endif // __STREAMING_HISTOGRAM_H__
