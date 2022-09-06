# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming Interquartile Range wrapper module for C++.

This module is used to wrap the C++ Streaming IQR implemtation.

Example:

    >>> from KML.statistics.summary.StreamingIQR import PyStreamingIQR
    >>> iqr = PyStreamingIQR(window_size=10)
    >>> iqr.update(list(range(1, 10)))
    >>> print(iqr.evaluate())
"""
from collections.abc import Iterable
from typing import Union


cdef class PyStreamingIQR:
    """Class containing the Streaming IQR implemenation in Cython.

    Streaming IQR wrapper for the C++ StreamingIQR class. This code contains
    the public interface usage for the streaming IQR statistic.

    Args:
        low (float): Low range (defaults to 25% quartile).
        high (float): High range (defaults to 75% quartile).
        window_size (int): Desired window size.

    Attributes:
        c_IQR (StreamingIqR*): Pointer to the C++ StreamingIQR implementation.
        low (float): Low range (defaults to 25% quartile).
        high (float): High range (defaults to 75% quartile).
        window_size (int): Desired window size.
    """
    cdef StreamingIQR* c_IQR

    def __init__(self, low=None, high=None, window_size=None) -> None:
        pass

    def __cinit__(self, low=None, high=None, window_size=None) -> None:
        if low is None or high is None:
           self.c_IQR = new StreamingIQR(window_size)
        else:
           self.c_IQR = new StreamingIQR(low, high, window_size)

    def update(self, observation: Union[float, Iterable]) -> None:
        """Update the Streaming IQR with the given item.

        Update the streaming IQR with the given item. The window_size
        parameter helps adjust for data drift within the iqr calculation.

        Args:
            item (float, Iterable): Item to update iqr.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_IQR.update(o)
        else:
            self.c_IQR.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming IQR value.

        Retrieve the current streaming iqr value from the previous items
        updated.

        Returns:
            float: Current IQR value in window.
        """
        return self.c_IQR.evaluate()

    def __dealloc__(self) -> None:
        del self.c_IQR
