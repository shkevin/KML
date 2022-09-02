# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming variance wrapper module for C++.

This module is used to wrap the C++ Streaming variance implemtation.

Example:

	```python
    from KML.statistics.summary.StreamingVariance import PyStreamingVariance

    sv = PyStreamingVariance(5)
    sv.update(list(range(1, 11)))
    print(sv.evaluate())
	```
"""
from collections.abc import Iterable


cdef class PyStreamingVariance:
    """Class containing the Streaming variance implementation in Cython.

    Streaming variance wrapper for the C++ StreamingVariance class. This code contains
    the public interface usage for the streaming variance statistic.

    Args:
        window_size (int): Desired window size.

    Attributes:
        c_SM (StreamingVariance*) : Pointer to the C++ StreamingVariance implementation.
        window_size (int): Desired window size.
    """
    cdef StreamingVariance* c_SV

    def __init__(self, window_size=None):
        pass

    def __cinit__(self, window_size=None):
        self.c_SV = new StreamingVariance(window_size)

    def update(self, observation):
        """Update the Streaming Variance with the given item.

        Update the streaming Variance with the given item. The window_size
        parameter helps adjust for data drift within the variance calculation.

        Args:
            item (float, Iterable): Item to update iqr.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SV.update(o)
        else:
            self.c_SV.update(observation)

    def evaluate(self):
        """Retrieve the current Streaming Variance value.

        Retrieve the current streaming mean value from the previous items
        updated.

        Returns:
            float: Current Variance value in window.
        """
        return self.c_SV.evaluate()

    def __dealloc__(self):
        del self.c_SV
