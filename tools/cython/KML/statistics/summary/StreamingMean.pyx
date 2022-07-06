#distutils: language = c++
from collections.abc import Iterable

cdef class PyStreamingMean:
    cdef StreamingMean* c_SM

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_SM = new StreamingMean(window_size)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SM.update(o)
        else:
            self.c_SM.update(observation)

    def evaluate(self):
        return self.c_SM.evaluate()

    def __dealloc__(self):
        del self.c_SM
