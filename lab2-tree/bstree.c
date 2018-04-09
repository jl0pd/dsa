#include "bstree.h"

bstree *bstree_create(char *key, int value)
{
	static bstree create;

	create.data = value;
	for (int i = 0; i < 25; i++)
		create.key[i] = key[i];

	create.parent = NULL;
	create.left   = NULL;
	create.right  = NULL;

	return &create;
}


void bstree_add(bstree *tree, char *key, int value)
{
	bstree *child = bstree_create(key, value);
	bstree *node = tree;

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

bstree *bstree_lookup(bstree *tree, const char *key)
{
	/*
    while (tree) {
        if (tree->key < key && (tree->key != NULL)) {
            tree = tree->left;
            continue;
        } else if (tree->key > key) {
            tree = tree->right;
            continue;
        } else {
            return tree;
        }
    }
    return NULL;
}
*/


    while(1){
        if(strcmp(key, tree->key) < 0){
            if(tree->left != NULL){
                tree = tree->left;
            } else {
                return NULL;
            }
        } else if (strcmp(key, tree->key) > 0){
            if(tree->right != NULL){
                tree = tree->right;
            } else {
                return NULL;
            }
        } else {
            return tree;
        }
    }
}

bstree *bstree_min(bstree *tree)
{
	if (tree->left != NULL){
		tree = tree->left;
	}
	return tree;
}

bstree *bstree_max(bstree *tree)
{
	if (tree->right != NULL){
		tree = tree->right;
	}
	return tree;
}