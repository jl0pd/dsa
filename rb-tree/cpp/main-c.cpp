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

    double start = clock();
    RBTree *my_tree = new RBTree(arr);
    double end = clock();

    printf("%lf seconds\n", (end - start)/CLOCKS_PER_SEC);

    delete my_tree;

    exit(EXIT_SUCCESS);
}
