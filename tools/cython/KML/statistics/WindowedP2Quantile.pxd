#distutils: language = c++
from libcpp.vector cimport vector
from libc.stdint cimport uint64_t

cdef extern from "WindowedP2Quantile.cc":
    pass

cdef extern from "StreamingP2Quantile.cc":
    pass

cdef extern from "WindowedP2Quantile.h" namespace "KML::Statistics":
    cdef cppclass WindowedP2Quantile:
        WindowedP2Quantile(double, uint64_t) except +
        void update(double) except +
        double evaluate() except +
