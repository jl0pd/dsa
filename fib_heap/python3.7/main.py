from dataclasses import dataclass
from typing import Dict

class Priority_Queue(object):
    def insert(self, key, value):
        pass

    def delMin(self):
        pass

    def delMax(self):
        pass

    def min(self):
        pass

    def max(self):
        pass

    def decreaseKey(self):
        pass

    def merge(self, other):
        pass


class Heap(object):
    pass


class DoubleLinkedList(object):
    @dataclass
    class Node(object):
        __slots__ = ("_parent", "_child", "_left", "_right", "_key", "_value", "_degree", "_mark")
        parent: "DoubleLinkedList.Node"
        child: "DoubleLinkedList.Node"
        left: "DoubleLinkedList.Node"
        right: "DoubleLinkedList.Node"
        key: int = -1# weight, key
        value: str = ""
        degree: int = 0
        mark: bool = False

        def __init__(self, key=None, value=None, degree=-1):
            if key is not None and value is not None and degree:
                self._key = key
                self._value = value
                self._degree = degree
            else:
                self._left = self._right = self


    def __init__(self):
        pass


class FibHeap(Heap, Priority_Queue):

    def insert(self, key, value):

        node = DoubleLinkedList.Node(key, value)



