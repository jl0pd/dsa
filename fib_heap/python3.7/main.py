from dataclasses import dataclass


class Priority_Queue(object):
    def insert(self, key):
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
        parent: "DoubleLinkedList.Node"
        child: "DoubleLinkedList.Node"
        left: "DoubleLinkedList.Node"
        right: "DoubleLinkedList.Node"
        key: str = ""
        value: str = ""
        degree: int = 0
        mark: bool = False

    def __init__(self):
        pass


class FibHeap(Heap, Priority_Queue):
    pass
