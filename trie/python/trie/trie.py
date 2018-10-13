class Trie(object):
    class Node(object):
        __slots__ = ("sym", "value", "child")

        def __init__(self, sym, value=None):
            self.sym = sym
            self.value = value
            self.child = dict()

        def keys(self):
            return self.child.keys()

        def __setitem__(self, key, value):
            self.child[key] = value

        def __getitem__(self, item):
            return self.child[item]

    def __init__(self):
        self.root = self.Node("")

    def __setitem__(self, key, value):
        self.insert(key, value)

    def __getitem__(self, item):
        try:
            return self.lookup(item)
        except KeyError:
            return None

    @staticmethod
    def hi():
        print("hi")

    def insert(self, key, value):
        tmp = self.root
        for c in key[:-1]:
            if c in tmp.keys() or c in tmp.keys():
                tmp = tmp[c]
            else:
                tmp[c] = self.Node(c)
                tmp = tmp[c]
        if tmp.keys():
            tmp[key[-1]].value = value
        else:
            tmp[key[-1]] = self.Node(key[-1], value)

    def clear(self):
        self.root = self.Node("")

    def delete(self, key):
        tmp = self.root
        for c in key:
            pass
            # tmp = tmp[c]

    def show(self):
        def show_branch(branch, deep):
            if branch.value:
                print(" " * (deep - 1), "\x1b[1A :=", branch.value)

            for c in branch.keys():
                print("|" * deep, c, sep="")
                show_branch(branch[c], deep + 1)

        for c in self.root.keys():
            print(c)
            show_branch(self.root[c], 1)

    def lookup(self, key):
        tmp = self.root[key[0]]
        for c in key[1:]:
            tmp = tmp[c]

        return tmp.value


if __name__ == "__main__":
    trie = Trie()
    trie["absolute"] = 100
    trie["abs"] = 200
    trie["fork"] = 700
    trie["abrakadabra"] = 100_500
    trie["for"] = "hi"
    trie["foreach"] = [1, 2, 3.14, ["Sum", "Len"]]
    trie["forever"] = int
    trie.show()

    print("\n\n\n\n")

    for i, key in enumerate(("abs", "fork", "foreach"), 1):
        print(f"{i}: {trie[key]}")
