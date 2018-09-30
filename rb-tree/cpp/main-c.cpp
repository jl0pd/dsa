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

    FILE *f = fopen("results.txt", "w+");
    fprintf(f, "#\t\t1\n");
    fclose(f);

    int iter_count = 5;

    for(int size = 100000; size <= 2000000; size+=100000)
    {
        f = fopen("results.txt", "a");

        for(int i = 1; i < size; i++)
        {
            arr.push_back(rand() % size);
        }

        std::vector<RBTree *> trees;
        double diff = 0;
        std::cout << "processing: " << size << std::endl;
        for(int i = 0; i < iter_count; i++)
        {
            double start = clock();
            trees.push_back(new RBTree(arr));
            double end = clock();
            diff += end - start;
        }
        fprintf(f, "%d\t%lf\n", size, (diff/iter_count)/CLOCKS_PER_SEC);
        fclose(f);

        for(auto tree : trees)
        {
            delete tree;
        }
    }
    
    exit(EXIT_SUCCESS);
}
