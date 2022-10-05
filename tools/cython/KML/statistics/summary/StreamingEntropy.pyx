# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming entropy wrapper module for C++.

This module is used to wrap the C++ Streaming entropy implemtation.

Example:

    >>> from KML.statistics.summary.StreamingEntropy import PyStreamingEntropy
    >>> sm = PyStreamingEntropy(10, 10)
    >>> sm.update(list(range(1, 11)))
    >>> print(sm.evaluate())
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyStreamingEntropy:
    """Class containing the Streaming Entropy implementation in Cython.

    Streaming entropy wrapper for the C++ StreamingEntropy class. This code contains
    the public interface usage for the streaming entropy statistic.

    Note:
        if num_bins is set at 0, the StreamingEntropy class will calculate the
        number of bins to use based off of the Sturges rule.

    Args:
        window_size (int, optional): Desired window size. Defaults to 100.
        num_bins (int, optional): Desired number of bins to approximate counts.
            Defaults to 0.

    Parameters:
        c_SE (StreamingEntropy*) : Pointer to the C++ StreamingEntropy implementation.
        window_size (int, optional): Desired window size. Defaults to 100.
        num_bins (int, optional): Desired number of bins to approximate counts.
            Defaults to 0.
    """
    cdef StreamingEntropy *c_SM

    def __init__(self, window_size: Optional[int]=100,
                 num_bins: Optional[int]=0) -> None:
        pass

    def __cinit__(self, window_size: Optional[int]=100,
                  num_bins: Optional[int]=0) -> None:
        self.c_SM = new StreamingEntropy(window_size, num_bins)

    def update(self, observation: Union[float, Iterable[float]]) -> None:
        """Update the Streaming Entropy with the given item.

        Update the streaming Entropy with the given item. The window_size
        parameter helps adjust for data drift within the entropy calculation.

        Args:
            item (float, Iterable): Item to update entropy.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_SM.update(o)
        else:
            self.c_SM.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming Entropy value.

        Retrieve the current streaming entropy value from the previous items
        updated.

        Returns:
            float: Current Entropy value in window.
        """
        return self.c_SM.evaluate()

    def __dealloc__(self) -> None:
        del self.c_SM
