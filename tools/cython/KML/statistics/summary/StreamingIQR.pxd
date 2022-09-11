#distutils: language = c++
from libc.stdint cimport uint64_t
from libcpp.vector cimport vector


cdef extern from "StreamingIQR.cc":
    pass

cdef extern from "StreamingP2Quantile.cc":
    pass

cdef extern from "WindowedP2Quantile.cc":
    pass

cdef extern from "StreamingIQR.h" namespace "KML::Statistics":
    cdef cppclass StreamingIQR:
        StreamingIQR(uint64_t) except +
        StreamingIQR(double, double, uint64_t) except +
        void update(double) except +
        double evaluate() except +
