# -*- coding: utf-8 -*-
#distutils: language = c++
"""Streaming P2 Quantile wrapper module for C++.

This module is used to wrap the C++ Streaming P2 Quantile implemtation.

Example:

    >>> from KML.statistics.summary.StreamingP2Quantile import PyStreamingP2Quantile
    >>> quant = PyStreamingP2Quantile(quantile=0.5)
    >>> quant.update(list(range(1, 10)))
    >>> print(quant.evaluate())

Reference:
    https://www.cs.wustl.edu/~jain/papers/ftp/psqr.pdf
"""
from collections.abc import Iterable
from typing import Union


cdef class PyStreamingP2Quantile:
    """Class containing the Streaming P2 Quantile implemenation in Cython.

    Streaming P2 Quantile wrapper for the C++ StreamingP2Quantile class.
    This code contains the public interface usage for the streaming P2 quantile
    statistic.

    Args:
        quantile (float): Quantile to calculate.

    Attributes:
        quantile (float): Quantile to calculate.
    """
    cdef StreamingP2Quantile* c_P2

    def __init__(self, quantile=0.5) -> None:
        pass

    def __cinit__(self, quantile=0.5) -> None:
        self.c_P2 = new StreamingP2Quantile(quantile)

    def update(self, observation: Union[float, Iterable]) -> None:
        """Update the Streaming P2 Quantile with the given item.

        Update the streaming quantile with the given item.

        Args:
            item (float, Iterable): Item to update quantile value.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_P2.update(o)
        else:
            self.c_P2.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current Streaming P2 Quantile statistic.

        Retrieve the current streaming quantile statisic from the previous items
        updated.

        Returns:
            float: Current quantile value.
        """
        return self.c_P2.evaluate()

    def __dealloc__(self) -> None:
        del self.c_P2
