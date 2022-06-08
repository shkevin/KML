#distutils: language = c++
from collections.abc import Iterable
from KML.statistics.StreamingIQR cimport StreamingIQR

cdef class PyStreamingIQR:
    cdef StreamingIQR* c_IQR

    def __init__(self, low=None, high=None, window_size=None):
        pass

    def __cinit__(self, low=None, high=None, window_size=None):
        if low is None or high is None:
           self.c_IQR = new StreamingIQR(window_size)
        else:
           self.c_IQR = new StreamingIQR(low, high, window_size)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_IQR.update(o)
        else:
            self.c_IQR.update(observation)

    def evaluate(self):
        return self.c_IQR.evaluate()

    def __dealloc__(self):
        del self.c_IQR
