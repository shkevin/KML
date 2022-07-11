#distutils: language = c++
from libc.stdint cimport uint64_t
from libcpp cimport bool

cdef extern from "LinkedList.h":
    pass

cdef extern from "LinkedList.h" namespace "KML::DataStructures":
    cdef cppclass LinkedList[T]:
        LinkedList(uint64_t) except +
        void update(const T&) except +
        T pop() except +
        void reset() except +
        bool empty() except +
        bool full() except +
        size_t size() except +
