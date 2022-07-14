#distutils: language = c++
from collections.abc import Iterable

cdef class PyStreamingMAD:
    cdef StreamingMAD *c_MAD

    def __init__(self):
        pass

    def __cinit__(self):
        self.c_MAD = new StreamingMAD()

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_MAD.update(o)
        else:
            self.c_MAD.update(observation)

    def evaluate(self):
        return self.c_MAD.evaluate()

    def __dealloc__(self):
        del self.c_MAD
