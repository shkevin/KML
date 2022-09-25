# -*- coding: utf-8 -*-
#distutils: language = c++
"""StreamingHistogram Cython wrapper module for C++.

This module is used to wrap the C++ StreamingHistogram implemtation.
This module specifically uses the double generic template. This histogram
implementation is an altered variant of the Ben-Haim and Tom-Tov histogram
implementation.

Example:

    >>> from KML.data_structures.histograms.StreamingHistogram import PyStreamingHistogram
    >>> SH = PyStreamingHistogram(num_bins=5,window_size=5)
    >>> for i in range(5):
    >>>     SH.update(i)
    >>> assert SH.size() == 5

References:
    * Histogram - https://jmlr.csail.mit.edu/papers/volume11/ben-haim10a/ben-haim10a.pdf
    * Quantile Estimation - https://arxiv.org/pdf/1712.02476.pdf
    * Exponential Histogram - https://randorithms.com/2022/01/31/streaming-histograms.html
"""
from collections.abc import Iterable
from typing import Optional


cdef class PyStreamingHistogram:
    """Class containing the StreamingHistogram implemenation in Cython.

    StreamingHistogram wrapper for the C++ StreamingHistogram class.
    This code contains the public interface usage for the StreamingHistogram
    data structure.

    Args:
        num_bins (int): Number of bins the histogram should have.
        window_size (int, optional): Desired window size for StreamingHistogram. Defaults to 100.
        decay_type (DecayType, optional): How to decay the counts when outside of scope.

    Attributes:
        c_SH (StreamingHistogram[double]*): Pointer to the C++ StreamingHistogram implementation.
        num_bins (int): Number of bins the histogram should have.
        window_size (int, optional): Desired window size for StreamingHistogram. Defaults to 100.
        decay_type (DecayType, optional): How to decay the counts when outside of scope.
    """
    cdef StreamingHistogram[double] *c_SH

    def __init__(self, num_bins: int, window_size: Optional[int]=100,
                 decay_type: Optional[DecayType]=WINDOW) -> None:
        pass

    def __cinit__(self, num_bins: int, window_size: Optional[int]=100,
                 decay_type: Optional[DecayType]=WINDOW) -> None:
        self.c_SH = new StreamingHistogram[double](num_bins, window_size, decay_type)

    def update(self, item) -> None:
        """Update the Histogram with the given item.

        Update the streaming Histogram with the given item.

        Args:
            item (double, Iterable): Item to add to histogram.
        """
        if isinstance(item, Iterable):
            for i in item:
                self.c_SH.update(i)
        else:
            self.c_SH.update(item)

    def pdf(self, normalize: bool=True, density: bool=True) -> vector[double]:
        """Calculate the approximate PDF of the histogram.

        Calculate the approximate probability density function (PDF)
        for this histogram. The output can be normalized or calculated
        as the density based off of user input.

        Args:
            normalize (bool, optional): Whether to normalize the counts by the
                the number of items in the window..
            density (bool, optional): Whether to calculate the histogram
                density from the frequency counts.

        Returns:
            vector[double]: The counts of the histogram.
        """
        return self.c_SH.pdf(normalize, density);

    def cdf(self, normalize: bool=True) -> vector[double]:
        """Calculate the Cumulatitive Density Function of the Histogram.

        Calculate the Cumulatitive Density (CDF) of the Histogram. If the normalize
        option is true, this will normalie the CDF by the number of items in the
        window.

        Args:
            normalize (bool, optional): Normalize the CDF by the number of items
                in the current window.

        Returns:
            vector[double]: The CDF of the current histogram.
        """
        return self.c_SH.cdf(normalize);

    def quantile(self, q_tile: double) -> double:
        """Retrieve the bin edge that represents the input quantile value.

        Calculate the bin edge that represents the input quantile value. This
        quantile calculation is a rough approximation, based off of the Tille-
        Langel histogram quantile estimation.

        Args:
            q_tile (double): Which quantile to estimate.

        Returns:
            double: The bin edge representing the given quantile.
        """
        return self.c_SH.quantile(q_tile)

    def bin_counts(self) -> vector[uint64_t]:
        """Retrieve the current bin counts in the Histogram.

        Retrieve the current bin counts for each bin the current histogram.

        Returns:
            vectr[uint64_t]: The frequency counts for each bin.
        """
        return self.c_SH.binCounts();

    def reset(self) -> None:
        """Reset this StreamingHistogram to empty.

        Reset will completely remove all elements in the current StreamingHistogram.
        """
        self.c_SH.reset()

    def empty(self) -> bool:
        """Determine if this StreamingHistogram is empty.

        Return a boolean value that showcases whether this StreamingHistogram contains
        any elements.

        Returns:
            bool: If StreamingHistogram is empty.
        """
        return self.c_SH.empty()

    def full(self) -> bool:
        """Determine if this StreamingHistogram is has window_size elements.

        Determine if this StreamingHistogram is full based off of the specified
        user input window_size.

        Returns:
            bool: If StreamingHistogram is full (window_size).
        """
        return self.c_SH.full()

    def size(self) -> int:
        """Retrieve the current number of nodes.

        Retrieve the current number of nodes in this StreamingHistogram.

        Returns:
            int: Size of StreamingHistogram.
        """
        return self.c_SH.size()
