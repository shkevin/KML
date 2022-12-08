#distutils: language = c++
from libc.stdint cimport uint64_t
from libcpp.vector cimport vector


cdef extern from "StreamingP2Quantile.cc":
    pass

cdef extern from "StreamingP2Quantile.h" namespace "KML::Statistics":
    cdef cppclass StreamingP2Quantile:
        StreamingP2Quantile(double) except +
        void update(double) except +
        double evaluate() except +
