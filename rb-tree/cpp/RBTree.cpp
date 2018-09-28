#include <iostream>
#include <string>
#include <vector>
#include <exception>

class RBTree
{
private:
    enum color
    {
        red,
        black,
        doubleBlack
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

            if (this->color)
            {
                std::cout << BLACK <<
                "key: " << this->key <<
                "\nvalue: " << this->value <<
                DEFAULT << std::endl;
            }
            else
            {
                std::cout << RED <<
                "key: " << this->key <<
                "\nvalue: " << this->value <<
                DEFAULT << std::endl;
            }
            #undef RED
            #undef BLACK
            #undef DEFAULT
        }
    };

    Node *root;
    Node *nullNode;
    void add_fixup(Node *node)
    {
        Node *uncle;
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
                if (uncle->color == this->color::red)
                {
                    node->parent->parent->color = this->color::red;
                    node->parent->color = this->color::black;
                    uncle->color = this->color::black;
                    node = node->parent->parent;
                }
                else
                {
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
        }

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
        }

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
    
        left->right = node;
        if (node != this->nullNode)
        {
            node->parent = left;
        }
    }
    
    void print(Node *node)
    {
        if(node != this->nullNode)
        {
            node->print();
            this->print(node->left);
            this->print(node->right);
        }
        else
        {
            std::cout << "\n~~~~~~~~~\n";
        }
    }

    void clear(Node *node)
    {
        if (node != this->nullNode)
        {
            this->clear(node->left);
            this->clear(node->right);
            delete node;
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

    Node* del_node(Node *node, int key)
    {
        if (node == this->nullNode)
            return node;

        if (key < node->key)
            return del_node(node->left, key);

        if (key > node->key)
            del_node(node->right, key);

        if (node->left == this->nullNode || node->right == this->nullNode)
            return node;

        Node *temp = this->get_min_node(node->right);
        node->key = temp->key;

        return del_node(node->right, temp->key);
    }

    void del_fixup(Node *node)
    { 
        if (node == this->nullNode)
            return;

        if (node == root) {
            root = this->nullNode;
            return;
        }

        if (node->color == this->color::red || node->left->color == this->color::red || node->right->color == this->color::red)
        {
            Node *child = node->left != this->nullNode ? node->left : node->right;

            if (node == node->parent->left)
            {
                node->parent->left = child;
                if (child != this->nullNode)
                {
                    child->parent = node->parent;
                }
                child->color = this->color::black;
                delete node;
            }
            else
            {
                node->parent->right = child;
                if (child != this->nullNode)
                {
                    child->parent = node->parent;
                }
                child->color = this->color::black;
                delete node;
            }
        }
        else
        {
            Node *sibling = this->nullNode;
            Node *parent = this->nullNode;
            Node *ptr = node;
            ptr->color = this->color::doubleBlack;
            while (ptr != root && ptr->color == this->color::doubleBlack) {
                parent = ptr->parent;
                if (ptr == parent->left)
                {
                    sibling = parent->right;
                    if (sibling->color == this->color::red)
                    {
                        sibling->color = this->color::black;
                        parent->color = this->color::red;
                        this->left_rotate(parent);
                    }
                    else
                    {
                        if (sibling->left->color == this->color::black && sibling->right->color == this->color::black)
                        {
                            sibling->color = this->color::red;
                            if(parent->color == this->color::red)
                            {
                                parent->color = this->color::black;
                            }
                            else
                            {
                                parent->color = this->color::doubleBlack;
                            }
                            ptr = parent;
                        }
                        else
                        {
                            if (sibling->right->color == this->color::black)
                            {
                                sibling->left->color = this->color::black;
                                sibling->color = this->color::red;
                                this->right_rotate(sibling);
                                sibling = parent->right;
                            }
                            sibling->color = parent->color;
                            parent->color = this->color::black;
                            sibling->right->color = this->color::black;
                            this->left_rotate(parent);
                            break;
                        }
                    }
                }
                else
                {
                    sibling = parent->left;
                    if (sibling->color == this->color::red)
                    {
                        sibling->color = this->color::black;
                        parent->color = this->color::red;
                        this->right_rotate(parent);
                    }
                    else
                    {
                        if (sibling->left->color == this->color::black && sibling->right->color == this->color::black)
                        {
                            sibling->color = this->color::red;
                            if (parent->color == this->color::red)
                            {
                                parent->color = this->color::black;
                            }
                            else
                            {
                                parent->color = this->color::doubleBlack;
                            }
                            ptr = parent;
                        }
                        else
                        {
                            if (sibling->left->color == this->color::black)
                            {
                                sibling->right->color = this->color::black;
                                sibling->color = this->color::red;
                                this->left_rotate(sibling);
                                sibling = parent->left;
                            }
                            sibling->color = parent->color;
                            parent->color = this->color::black;
                            sibling->left->color = this->color::black;
                            this->right_rotate(parent);
                            break;
                        }
                    }
                }
            }

            if (node == node->parent->left)
            {
                node->parent->left = this->nullNode;
            }
            else
            {
                node->parent->right = this->nullNode;
            }
            delete node;

            this->root->color = this->color::black;
        }
    }

    Node* get_min_node(Node *node)
    {
        while (node->left != this->nullNode)
            node = node->left;

        return node;
    }

public:
    RBTree()
    {
        this->nullNode = new Node(
            0, this->color::black, std::string(""), NULL, NULL, NULL
        );

        this->root = this->nullNode;
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
        if (this->root != this->nullNode)
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
    }

    void print()
    {
        if(this->root != this->nullNode)
        {
            this->root->print();
            this->print(this->root->left);
            this->print(this->root->right);
        }
        else
        {
            std::cout << "~~~~~~~~~\n";
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
    
    void del(int key)
    {
        Node *node = del_node(this->root, key);
        del_fixup(node);
    }

};


// class trash
// {
// /*
//     void del(int key)
//     {
//         if(root==NULL)
//         {
//             return;
//         }

//         Node *p = this->root;

//         Node *y = NULL;
//         Node *node = NULL;

//         int found = 0;

//         while(p != NULL && found == 0)
//         {
//             if(p->key == key)
//             {
//                 found = 1;
//             }

//             if(found == 0)
//             {
//                 if(p->key < key)
//                     p = p->right;
//                 else
//                     p = p->left;
//             }
//         }

//         if(found == 0)
//         {
//             throw std::exception();
//         }
//         else
//         {
//             if(p->left == NULL || p->right == NULL)
//             {
//                 y = p;
//             }
//             else
//             {
//                 y = successor(p);
//             }

//             if(y->left!=NULL)
//             {           
//                 node=y->left;
//             }
//             else
//             {
//                 if(y->right!=NULL)
//                 { 
//                     node=y->right;
//                 }
//                 else
//                 {
//                     node=NULL;
//                 }
//             }
            
//             if(node!=NULL)
//             {
//                 node->parent=y->parent;
//             }

//             if(y->parent==NULL)
//             {
//                 root=node;
//             }
//             else
//             {
//                 if(y==y->parent->left)
//                 {
//                     y->parent->left=node;
//                 }
//                 else
//                 {
//                     y->parent->right=node;
//                 }
//             }

//             if(y!=p)
//             {
//                 p->color=y->color;
//                 p->key=y->key;
//             }

//             if(y->color=='b')
//                 delfix(node);
//         }
//     }

//     void delfix(Node *p)
//     {
//         node *s;
//         while(p!=root&&p->color=='b')
//         {
//             if(p->parent->left==p)
//             {
//                     s=p->parent->right;
//                     if(s->color=='r')
//                     {
//                             s->color='b';
//                             p->parent->color='r';
//                             leftrotate(p->parent);
//                             s=p->parent->right;
//                     }
//                     if(s->right->color=='b'&&s->left->color=='b')
//                     {
//                             s->color='r';
//                             p=p->parent;
//                     }
//                     else
//                     {
//                         if(s->right->color=='b')
//                         {
//                                 s->left->color=='b';
//                                 s->color='r';
//                                 rightrotate(s);
//                                 s=p->parent->right;
//                         }
//                         s->color=p->parent->color;
//                         p->parent->color='b';
//                         s->right->color='b';
//                         leftrotate(p->parent);
//                         p=root;
//                     }
//             }
//             else
//             {
//                     s=p->parent->left;
//                     if(s->color=='r')
//                     {
//                             s->color='b';
//                             p->parent->color='r';
//                             rightrotate(p->parent);
//                             s=p->parent->left;
//                     }
//                     if(s->left->color=='b'&&s->right->color=='b')
//                     {
//                             s->color='r';
//                             p=p->parent;
//                     }
//                     else
//                     {
//                             if(s->left->color=='b')
//                             {
//                                 s->right->color='b';
//                                 s->color='r';
//                                 leftrotate(s);
//                                 s=p->parent->left;
//                             }
//                             s->color=p->parent->color;
//                             p->parent->color='b';
//                             s->left->color='b';
//                             rightrotate(p->parent);
//                             p=root;
//                     }
//             }
//         p->color='b';
//         root->color='b';
//         }
//     }

//     node* RBtree::successor(node *p)
//     {
//         node *y=NULL;
//         if(p->left!=NULL)
//         {
//             y=p->left;
//             while(y->right!=NULL)
//                 y=y->right;
//         }
//         else
//         {
//             y=p->right;
//             while(y->left!=NULL)
//                 y=y->left;
//         }
//         return y;
//     }
// */
// };
