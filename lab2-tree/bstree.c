#ifndef BSTREE_H
#define BSTREE_H
#include <stdio.h>
#include <string.h>

struct bstree{
	int data;
	struct bstree *left;
	struct bstree *right;
	struct bstree *parent;
	char key[25];
};

struct bstree *bstree_create(char *key, int value);
void bstree_add(struct bstree *tree, char *key, int value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);

#endif

#include "bstree.h"

struct bstree *bstree_create(char *key, int value)
{
	static struct bstree create;

	create.data = value;
	strcpy(create.key, key);

	create.parent = NULL;
	create.left = NULL;
	create.right = NULL;

	return &create;
}

void bstree_add(struct bstree *tree, char *key, int value)
{
	struct bstree *child = bstree_create(key, value);
	struct bstree *node = tree;

	int cmp;
	while(1)
	{
		cmp = strcmp(key, node->key);
		if(cmp < 0){
			if (node->left == NULL){
				node->left = child;
				child->parent = node;
				break;
			}
			node = node->left;
		} else {
		if (node->right == NULL){
			node->right = child;
			child->parent = node;
			break;
			}
		node = node->right;
		}
	}
}
