#distutils: language = c++
from libc.stdint cimport uint64_t

cdef extern from "RingBuffer.tcc":
    pass

cdef extern from "RingBuffer.h" namespace "KML::DataStructures":
    cdef cppclass RingBuffer[T]:
        RingBuffer(uint64_t) except +
