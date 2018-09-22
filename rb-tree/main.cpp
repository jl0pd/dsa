#include <iostream>
#include <string>

enum clr
{
    red,
    black
};

class RBTree
{
private:
    int key;
    int color;
    std::string value;

    RBTree *parent;
    RBTree *left;
    RBTree *right;
public:
    RBTree(int key, std::string value)
    {
        this->key = key;
        this->value = value;
    }

    void add(RBTree *node)
    {
        
    }
};
