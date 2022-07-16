#distutils: language = c++
from collections.abc import Iterable

cdef class PyLinkedList:
    cdef LinkedList[float] *c_LL

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_LL = new LinkedList[float](window_size)

    def update(self, item):
        if isinstance(item, Iterable):
            for i in item:
                self.c_LL.update(i)
        else:
            self.c_LL.update(item)

    def pop(self):
        return self.c_LL.pop()

    def reset(self):
        self.c_LL.reset()

    def empty(self):
        return self.c_LL.empty()

    def full(self):
        return self.c_LL.full()

    def size(self):
        return self.c_LL.size()

    # def __dealloc__(self):
    #     del self.c_LL
