#distutils: language = c++
from collections.abc import Iterable

cdef class PyWindowedFAME:
    cdef WindowedFAME* c_FM

    def __init__(self, step_size=0.1, epsilon=0.0):
        pass

    def __cinit__(self, step_size=0.1, epsilon=0.0):
        self.c_FM = new WindowedFAME(step_size, epsilon)

    def update(self, observation):
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_FM.update(o)
        else:
            self.c_FM.update(observation)

    def evaluate(self):
        return self.c_FM.evaluate()

    def __dealloc__(self):
        del self.c_FM
