#ifndef BSTREE_H
#define BSTREE_H
#include <string.h>
#include <stdlib.h>

typedef struct bstree{
	int data;
	struct bstree *left;
	struct bstree *right;
	struct bstree *parent;
	char *key;
}bstree;

bstree *bstree_create(char *key, int value);
void bstree_add(bstree *tree, char *key, int value);
bstree *bstree_lookup(bstree *tree, const char *key);
bstree *bstree_min(bstree *tree);
bstree *bstree_max(bstree *tree);

#endif