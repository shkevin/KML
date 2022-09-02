#distutils: language = c++
from libcpp.vector cimport vector
from libc.stdint cimport uint64_t

cdef extern from "StreamingP2Quantile.cc":
    pass

cdef extern from "StreamingP2Quantile.h" namespace "KML::Statistics":
    cdef cppclass StreamingP2Quantile:
        StreamingP2Quantile(double) except +
        void update(double) except +
        double evaluate() except +
