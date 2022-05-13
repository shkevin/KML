#ifndef __STREAMING_MEAN_H__
#define __STREAMING_MEAN_H__

#include "IStreamingStatistic.h"

namespace KML
{
    namespace Statistics
    {
        class StreamingMean : public IStreamingStatistic<double>
        {
            public:
                StreamingMean(const uint64_t windowSize = 0);

                ~StreamingMean();

                using IStreamingStatistic<double>::update;
                virtual void update(const double& observation);

                using IStreamingStatistic<double>::evaluate;
                virtual double evaluate();

            protected:
                double m_sum;
        };
    }
}

#endif // __STREAMING_MEAN_H
