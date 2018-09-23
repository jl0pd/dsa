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
    for(int i = 1; i < 10; i++){
        arr.push_back(i);
    }

    RBTree *my_tree = new RBTree(arr);

    my_tree->print();

    delete my_tree;

    exit(EXIT_SUCCESS);
}
