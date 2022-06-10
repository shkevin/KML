#distutils: language = c++
from collections.abc import Iterable

cdef class PyStreamingP2Quantile:
    cdef StreamingP2Quantile* c_P2

    def __init__(self, quantile=0.5):
        pass

    def __cinit__(self, quantile=0.5):
        self.c_P2 = new StreamingP2Quantile(quantile)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_P2.update(o)
        else:
            self.c_P2.update(observation)

    def evaluate(self):
        return self.c_P2.evaluate()

    def __dealloc__(self):
        del self.c_P2