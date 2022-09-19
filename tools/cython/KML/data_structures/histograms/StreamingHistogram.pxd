#distutils: language = c++
from libcpp.vector cimport vector
from libc.stdint cimport uint64_t
from libcpp cimport bool

cdef extern from "IStreamingHistogram.h" namespace "KML::DataStructures":
    cpdef enum DecayType:
        WINDOW=1

cdef extern from "StreamingHistogram.h" namespace "KML::DataStructures":
    cdef cppclass StreamingHistogram[T]:
        StreamingHistogram(uint64_t, uint64_t, DecayType) except +
        void update(const T&) except +
        vector[double] pdf(bool, bool) except +
        vector[double] cdf(bool) except +
        T quantile(double) except +
        vector[uint64_t] binCounts() except +
        void reset() except +
        bool empty() except +
        bool full() except +
        size_t size() except +
