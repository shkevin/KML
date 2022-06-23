#distutils: language = c++
# from collections.abc import Iterable
# from KML.data_structures.RingBuffer cimport RingBuffer

# cdef class PyRingBuffer:
#     cdef RingBuffer[double]* c_RB

#     def __init__(self, window_size=None):
#         pass

#     def __cinit__(self, window_size=None):
#         self.c_RB = new RingBuffer[double](window_size)

#     def __dealloc__(self):
#         del self.c_SM
