#include <iostream>
#include <string>
#include <vector>

class RBTree
{
private:
    enum color
    {
        red,
        black
    };

    struct Node
    {
        int key;
        int color;
        std::string value;

        struct Node *parent;
        struct Node *left;
        struct Node *right;

        Node()
        {
            this->key = -1;
            this->value.clear();
            this->color = -1;

            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
        }

        Node(int key, int color, std::string value,
            Node *parent, Node *left, Node *right)
        {
            this->key = key;
            this->value = value;
            this->color = color;

            this->parent = parent;
            this->left = left;
            this->right = right;        
        }

        ~Node()
        {
            this->value.clear();
        }

        void print()
        {
            #define RED "\x1b[41m"
            #define BLACK "\x1b[40m"
            #define DEFAULT "\x1b[49m"
            #define DIVIDER "\n~~~~~~~~\n"

            if (this->color)
            {
                std::cout << BLACK <<
                "key: " << this->key <<
                "\nvalue: " << this->value <<
                DEFAULT << DIVIDER;
            }
            else
            {
                std::cout << RED <<
                "key: " << this->key <<
                "\nvalue: " << this->value <<
                DEFAULT << DIVIDER;
            }
            #undef RED
            #undef BLACK
            #undef DEFAULT
            #undef DIVIDER
        }
    };

    Node *root;
    Node *nullNode;
    void add_fixup(Node *node)
    {
        Node *uncle;
        std::cout << "~~~~~~~~~fixupping" << std::endl;

        while (node != this->root && node->parent->color == this->color::red)
        {
            if (node->parent == node->parent->parent->left)
            {
                uncle = node->parent->parent->right;
                if (uncle->color == this->color::red)
                {
                    node->parent->parent->color = this->color::red;
                    node->parent->color = this->color::black;
                    uncle->color = this->color::black;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        this->left_rotate(node);
                    }

                    node->parent->color = this->color::black;
                    node->parent->parent->color = this->color::red;
                    this->right_rotate(node->parent->parent);
                }
            }
            else
            {
                uncle = node->parent->parent->left;
                uncle->print();
                std::cout << "after uncle" << std::endl;
                if (uncle->color == this->color::red)
                {
                    std::cout << "in if" << std::endl;
                
                    node->parent->parent->color = this->color::red;
                    node->parent->color = this->color::black;
                    uncle->color = this->color::black;
                    node = node->parent->parent;
                }
                else
                {
                    std::cout << "in else" << std::endl;
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        this->right_rotate(node);
                    }
                    node->parent->color = this->color::black;
                    node->parent->parent->color = this->color::red;                    
                    this->left_rotate(node->parent->parent);
                }
            }
        }

        this->root->color = this->color::black;

        std::cout << "~~~~~~~~~fixupped" << std::endl;

    }

    void left_rotate(Node *node)
    {
        Node *right = node->right;
        node->right = right->left;

        if (right->left != this->nullNode)
        {
            right->left->parent = node;
        }

        if (right != this->nullNode)
        {
            right->parent = node->parent;
            if (node->parent != this->nullNode)
            {
                if (node->parent != this->nullNode)
                {
                    if (node == node->parent->left)
                    {
                        node->parent->left = right;
                    }
                    else
                    {
                        node->parent->right = right;
                    }
                }
                else
                {
                    this->root = right;
                }
            }
        }

        right->left = node;
        if (node != this->nullNode)
        {
            node->parent = right;
        }
    }

    void right_rotate(Node *node)
    {
        Node *left = node->left;
        node->left = left->right;

        if (left->right != this->nullNode)
        {
            left->right->parent = node;
        }

        if (left != this->nullNode)
        {
            left->parent = node->parent;
            if (node->parent != this->nullNode)
            {
                if (node->parent != this->nullNode)
                {
                    if (node == node->parent->right)
                    {
                        node->parent->right = left;
                    }
                    else
                    {
                        node->parent->left = left;
                    }
                }
                else
                {
                    this->root = left;
                }
            }
        }

        left->right = node;
        if (node != this->nullNode)
        {
            node->parent = left;
        }
    }
    
    void print(Node *root)
    {
        if(root->value[0])
        {
            root->print();
            this->print(root->left);
            this->print(root->right);
        }
    }

    void clear(Node *root)
    {
        if (this->root->value[0])
        {
            this->clear(this->root->left);
            this->clear(this->root->right);
            delete this->root;
        }
    }

    std::string lookup(Node *node, int key)
    {
        if (node->key != key)
        {
            if (key > node->key)
            {
                this->lookup(node->right, key);
            }
            else
            {
                this->lookup(node->left, key);
            }
        }
        else
        {
            return node->value;
        }
    }

public:
    RBTree()
    {
        this->root = new Node();
        this->nullNode = new Node(
            0, this->color::black, std::string(""), NULL, NULL, NULL
        );

        // this->nullNode->parent = this->nullNode->left = this->nullNode->right = this->nullNode;
    }

    RBTree(std::vector<int> array) : RBTree()
    {
        for(int adding : array)
        {
            this->add(adding, std::to_string(adding));
        }
    }

    ~RBTree()
    {
        this->clear();
    }

    std::string lookup(int key)
    {
        if (this->root->key != key)
        {
            if (key > this->root->key)
            {
                this->lookup(this->root->right, key);
            }
            else
            {
                this->lookup(this->root->left, key);
            }
        }
        else
        {
            return this->root->value;
        }
    }

    void clear()
    {
        if (this->root->value[0])
        {
            this->clear(this->root->left);
            this->clear(this->root->right);
            delete this->root;
        }

        delete this->nullNode;
    }

    void add(int key, std::string value)
    {
        Node *node = this->root;
        Node *parent = this->nullNode;

        while (node != this->nullNode && node != NULL)
        {
            parent = node;
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                node = node->right;
            }
            else
            {
                return;
            }
        }

        node = new Node(
                key, this->color::red, value,
                parent, this->nullNode, this->nullNode
            );

        if (parent != nullNode)
        {
            if (key < parent->key)
            {
                parent->left = node;
            }
            else
            {
                parent->right = node;            
            }
        }
        else
        {
            this->root = node;
        }

        this->add_fixup(node);
        std::cout << "~~~~~~~~~added key: " << key << " value: " << value << "\n\n\n\n";

    }

    void print()
    {
        if(this->root->value[0])
        {
            this->root->print();
            this->print(this->root->left);
            this->print(this->root->right);
        }
    }

    std::string min()
    {
        Node *tmp = this->root;
        while(tmp->left != this->nullNode)
        {
            tmp = tmp->left;
        }
        return tmp->value;
    }

    std::string max()
    {
        Node *tmp = this->root;
        while(tmp->right != this->nullNode)
        {
            tmp = tmp->right;
        }
        return tmp->value;
    }

};
