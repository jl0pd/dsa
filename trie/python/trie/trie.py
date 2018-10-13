class Trie(object):
    class Node(dict):
        __slots__ = ("sym", "value")

        def __init__(self, sym, value=None):
            self.sym = sym
            self.value = value

    def __init__(self, key_val_dict=None):
        self.root = self.Node("")
        if key_val_dict:
            for key, value in key_val_dict.items():
                self[key] = value

    def __setitem__(self, key, value):
        self.insert(key, value)

    def __getitem__(self, item):
        try:
            return self.lookup(item)
        except KeyError:
            return None

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
                print(f"{'|' * (deep - 1)}>> {branch.value}")
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
    keys = ["abs", "absolute", "fork", "for", "forever", "foreach"]
    values = [100, "200", 3.14, "hi", [int, float], keys]
    trie = Trie(dict(zip(keys, values)))
    trie.show()
    print("\n\n\n\n")

    for i, key in enumerate(("abs", "fork", "foreach", "askdjalksjdlkajl"), 1):
        print(f"{i}: {key} ==> {trie[key]}")
