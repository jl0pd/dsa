#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <vector>

#include "RBTree.cpp"

int main(int argc, char **argv)
{
    srand(time(NULL));

    std::vector<int> arr;

    int size = 20000000;
    for(int i = 1; i < size; i++)
    {
        arr.push_back(rand() % size);
    }

    double start = clock();
    RBTree *tree = new RBTree(arr);
    double end = clock();
    double diff = end - start;
    
    fprintf(stdout, "%d\t%3.10f\n", size, (diff/CLOCKS_PER_SEC));
    
    exit(EXIT_SUCCESS);
}
