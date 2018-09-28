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

    for(int i = 1; i < 50000; i++)
    {
        arr.push_back(rand() % 100);
    }


    double diff = 0;

    std::vector<RBTree *> trees;
    for(int i = 0; i < 200; i++)
    {
        double start = clock();
        trees.push_back(new RBTree(arr));
        double end = clock();
        diff += end - start;
    }
    
    printf("%lf seconds\n", (diff/200)/CLOCKS_PER_SEC);

    for(auto tree : trees)
    {
        delete tree;
    }

    trees.clear();

    exit(EXIT_SUCCESS);
}
