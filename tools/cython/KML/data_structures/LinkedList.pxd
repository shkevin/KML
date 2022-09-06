#distutils: language = c++
from libc.stdint cimport uint64_t
from libcpp cimport bool

"""LinkedList Cython wrapper module for C++.

This module is used to wrap the C++ LinkedList implemtation. This module
specifally uses the float generic template.

Example:

	```python
	from KML.data_structures.LinkedList import PyLinkedList

	LL = PyLinkedList(window_size=5)

    for i in range(5):
        LL.update(i)

    assert LL.size() == 5
	```
"""
cdef extern from "LinkedList.h" namespace "KML::DataStructures":
    cdef cppclass LinkedList[T]:
        LinkedList(uint64_t) except +
        void update(const T&) except +
        T pop() except +
        void reset() except +
        bool empty() except +
        bool full() except +
        size_t size() except +
