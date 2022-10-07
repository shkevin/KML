# -*- coding: utf-8 -*-
#distutils: language = c++
"""Windowed FAME wrapper module for C++.

This module is used to wrap the C++ Windowed FAME implemtation.

Example:

    >>> from kml.statistics.summary.WindowedFAME import PyWindowedFAME
    >>> fame = PyWindowedFAME()
    >>> fame.update(list(range(1, 11)))
    >>> print(fame.evaluate())

Reference:
    https://ieeexplore.ieee.org/document/4261339
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyWindowedFAME:
    """Class containing the Windowed FAME implementation in Cython.

    Windowed FAME wrapper for the C++ WindowedFame class. This code contains
    the public interface usage for the Windowed FAME (Fast Algorithm for Median Estimation)
    statistic.

    Args:
        step_size (int, optional): The step size to take when calculating median. Defaults to 0.1.
        epsilon (float, optional): epsilon The exponential growth factor. This gives the
                         median calculation a "windowing flavor". Defaults to 0.0.

    Parameters:
        c_FM (WindowedFAME*) : Pointer to the C++ WindowedFAME implementation.
        step_size (int, optional): The step size to take when calculating median. Defaults to 0.1.
        epsilon (float, optional): epsilon The exponential growth factor. This gives the
                         median calculation a "windowing flavor". Defaults to 0.0.
    """
    cdef WindowedFAME* c_FM

    def __init__(self, step_size: Optional[float]=0.1,
                 epsilon: Optional[float]=0.0) -> None:
        pass

    def __cinit__(self, step_size: Optional[float]=0.1,
                  epsilon: Optional[float]=0.0) -> None:
        self.c_FM = new WindowedFAME(step_size, epsilon)

    def update(self, observation: Union[float, Iterable[float]]) -> None:
        """Update the Median with the given item.

        Update the Windowed FAME median calculation with the given item.

        Args:
            observation (float, Iterable): Item to update median.
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
