#distutils: language = c++
from KML.statistics.StreamingMean cimport StreamingMean

cdef class PyStreamingMean:
    cdef StreamingMean* c_SM

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_SM = new StreamingMean(window_size)

    def update(self, observation):
        return None

    def evaluate(self):
        return self.c_SM.evaluate()

    def __str__(self):
        return "Yes"

    def __dealloc__(self):
        del self.c_SM
