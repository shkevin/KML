#distutils: language = c++
from libc.stdint cimport uint64_t


cdef extern from "WindowedFAME.cc":
    pass

cdef extern from "WindowedFAME.h" namespace "KML::Statistics":
    cdef cppclass WindowedFAME:
        WindowedFAME(double, double) except +
        void update(double) except +
        double evaluate() except +
