#distutils: language = c++
from collections.abc import Iterable
from KML.statistics.WindowedP2Quantile cimport WindowedP2Quantile

cdef class PyWindowedP2Quantile:
    cdef WindowedP2Quantile* c_WP2

    def __init__(self, quantile, window_size=None):
        pass

    def __cinit__(self, quantile, window_size=None):
        self.c_WP2 = new WindowedP2Quantile(quantile, window_size)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_WP2.update(o)
        else:
            self.c_WP2.update(observation)

    def evaluate(self):
        return self.c_WP2.evaluate()

    def __dealloc__(self):
        del self.c_WP2
