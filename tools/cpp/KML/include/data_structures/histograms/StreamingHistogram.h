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
                 * @param  decay Which decay type to use. Defaults to window.
                 */
                explicit StreamingHistogram(
                    const size_t& numBins, const size_t& windowSize,
                    const DecayType decay = DecayType::WINDOW);

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
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

            private:
                /*!
                 * @brief Merge the two closest bins based off of bin width. This
                 *        function will return the index of the merged item.
                 */
                size_t merge();
        };
    }  // namespace DataStructures
}  // namespace KML

#include "StreamingHistogram.tcc"

#endif  // __STREAMING_HISTOGRAM_H__
