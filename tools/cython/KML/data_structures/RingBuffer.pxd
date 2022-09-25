#distutils: language = c++
from libc.stdint cimport uint64_t
from libcpp cimport bool


cdef extern from "RingBuffer.h" namespace "KML::DataStructures":
    cdef cppclass RingBuffer[T]:
        RingBuffer(uint64_t) except +
        void update(const T&) except +
        T pop() except +
        void reset() except +
        bool empty() except +
        bool full() except +
        size_t size() except +
