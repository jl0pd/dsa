class Node(object):
	parent: "Node"
	child: "Node"
	left: "Node"
	right: "Node"
	mark: str
	degree: int
	c: str
	value: int

class FibonacciHeap(object):
	__root: Node
	__nH: int

	def __init__(self):
		self.__root = None

	def link(self, st: Node, nd: Node) -> int:
		pass

	def insert(self, key: int) -> Node:
		pass

	def union(self, other: Node) -> Node:
		pass

	def extractMin(self, node: Node) -> Node:
		pass

	def consolidate(self, node: Node) -> int:
		pass

	def display(self, node: Node) -> int:
		pass

	def find(self, node: Node, key: int) -> Node:
		pass

	def decreaseKey(self, node: Node, a: int, b: int) -> int:
		pass

	def deleteKey(self, node: Node, a: int) -> int:
		pass

	def cut(self, st: Node, nd: Node, rd: Node) -> int:
		pass

	def cascadeCut(self, st: Node, nd: Node) -> int:
		pass
