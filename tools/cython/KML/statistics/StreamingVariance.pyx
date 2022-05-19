#distutils: language = c++
from collections.abc import Iterable
from KML.statistics.StreamingVariance cimport StreamingVariance

cdef class PyStreamingVariance:
    cdef StreamingVariance* c_SV

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_SV = new StreamingVariance(window_size)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SV.update(o)
        else:
            self.c_SV.update(observation)

    def evaluate(self):
        return self.c_SV.evaluate()

    def __dealloc__(self):
        del self.c_SV
