#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bstree.h"

// #define WORD_COUNT 20711 
// #define WORD_COUNT 51203
// #define WORD_COUNT 10000

int main()
{
    int WORD_COUNT;
    printf("enter word count: ");
    scanf("%d", &WORD_COUNT);
    srand(time(NULL));
    char buffer[WORD_COUNT][40];

    // for(size_t i = 0; i < WORD_COUNT; i++) {
    //     buffer[i] = (char *)malloc(20 * sizeof(char));
    // }

    double start = clock();
    FILE *text = fopen("aver_way.txt", "r");
    for (int i = 0; i < WORD_COUNT; i++) {
        fscanf(text, "%s", buffer[i]);
        // puts(buffer[i]);
    }
    fclose (text);
    double end = clock();
    double time = difftime(end, start) / 1000000;
    printf("reading time:\t\t%0.10f\n", time);

    start = clock();
    bstree *tree = bstree_create(buffer[0], 0);
    end = clock();
    time = difftime(end, start) / 1000000;
    printf("creating time:\t\t%0.10f\n", time);

    start = clock();
    for (int i = 0; i < WORD_COUNT; i++)
    {
        bstree_add(tree, buffer[i], i);
    }
    end = clock();
    time = difftime(end, start) / CLOCKS_PER_SEC;
    printf("adding time:\t\t%0.10f\n", time);
     
    start = clock();
    bstree *min    = bstree_min(tree);
    end = clock();
    time = difftime(end, start) / CLOCKS_PER_SEC;
    printf("min_search time:\t%0.10f\n", time);
    
    start = clock();
    bstree *max    = bstree_max(tree);
    end = clock();
    time = difftime(end, start) / CLOCKS_PER_SEC;
    printf("max_search time:\t%0.10f\n", time);


    double loctime = 0;
    for (int i = 0; i < 10000; i++){
        start = clock();
        bstree *search = bstree_lookup(tree, buffer[rand()%WORD_COUNT]);
        end = clock();
        loctime += difftime(end, start);
    }

    time = loctime / CLOCKS_PER_SEC /10000;
    printf("key_search average of %d, time:\t%0.10f\n", 10000, time);

    // puts(min->key);
    // puts(max->key);
    // puts(search->key);
    return 0;
}
