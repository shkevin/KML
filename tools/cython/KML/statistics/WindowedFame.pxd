#distutils: language = c++
from libc.stdint cimport uint64_t

cdef extern from "WindowedFame.cc":
    pass

cdef extern from "WindowedFame.h" namespace "KML::Statistics":
    cdef cppclass WindowedFame:
        WindowedFame(double, uint64_t) except +
        void update(double) except +
        double evaluate() except +
