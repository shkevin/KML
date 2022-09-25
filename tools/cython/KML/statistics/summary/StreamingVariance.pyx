# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming variance wrapper module for C++.

This module is used to wrap the C++ Streaming variance implemtation.

Example:

    >>> from KML.statistics.summary.StreamingVariance import PyStreamingVariance
    >>> sv = PyStreamingVariance(5)
    >>> sv.update(list(range(1, 11)))
    >>> print(sv.evaluate())
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyStreamingVariance:
    """Class containing the Streaming variance implementation in Cython.

    Streaming variance wrapper for the C++ StreamingVariance class. This code contains
    the public interface usage for the streaming variance statistic.

    Note:
        If window_size is set to None, or not specified, the variance calculation
        will behave similar to a batch setting.

    Args:
        window_size (int, optional): Desired window size. Defaults to None.

    Parameters:
        c_SM (StreamingVariance*) : Pointer to the C++ StreamingVariance implementation.
        window_size (int, optional): Desired window size.
    """
    cdef StreamingVariance* c_SV

    def __init__(self, window_size: Optional[int]=None) -> None:
        pass

    def __cinit__(self, window_size: Optional[int]=None) -> None:
        self.c_SV = new StreamingVariance(window_size)

    def update(self, observation: Union[float, Iterable[float]]) -> None:
        """Update the Streaming Variance with the given item.

        Update the streaming Variance with the given item. The window_size
        parameter helps adjust for data drift within the variance calculation.

        Args:
            observation: Item to update iqr.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SV.update(o)
        else:
            self.c_SV.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming Variance value.

        Retrieve the current streaming mean value from the previous items
        updated.

        Returns:
            float: Current Variance value in window.
        """
        return self.c_SV.evaluate()

    def __dealloc__(self) -> None:
        del self.c_SV
