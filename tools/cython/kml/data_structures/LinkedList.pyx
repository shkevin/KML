# -*- coding: utf-8 -*-
#distutils: language = c++
"""LinkedList Cython wrapper module for C++.

This module is used to wrap the C++ LinkedList implemtation.
This module specifically uses the float generic template.

Example:

    >>> from kml.data_structures.LinkedList import PyLinkedList
    >>> LL = PyLinkedList(window_size=5)
    >>> for i in range(5):
    >>>     LL.update(i)
    >>> assert LL.size() == 5
"""
from collections.abc import Iterable
from typing import Optional, Union


cdef class PyLinkedList:
    """Class containing the LinkedList implemenation in Cython.

    LinkedList wrapper for the C++ LinkedList class. This code contains
    the public interface usage for the LinkedList data structure.

    Note:
        If window_size is set to None, the LinkedList will behave similar to a
        window less LinkedList.

    Args:
        window_size (int, optional): Desired window size for LinkedList. Defaults to None.

    Parameters:
        c_LL (LinkedList[float]*): Pointer to the C++ LinkedList implementation.
        window_size (int, optional): Desired window size for LinkedList.
    """
    cdef LinkedList[float] *c_LL

    def __init__(self, window_size: Optional[int]=None) -> None:
        pass

    def __cinit__(self, window_size: Optional[int]=None) -> None:
        self.c_LL = new LinkedList[float](window_size)

    def update(self, item: Union[float, Iterable[float]]) -> None:
        """Update the LinkedList with the given item.

        Update the streaming LinkedList with the given item. If the
        number of items inside the LinkedList is more the the specified window_size,
        remove the oldest element and update.

        Args:
            item (float, Iterable): Item to push to LinkedList.
        """
        if isinstance(item, Iterable):
            for i in item:
                self.c_LL.update(i)
        else:
            self.c_LL.update(item)

    def pop(self) -> float:
        """Remove the head of the LinkedList and return the value.

        Pop the head of the LinkedList and return the heads value.

        Returns:
            float: Value of head.
        """
        return self.c_LL.pop()

    def reset(self) -> None:
        """Reset this LinkedList to empty.

        Reset will completely remove all elements in the current LinkedList.
        """
        self.c_LL.reset()

    def empty(self) -> bool:
        """Determine if this LinkedList is empty.

        Return a boolean value that showcases whether this LinkedList contains
        any elements.

        Returns:
            bool: If LinkedList is empty.
        """
        return self.c_LL.empty()

    def full(self) -> bool:
        """Determine if this LinkedList is has window_size elements.

        Determine if this LinkedList is full based off of the specified
        user input window_size.

        Note:
            This function will always evaluate to false if window_size is None.

        Returns:
            bool: If LinkedList is full (window_size).
        """
        return self.c_LL.full()

    def size(self) -> int:
        """Retrieve the current number of nodes.

        Retrieve the current number of nodes in this LinkedList.

        Returns:
            int: Size of LinkedList.
        """
        return self.c_LL.size()
