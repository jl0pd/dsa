#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

int main()
{
    int i;
    char **buffer = (char **)malloc(51203 * sizeof(char *));
    for(size_t i = 0; i < 51203; i++) {
        buffer[i] = (char *)malloc(20 * sizeof(char));
    }
    FILE *text = fopen("slova(utf-8).txt", "r");
    for(i = 0; i < 51203; i++) {
        fscanf(text,"%s",buffer[i]);
        puts(buffer[i]);
    }
    fclose (text);

    bstree *tree = bstree_create(buffer[0], 0);

    for (i = 0; i < 51203; i++)
    {
        bstree_add(tree, buffer[i], i);
    }
    
    bstree *min = bstree_min(tree);
    bstree *max = bstree_max(tree);
    bstree *search = bstree_lookup(tree, *buffer);
    printf("min = %s\n", min->key);
    printf("max = %s\n", max->key);
    printf("search = %s\n", search->key);

    return 0;

}