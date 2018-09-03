#include "bstree.h"

bstree *bstree_create(char *key, int value)
{
	bstree *create = (bstree*)malloc(sizeof(bstree));
	if (create != NULL){
		create->data = value;
		create->key = key;
		create->parent = NULL;
		create->left   = NULL;
		create->right  = NULL;
	}
	return create;
}


void bstree_add(bstree *tree, char *key, int value)
{
	if (strcmp(tree->key, key) > 0){
		if (tree->left == NULL){
			bstree *tmp = (bstree*)malloc(sizeof(bstree));
			tmp->parent = tree;
			tmp->left = tmp->right = NULL;
			tmp->data = value;
			tmp->key = key;
			tree->left = tmp;
		}else{
			bstree_add(tree->left, key, value);
		}
	}else{
		if (tree->right == NULL){
			bstree *tmp = (bstree*)malloc(sizeof(bstree));
			tmp->parent = tree;
			tmp->left = tmp->right = NULL;
			tmp->data = value;
			tmp->key = key;
			tree->right = tmp;
		}else{
			bstree_add(tree->right, key, value);
		}
	}
}

bstree *bstree_lookup(bstree *tree, const char *key)
{
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
	while (tree->left != NULL){
		tree = tree->left;
	}
	return tree;
}

bstree *bstree_max(bstree *tree)
{
	while (tree->right != NULL){
		tree = tree->right;
	}
	return tree;
}