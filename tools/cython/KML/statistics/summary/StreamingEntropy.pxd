#distutils: language = c++
from libc.stdint cimport uint64_t

cdef extern from "Utils.cc":
    pass

cdef extern from "StreamingEntropy.cc":
    pass

cdef extern from "StreamingEntropy.h" namespace "KML::Statistics":
    cdef cppclass StreamingEntropy:
        StreamingEntropy(uint64_t, uint64_t) except +
        void update(double) except +
        double evaluate() except +
