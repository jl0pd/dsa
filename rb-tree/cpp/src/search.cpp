#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <unistd.h>

#include "RBTree.cpp"

int main(int argc, char **argv)
{
    srand(time(NULL));

    std::vector<int> arr;

    FILE *f = fopen("data/search.txt", "w+");
    fprintf(f, "#\t\trand\t\t\tmin\t\t\t\tmax\n");
    fclose(f);

    int iter_count = 100000;

    for(int size = 100000; size <= 2000000; size+=100000)
    {
        f = fopen("data/search.txt", "a");

        for(int i = 0; i < size; i++)
        {
            arr.push_back(i);
        }

        double tree_st = clock();
        RBTree *tree = new RBTree(arr);
        double tree_end = clock();
        arr.clear();

        double rand_diff = 0;
        double min_diff = 0;
        double max_diff = 0;
        printf("size: %d -- init time: %2.10f\n", size, (tree_end - tree_st)/CLOCKS_PER_SEC);
        
        for(int i = 0; i < iter_count; i++)
        {
            double start = clock();
            tree->lookup(rand() % (size-1));
            double end = clock();
            rand_diff += end - start;

            start = clock();
            tree->min();
            end = clock();
            min_diff += end - start;

            start = clock();
            tree->max();
            end = clock();
            max_diff += end - start;
        }

        fprintf(f, "%d\t%0.10f\t%0.10f\t%0.10f\n",
            size,
            (rand_diff/iter_count)/CLOCKS_PER_SEC,
            (min_diff/iter_count)/CLOCKS_PER_SEC,
            (max_diff/iter_count)/CLOCKS_PER_SEC
        );

        fclose(f);

        delete tree;
    }
    
    exit(EXIT_SUCCESS);
}
