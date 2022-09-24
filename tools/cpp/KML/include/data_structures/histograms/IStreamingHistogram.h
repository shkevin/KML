/*!
 * @file  IStreamingHistogram.h
 * @brief Provides an abstract interface for streaming histograms.
 */
#ifndef __ABSTRACT_HISTOGRAM_H__
#define __ABSTRACT_HISTOGRAM_H__

#include <deque>
#include <vector>

#include "IBin.h"
#include "IDataStructure.h"

namespace KML
{
    namespace DataStructures
    {
        /*!
         * @brief Enum containing the histogram count decay types.
         */
        enum DecayType
        {
            WINDOW = 1, /*! Decay type to decrease counts out of window.  */
        };

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
                    const size_t& numBins, const size_t& windowSize = 100,
                    const DecayType decay = DecayType::WINDOW);

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

                /*!
                 * @brief Get the index where the given bin should be inserted.
                 * @param bin The bin to find where to place in histogram.
                 */
                size_t binSearch(const IBin<T> bin) const;

                /*!
                 * @brief Calculate the approximate pdf from the histogram.
                 * @param normalize Get the window normalized counts.
                 * @param density Calculate the density of the histogram.
                 */
                std::vector<double> pdf(const bool normalize = true,
                                        const bool density = true) const;

                /*!
                 * @brief Calcualte the approximate cdf of bin counts.
                 * @param normalize Normalize the counts by the window.
                 */
                std::vector<double> cdf(const bool normalize = true) const;

                /*!
                 * @brief Get the bin edge corresponding to the pth percentile.
                 * @param qtile Which quantile to estimate.
                 */
                T quantile(const double qtile) const;

                /*!
                 * @brief Retrieve the counts for each bin.
                 */
                std::vector<size_t> binCounts() const;

                /*!
                 * @brief Print Operator.
                 */
                template<typename F>
                friend std::ostream& operator<<(
                    std::ostream& os, const IStreamingHistogram<F>& hist);

            protected:
                /*!
                 * @brief Update the value used in normalizing the counts.
                 */
                void updateNormalizer();

                /*!
                 * @brief Decrease the count of an item outside of window.
                 */
                void decayCounts();

                /*!
                 * @brief The value to normalize the counts in the histogram.
                 */
                double m_normalizer = 0.0;

                /*!
                 * @brief Vector of Bins in the Histogram.
                 */
                std::vector<IBin<T>*> m_bins;

                /*!
                 * @brief Window buffer containing m_windowSize indices of bins. This
                 *        is only used if the decay type is set to WINDOW.
                 */
                std::deque<size_t>* m_window = nullptr;

                /*!
                 * @brief Number of bins maintained by this Histogram.
                 */
                const size_t m_numBins;

                /*!
                 * @brief Decay type to decrease histogram counts.
                 */
                const DecayType m_decay;
        };
    }  // namespace DataStructures
}  // namespace KML

#include "IStreamingHistogram.tcc"

#endif  // __ABSTRACT_HISTOGRAM_H__
