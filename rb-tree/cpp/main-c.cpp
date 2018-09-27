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
        arr.push_back(rand() % 100);
    }

    // std::vector<int> arr = {11, 2, 7, 5, 8, 1, 14, 15};

    RBTree *my_tree = new RBTree(arr);

    my_tree->print();

    std::cout << my_tree->min() << " <-min || max-> " << my_tree->max() << std::endl;

    delete my_tree;

    exit(EXIT_SUCCESS);
}
