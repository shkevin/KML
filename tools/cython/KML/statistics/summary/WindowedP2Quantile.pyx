# -*- coding: utf-8 -*-
#distutils: language = c++
"""Windowed P2 Quantile wrapper module for C++.

This module is used to wrap the C++ Windowed P2 Quantile implemtation.

Example:

    >>> from KML.statistics.summary.WindowedP2Quantile import PyWindowedP2Quantile
    >>> p2 = PyWindowedP2Quantile(quantile=0.5, window_size=10)
    >>> p2.update(list(range(1, 11)))
    >>> print(p2.evaluate())
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyWindowedP2Quantile:
    """Class containing the Windowed P2 Quantile implementation in Cython.

    Windowed P2 Quantile wrapper for the C++ WindowedP2Quantile class. This code contains
    the public interface usage for calculating the quantile value within a window.

    Args:
        quantile (float): Quantile to calculate.
        window_size (int, optional): Desired window size. Defaults to None.

    Parameters:
        c_WP2 (WindowedP2Quantile*) : Pointer to the C++ WindowedP2Quantile implementation.
        quantile (float): Quantile to calculate.
        window_size (int, optional): Desired window size. Defaults to None.
    """
    cdef WindowedP2Quantile* c_WP2

    def __init__(self, quantile, window_size: Optional[int]=None) -> None:
        pass

    def __cinit__(self, quantile, window_size: Optional[int]=None) -> None:
        self.c_WP2 = new WindowedP2Quantile(quantile, window_size)

    def update(self, observation: Union[float, Iterable[float]]) -> None:
        """Update the Windowed P2 Quantile with the given item.

        Update the streaming quantile with the given item.

        Args:
            item (float, Iterable): Item to update quantile value.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_WP2.update(o)
        else:
            self.c_WP2.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current quantile statistic.

        Retrieve the current streaming quantile statisic from the previous items
        updated.

        Returns:
            float: Current quantile value.
        """
        return self.c_WP2.evaluate()

    def __dealloc__(self) -> None:
        del self.c_WP2
