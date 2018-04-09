#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

#define WORD_COUNT 20711 //51203

int main()
{
   char **buffer = (char **)malloc(WORD_COUNT * sizeof(char *));

    for(size_t i = 0; i < WORD_COUNT; i++) {
        buffer[i] = (char *)malloc(20 * sizeof(char));
    }

    FILE *text = fopen("input.txt", "r");
    for(size_t i = 0; i < WORD_COUNT; i++) {
        fscanf(text, "%s", buffer[i]);
        puts(buffer[i]);
    }
    fclose (text);

    bstree *tree = bstree_create(buffer[0], 0);

    for (size_t i = 0; i < WORD_COUNT; i++)
    {
        bstree_add(tree, buffer[i], i);
    }
    
    bstree *min    = bstree_min(tree);
    bstree *max    = bstree_max(tree);
    bstree *search = bstree_lookup(tree, *buffer);
    
    puts(min->key);
    puts(max->key);
    puts(search->key);

    return 0;
}
