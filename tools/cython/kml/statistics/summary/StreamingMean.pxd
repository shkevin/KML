#distutils: language = c++
from libc.stdint cimport uint64_t


cdef extern from "StreamingMean.cc":
    pass

cdef extern from "StreamingMean.h" namespace "KML::Statistics":
    cdef cppclass StreamingMean:
        StreamingMean(uint64_t) except +
        void update(double) except +
        double evaluate() except +
