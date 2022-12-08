/*!
 * @file  StreamingEntropy.h
 * @brief Provides the declarations for the StreamingEntropy calculation.
 *
 * The StreamingEntropy computes the entropy of a data stream. This class
 * can work on all the data or a window of the data.  
 * 
 */
#ifndef __STREAMING_ENTROPY_H__
#define __STREAMING_ENTROPY_H__

#include "IStreamingStatistic.h"
#include "StreamingHistogram.h"

namespace KML
{
    namespace Statistics
    {
        using KML::DataStructures::StreamingHistogram;

        /*! @brief A StreamingEntropy class for calculating the entropy of
         *  a datastream.
         */
        class StreamingEntropy : public IStreamingStatistic<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
                 * @param windowSize The window size to calculate the streaming entropy.
                 *        This window size defaults to a window size of 100.
                 * @param numBins Number of bins to approximate counts with.
                 */
                explicit StreamingEntropy(const size_t& windowSize = 100,
                                          const size_t& numBins = 0);

                /*!
                 * @copydoc IStreamingStatistic::update()
                 */
                void update(const double& observation) override;
                using IStreamingStatistic<double>::update;

                /*!
                 * @copydoc IStreamingStatistic::evaluate()
                 */
                double evaluate() const override;
                using IStreamingStatistic<double>::evaluate;

            private:
                /*!
                 * @brief Increment the entropy with the given bin index.
                 */
                void increment(const size_t& index);

                /*!
                 * @brief Decrement the entropy with the given bin index.
                 */
                void decrement(const size_t& index);

                /*!
                 * @brief Underlying histogram to approximate probabilities and 
                 *        counts for seen observations.
                 */
                StreamingHistogram<double>* m_histogram = nullptr;

                /*!
                 * @brief Variable holding the current calculated entropy.
                 */
                double m_entropy = 0.0;
        };
    }  // namespace Statistics
}  // namespace KML

#endif  // __STREAMING_ENTROPY_H__
