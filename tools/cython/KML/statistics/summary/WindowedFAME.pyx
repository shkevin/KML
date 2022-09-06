# -*- coding: utf-8 -*-
#distutils: language = c++
"""Windowed FAME wrapper module for C++.

This module is used to wrap the C++ Windowed FAME implemtation.

Example:

    >>> from KML.statistics.summary.WindowedFAME import PyWindowedFAME
    >>> fame = PyWindowedFAME()
    >>> fame.update(list(range(1, 11)))
    >>> print(fame.evaluate())

Reference:
    https://ieeexplore.ieee.org/document/4261339
"""
from collections.abc import Iterable
from typing import Union


cdef class PyWindowedFAME:
    """Class containing the Windowed FAME implementation in Cython.

    Windowed FAME wrapper for the C++ WindowedFame class. This code contains
    the public interface usage for the Windowed FAME (Fast Algorithm for Median Estimation)
    statistic.

    Args:
        step_size (int): The step size to take when calculating median.
        epsilon (float): epsilon The exponential growth factor. This gives the
                         median calculation a "windowing flavor".

    Attributes:
        c_FM (WindowedFAME*) : Pointer to the C++ WindowedFAME implementation.
        step_size (int): The step size to take when calculating median.
        epsilon (float): epsilon The exponential growth factor. This gives the
                         median calculation a "windowing flavor".
    """
    cdef WindowedFAME* c_FM

    def __init__(self, step_size=0.1, epsilon=0.0) -> None:
        pass

    def __cinit__(self, step_size=0.1, epsilon=0.0) -> None:
        self.c_FM = new WindowedFAME(step_size, epsilon)

    def update(self, observation: Union[float, Iterable]) -> None:
        """Update the Median with the given item.

        Update the Windowed FAME median calculation with the given item.

        Args:
            item (float, Iterable): Item to update iqr.
        """
        if isinstance(observation, Iterable):
            for o in observation:
                self.c_FM.update(o)
        else:
            self.c_FM.update(observation)

    def evaluate(self) -> float:
        """Retrieve the current median approximation.

        Retrieve the current FAME median from the previous items updated.

        Returns:
            float: Current median approximation.
        """
        return self.c_FM.evaluate()

    def __dealloc__(self) -> None:
        del self.c_FM
