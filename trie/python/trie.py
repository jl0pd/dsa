class Trie(object):
    class Node(object):
        def __init__(self, sym, value=None):
            self.sym = sym
            self.value = value
            self.childs = dict()

        def add_child(self, node):
            self.childs[node.sym] = node

        def keys(self):
            return self.childs.keys()

    def __init__(self):
        self.root = self.Node("")

    def insert(self, key, value):
        tmp = self.root
        for c in key[:-1]:
            if c in tmp.keys() or c in tmp.childs.keys():
                tmp = tmp.childs[c]
            else:
                tmp.childs[c] = self.Node(c)
                tmp = tmp.childs[c]
        if tmp.keys():
            tmp.childs[key[-1]].value = value
        else:
            tmp.childs[key[-1]] = self.Node(key[-1], value)

    def clear(self):
        self.root = self.Node("")

    def delete(self, key):
        tmp = self.root
        for c in key:
            tmp = tmp[c]

    def show(self):
        def show_branch(branch, deep):
            if branch.value:
                print(" " * (deep - 1), branch.value)
            for c in branch.keys():
                print(" " * deep, c, sep="")
                show_branch(branch.childs[c], deep + 1)

        for c in self.root.keys():
            print(c)
            show_branch(self.root.childs[c], 1)

    def lookup(self, key):
        tmp = self.root.childs[key[0]]
        for c in key:
            tmp = tmp.childs[c]

        return tmp.value


if __name__ == "__main__":
    trie = Trie()
    trie.insert("absolute", 100)
    trie.insert("abs", 200)
    trie.insert("abrakadabra", 100_500)
    trie.show()
