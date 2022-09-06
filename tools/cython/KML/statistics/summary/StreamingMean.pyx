# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming mean wrapper module for C++.

This module is used to wrap the C++ Streaming mean implemtation.

Example:

    >>> from KML.statistics.summary.StreamingMean import PyStreamingMean
    >>> sm = PyStreamingMean(5)
    >>> sm.update(list(range(1, 11)))
    >>> print(sm.evaluate())
"""
from collections.abc import Iterable
from typing import Union


cdef class PyStreamingMean:
    """Class containing the Streaming Mean implementation in Cython.

    Streaming mean wrapper for the C++ StreamingMean class. This code contains
    the public interface usage for the streaming mean statistic.

    Args:
        window_size (int): Desired window size.

    Attributes:
        c_SM (StreamingMean*) : Pointer to the C++ StreamingMean implementation.
        window_size (int): Desired window size.
    """
    cdef StreamingMean *c_SM

    def __init__(self, window_size=None) -> None:
        pass

    def __cinit__(self, window_size=None) -> None:
        self.c_SM = new StreamingMean(window_size)

    def update(self, observation: Union[float, Iterable]) -> None:
        """Update the Streaming Mean with the given item.

        Update the streaming Mean with the given item. The window_size
        parameter helps adjust for data drift within the mean calculation.

        Args:
            item (float, Iterable): Item to update iqr.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SM.update(o)
        else:
            self.c_SM.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming Mean value.

        Retrieve the current streaming mean value from the previous items
        updated.

        Returns:
            float: Current Mean value in window.
        """
        return self.c_SM.evaluate()

    def __dealloc__(self) -> None:
        del self.c_SM
