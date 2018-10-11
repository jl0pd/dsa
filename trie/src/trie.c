

struct trie *trie_create();
char* trie_lookup(struct trie *root, char *key);
struct trie *trie_insert(struct trie *root, char *key, char *value);
struct trie *trie_delete(struct trie *root, char *key);
void print_trie(struct trie *root, int level);
