/*!
 * @file  IStreamingHistogram.h
 * @brief Provides an abstract interface for streaming histograms.
 */
#ifndef __ABSTRACT_HISTOGRAM_H__
#define __ABSTRACT_HISTOGRAM_H__

#include <deque>
#include <map>
#include <utility>
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
                 * @brief Default Constructor.
                 * @param numBins Number of bins the Histogram should maintain.
                 * @param windowSize Desired window size of Histogram. This helps with data drift.
                 * @param decay How to decay the counts.
                 */
                explicit IStreamingHistogram(const size_t& numBins, const size_t& windowSize = 100,
                                             const DecayType& decay = DecayType::WINDOW);

                /*!
                 * @brief Copy Constructor.
                 */
                IStreamingHistogram(const IStreamingHistogram<T>& other);

                /*!
                 * @brief Copy Assignment.
                 */
                IStreamingHistogram<T>& operator=(const IStreamingHistogram<T>& rhs);

                /*!
                 * @brief Move Constructor.
                 */
                IStreamingHistogram(IStreamingHistogram<T>&& other);

                /*!
                 * @brief Move Assignment.
                 */
                IStreamingHistogram<T>& operator=(IStreamingHistogram<T>&& rhs);

                /*!
                 * @brief Default Destructor.
                 */
                ~IStreamingHistogram();

                /*!
                 * @copydoc IDataStructure::update()
                 */
                using IDataStructure<T>::update;

                /*!
                 * @brief Determine if the Linked List is full.
                 */
                bool full() const override;

                /*!
                 * @brief Determine if the Linked List is empty.
                 */
                bool empty() const override;

                /*!
                 * @brief Retrieve the current number of nodes in the list.
                 */
                size_t size() const override;

                /*!
                 * @brief Completely reset the linked list.
                 */
                void reset() override;

                /*!
                 * @brief Get the index where the given bin should be inserted.
                 * @param bin The bin to find where to place in histogram.
                 */
                size_t binSearch(const IBin<T>& bin) const;

                /*!
                 * @brief Get the index where the given item should be inserted.
                 * @param item The item to find where to place in histogram.
                 */
                size_t binSearch(const T& item) const;

                /*!
                 * @brief Calculate the approximate pdf from the histogram.
                 * @param normalize Get the window normalized counts.
                 * @param density Calculate the density of the histogram.
                 */
                std::vector<double> pdf(const bool& normalize = true,
                                        const bool& density = true) const;

                /*!
                 * @brief Calcualte the approximate cdf of bin counts.
                 * @param normalize Normalize the counts by the window.
                 */
                std::vector<double> cdf(const bool& normalize = true) const;

                /*!
                 * @brief Get the bin edge corresponding to the pth percentile.
                 * @param qtile Which quantile to estimate.
                 */
                T quantile(const double& qtile) const;

                /*!
                 * @brief Add the given bin to the histogram.
                 * @param item Item to add in histogram.
                 */
                void add(const T& item);

                /*!
                 * @brief Retrieve the counts for each bin.
                 */
                std::vector<size_t> binCounts() const;

                /*!
                 * @brief Retrieve the bin boundaries and bin counts of the histogram.
                 */
                std::map<std::pair<double, double>, size_t> report();

                /*!
                 * @brief Print Operator.
                 */
                template<typename F>
                friend std::ostream& operator<<(std::ostream& os,
                                                const IStreamingHistogram<F>& hist);

                /*!
                 * @brief Decrease the count of an item outside of window.
                 */
                void decayCounts();

                /*!
                 * @brief Get the total number of items across all bins.
                 */
                size_t getTotalCount() const;

                /*!
                 * @brief Get bin at the given index.
                 * @param index Which bin to get from the histogram.
                 */
                IBin<T>* getBin(size_t index) const;

            protected:
                /*!
                 * @brief Get the current window for the histogram.
                 */
                std::deque<size_t>* getWindow() const;

                /*!
                 * @brief
                 */
                void mergeBins(const size_t& lhs, const size_t& rhs);

                /*!
                 * @brief Get the current number of bins in the histogram.
                 */
                size_t getCurrentNumBins() const;

                /*!
                 * @brief Get the current number of bins in the histogram.
                 */
                size_t getNumBins() const;

                /*!
                 * @brief Get the set decay type.
                 */
                DecayType getDecayType() const;

            private:
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

                /*!
                 * @brief Total count of items inside all current bins.
                 */
                size_t m_totalCount = 0;
        };
    }  // namespace DataStructures
}  // namespace KML

#include "IStreamingHistogram.tcc"

#endif  // __ABSTRACT_HISTOGRAM_H__
