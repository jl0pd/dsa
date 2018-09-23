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
    for(int i = 1; i < 2; i++){
        arr.push_back(i);
    }

    std::cout << "before init" << std::endl;
    RBTree *my_tree = new RBTree(arr);
    // RBTree *my_tree = new RBTree();
    // my_tree->add(10, "10");
    std::cout << "after init" << std::endl;


    my_tree->print();

    delete my_tree;

    exit(EXIT_SUCCESS);
}
