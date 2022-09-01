#distutils: language = c++
from libc.stdint cimport uint64_t

cdef extern from "StreamingMean.cc":
    pass

cdef extern from "StreamingVariance.cc":
    pass

cdef extern from "StreamingVariance.h" namespace "KML::Statistics":
    cdef cppclass StreamingVariance:
        StreamingVariance(uint64_t) except +
        void update(double) except +
        double evaluate() except +
