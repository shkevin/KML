#ifndef __STREAMING_STATISTIC_H__
#define __STREAMING_STATISTIC_H__

#include <cstdint>
#include <vector>
#include <deque>

namespace KML 
{
    namespace Statistics
    {
        template<typename T = double>
        class IStreamingStatistic
        {
            public:
                IStreamingStatistic(const uint64_t windowSize);

                virtual ~IStreamingStatistic();

                virtual void update(const T& observation) = 0;

                virtual void update(const std::vector<T>& observations);

                virtual double evaluate() = 0;

                virtual std::deque<T>* getWindow();

            protected:
                std::deque<T>* m_window;

                uint64_t m_windowSize;

                uint64_t m_historyCount;
        };
    }
}

#include "statistics/IStreamingStatistic.tcc"

#endif // __STREAMING_STATISTIC_H__
