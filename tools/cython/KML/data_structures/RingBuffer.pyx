# -*- coding: utf-8 -*-
#distutils: language = c++
"""RingBuffer Cython wrapper module for C++.

This module is used to wrap the C++ RingBuffer implemtation. This module
specifally uses the float generic template.

Example:

    >>> from KML.data_structures.RingBuffer import PyRingBuffer
    >>> RB = PyRingBuffer(window_size=5)
    >>> for i in range(5):
    >>>     RB.update(i)
    >>> assert RB.size() == 5
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyRingBuffer:
    """Class containing the RingBuffer implemenation in Cython.

    RingBuffer wrapper for the C++ RingBuffer class. This code contains
    the public interface usage for the RingBuffer data structure.

    Note:
        If window_size is set to None, the RingBuffer will behave similar to a
        window less LinkedList.

    Args:
        window_size (int, optional): Desired window size for ring buffer. Defaults to None.

    Attributes:
        c_RB (RingBuffer[float]*): Pointer to the C++ RingBuffer implementation.
        window_size (int, optional): Desired window size for ring buffer. Defaults to None.
    """
    cdef RingBuffer[float] *c_RB

    def __init__(self, window_size: Optional[int]=None) -> None:
        pass

    def __cinit__(self, window_size: Optional[int]=None) -> None:
        self.c_RB = new RingBuffer[float](window_size)

    def update(self, item: Union[float, Iterable]) -> None:
        """Update the RingBuffer with the given item.

        Update the streaming RingBuffer with the given item. If the item the
        number of items inside the RingBuffer is more the the specified window_size, remove the
        oldest element and update.

        Args:
            item (float, Iterable): Item to push to RingBuffer.
        """
        if isinstance(item, Iterable):
            for i in item:
                self.c_RB.update(i)
        else:
            self.c_RB.update(item)

    def pop(self) -> float:
        """Remove the head of the RingBuffer and return the value.

        Pop the head of the RingBuffer and return the heads value.

        Returns:
            float: Value of head.
        """
        return self.c_RB.pop()

    def reset(self) -> None:
        """Reset this RingBuffer to empty.

        Reset will completely remove all elements in the current RingBuffer.
        """
        self.c_RB.reset()

    def empty(self) -> bool:
        """Determine if this RingBuffer is empty.

        Return a boolean value that showcases whether this RingBuffer contains
        any elements.

        Returns:
            bool: If RingBuffer is empty.
        """
        return self.c_RB.empty()

    def full(self) -> bool:
        """Determine if this RingBuffer is has window_size elements.

        Determine if this RingBuffer is full based off of the specified
        user input window_size.

        Returns:
            bool: If RingBuffer is full (window_size).
        """
        return self.c_RB.full()

    def size(self) -> int:
        """Retrieve the current number of nodes.

        Retrieve the current number of nodes in this RingBuffer.

        Returns:
            int: Size of RingBuffer.
        """
        return self.c_RB.size()
