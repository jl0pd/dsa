#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_RED   0
#define COLOR_BLACK 1

typedef struct rbtree{
    int key;
    char *value;
    int color;

    struct rbtree *parent;
    struct rbtree *left;
    struct rbtree *right;
}rbtree;

rbtree * rbtree_add(rbtree *root, int key, char *value);
rbtree * rbtree_fixup_add(rbtree *root,  rbtree *node);
rbtree * rbtree_left_rotate(rbtree *root, rbtree *node);
rbtree * rbtree_right_rotate(rbtree *root, rbtree *node);
void rbtree_print(rbtree *root);

rbtree EmptyNode = {0, NULL, COLOR_BLACK, NULL, NULL, NULL};
rbtree *NullNode = &EmptyNode;

int main(int argc, char **argv)
{
    rbtree *tree = NULL;

    char cache[15][10];
    for (int i = 1; i < 10; i++)
    {
        sprintf(cache[i], "%d", i);
        tree = rbtree_add(tree, i, cache[i]);
    }

    // tree = rbtree_add(tree, 10, "10");
    // tree = rbtree_add(tree, 5, "5");
    // tree = rbtree_add(tree, 3, "3");
    // tree = rbtree_add(tree, 11, "11");
    // tree = rbtree_add(tree, 12, "12");
    // tree = rbtree_add(tree, 6, "6");
    // tree = rbtree_add(tree, 8, "8");
    // tree = rbtree_add(tree, 9, "9");

    rbtree_print(tree);
    // rbtree_free(tree);           


    return 0;
}

#define RED "\x1b[41m"
#define BLACK "\x1b[40m"
#define DEFAULT "\x1b[49m"
void print_struct(rbtree *one_node)
{
    #define DIVIDER "~~~~~~~~"
    if (one_node->color)
        printf(BLACK "key: %d\nvalue: %s" DEFAULT "\n" DIVIDER "\n", 
            one_node->key, 
            one_node->value
        );
    else
        printf(RED "key: %d\nvalue: %s" DEFAULT "\n" DIVIDER "\n", 
            one_node->key, 
            one_node->value
        );
    #undef DIVIDER
}

void rbtree_print(rbtree *root)
{
    if (root->value[0])
    {
        print_struct(root);
        rbtree_print(root->left);
        rbtree_print(root->right);
    }
}
#undef RED
#undef BLACK
#undef DEFAULT

rbtree * rbtree_add(rbtree *root, int key, char *value)
{
    rbtree *node, *parent = NullNode;
    /* Search leaf for new element */ 
    for (node = root; node != NullNode && node != NULL; ) 
    { 
        parent = node; 
        if (key < node->key) 
            node = node->left; 
        else if (key > node->key) 
            node = node->right; 
        else 
            return root; 
    } 
    node = malloc(sizeof(*node)); 
    
    if (node == NULL) 
        return NULL;
    
    node->key    = key;
    node->value  = value;
    node->color  = COLOR_RED;
    node->parent = parent;
    node->left   =  NullNode;
    node->right  =  NullNode;

    if (parent != NullNode) 
    { 
        if (key < parent->key) 
            parent->left = node;
        else parent->right = node;    
    } else {
        root = node;
    } 
    return rbtree_fixup_add(root, node);
}

rbtree * rbtree_fixup_add(rbtree *root, rbtree *node)
{
    rbtree *uncle;
    /* Current node is RED */ 
    while (node != root && node->parent->color == COLOR_RED)  
    { 
        if (node->parent == node->parent->parent->left)  
        { 
            /*  N ode  in left tree of grandfather */ 
            uncle = node->parent->parent->right; 
            if (uncle->color == COLOR_RED) 
            { 
                /*  Case 1  - uncle is RED */ 
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                node  = node->parent->parent;
            } else { 
                /* Cases 2 & 3  - uncle is BLACK */ 
                if (node == node->parent->right) 
                { 
                    /* Reduce case 2 to case 3  */ 
                    node = node->parent; 
                    root = rbtree_left_rotate(root, node); 
                } 
                /*  Case 3 */ 
                node->parent->color = COLOR_BLACK; 
                node->parent->parent->color = COLOR_RED; 
                root = rbtree_right_rotate (root, node->parent->parent);
            }
        } else { 
            /*  * Node  in  right tree  of grandfather  * * Cases 4, 5, 6  - node in right tree  * of grandfather  */ 
            uncle = node->parent->parent->left; 
            if (uncle->color == COLOR_RED) 
            { 
                /* Uncle is RED  – case 4 */ 
                node->parent->color = COLOR_BLACK; 
                uncle->color = COLOR_BLACK; 
                node->parent->parent->color = COLOR_RED; 
                node = node->parent->parent;
            } else { 
                /*  Uncle is BLACK */ 
                if (node == node->parent->left) 
                { 
                    node = node->parent; 
                    root = rbtree_right_rotate (root, node); 
                } 
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                root = rbtree_left_rotate (root, node->parent->parent);
            } 
        } 
    }
    root->color = COLOR_BLACK; 
    return root; 
}

rbtree * rbtree_left_rotate(rbtree *root, rbtree *node) 
{
    rbtree *right = node->right; 
    /* Create node->right link */ 
    node->right = right->left; 
    if (right->left != NullNode)  
        right->left->parent = node; 
    /* Create right->parent link */ 
    if (right != NullNode)  
        right->parent = node->parent; 
        if (node->parent != NullNode) 
        { 
            if (node == node->parent->left) 
                node->parent->left = right; 
            else node->parent->right = right; 
        } else { 
            root = right; 
        } 
    right->left = node; 
    if (node != NullNode)  
        node->parent = right; 
    return root; 
}

rbtree * rbtree_right_rotate(rbtree *root, rbtree *node) 
{
    rbtree *left = node->left; 
    /* Create node->left link */ 
    node->left = left->right; 
    if (left->right != NullNode)  
        left->right->parent = node; 
    /* Create left->parent link */
    if (left != NullNode)  
        left->parent = node->parent;
    if (node->parent != NullNode) 
    { 
        if (node == node->parent->right) 
            node->parent->right = left; 
        else node->parent->left = left; 
    } else { 
        root = left; 
    } 
    left->right = node; 
    if (node != NullNode)  
        node->parent = left; 
    return root; 
}

