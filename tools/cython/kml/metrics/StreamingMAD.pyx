# -*- coding: utf-8 -*-
#distutils: language = c++
"""StreamingMAD Cython wrapper module for C++.

This module is used to wrap the C++ StreamingMAD implemtation.

Example:

    >>> from kml.metrics.StreamingMAD import PyStreamingMAD
    >>> MAD = PyStreamingMAD()
    >>> MAD.update(list(range(1, 5)))
    >>> print(MAD.evaluate())

TODO: Add arguments for windowed fame in streaming mad init.
"""
from collections.abc import Iterable
from typing import Union


cdef class PyStreamingMAD:
    """Class containing the Streaming MAD implemenation in Cython.

    Streaming Median Absolute Deviation (MAD) wrapper for the C++ StreamingMAD class.
    This code contains the public interface usage for the StreamingMAD metric.
    The mad value is calculated using the WindowedFame code, and inherently adjusts
    for data drift.

    Parameters:
        c_MAD (StreamingMAD*): Pointer to the C++ StreamingMAD implementation.
    """
    cdef StreamingMAD *c_MAD

    def __init__(self) -> None:
        pass

    def __cinit__(self) -> None:
        self.c_MAD = new StreamingMAD()

    def update(self, observation: Union[float, Iterable[float]]) -> None:
        """Update the StreamingMAD with the given item.

        Update the StreamingMAD with the given item.

        Args:
            item (float, Iterable): Item to update metric.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_MAD.update(o)
        else:
            self.c_MAD.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming MAD value.

        Retrieve the current streaming median absolute deviation
        value from the previous items updated.

        Returns:
            float: Median Absoluate Deviation for seen items.
        """
        return self.c_MAD.evaluate()

    def __dealloc__(self) -> None:
        del self.c_MAD
