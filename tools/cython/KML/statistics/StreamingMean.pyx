#distutils: language = c++
from collections.abc import Iterable
from KML.statistics.StreamingMean cimport StreamingMean

cdef class PyStreamingMean:
    cdef StreamingMean* c_SM

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_SM = new StreamingMean(window_size)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for _ in observation:
                self.c_SM.update(_)
        else:
            self.c_SM.update(observation)

    def evaluate(self):
        return self.c_SM.evaluate()

    def __str__(self):
        return "Yes"

    def __dealloc__(self):
        del self.c_SM
