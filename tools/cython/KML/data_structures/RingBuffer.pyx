#distutils: language = c++
from collections.abc import Iterable

cdef class PyRingBuffer:
    cdef RingBuffer[float] *c_RB

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_RB = new RingBuffer[float](window_size)

    def update(self, item):
        if isinstance(item, Iterable):
            for i in item:
                self.c_RB.update(i)
        else:
            self.c_RB.update(item)

    def pop(self):
        return self.c_RB.pop()

    def reset(self):
        self.c_RB.reset()

    def empty(self):
        return self.c_RB.empty()

    def full(self):
        return self.c_RB.full()

    def size(self):
        return self.c_RB.size()

    # def __dealloc__(self):
    #     del self.c_RB
