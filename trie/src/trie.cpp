#include <string>
#include <iostream>
#include <map>

class Trie
{
private:
    struct Node
    {
        char sym;
        int value;
        std::map<char, Node*> childs;
    
        Node()
        {
            this->value = -1;
            this->sym = -1;
        }

        Node(char sym) : Node()
        {
            this->sym = sym;
        }

        Node(char sym, int value) : Node(sym)
        {
            this->value = value;
        }

        ~Node()
        {
            this->childs.clear();
        }

        void set_value(int value)
        {
            this->value = value;
        }

        int get_value()
        {
            return this->value;
        }

        void add_child(char sym)
        {
            Node *node = new Node(sym);
            this->childs.insert(std::pair<char, Node*>(sym, node));
        }
    };

    std::map<char, Node*> root;

    void show(Node *node, int level)
    {
        for (auto &pair : node->childs)
        {
            for (int i = 0; i < level; i++)
            {
                std::cout << ' ';
            }

            std::cout << pair.first << std::endl;
            this->show(pair.second, level + 1);
        }
    }

public:
    Trie(){}

    ~Trie()
    {
        this->root.clear();
    }

    void insert(std::string key, int value)
    {
        std::map<char, Node*> *tmp = &this->root;
        for (int i = 0; i < key.size() - 1; i++)
        {
            char c = key[i];
            if (tmp->find(c) == tmp->end())
            {
                tmp->insert(std::pair<char, Node*>(c, new Node(c)));
            }
            else if (tmp->find(c) != NULL)
            {
                tmp = &tmp[c];
                continue;
            }
            else
            {
                tmp->insert(std::pair<char, Node*>(c, new Node(c, value)));
            }
            tmp = &tmp[c];

        }
    }

    int lookup(std::string key)
    {
        Node *tmp = this->root[key[0]];
        for (char c : key)
        {
            tmp = tmp->childs[c];
        }

        return tmp->value;
    }

    void del(std::string key)
    {

    }

    void show()
    {
        for (auto &pair : this->root)
        {
            std::cout << pair.first <<  std::endl;
            this->show(pair.second, 1);
        }
    }
};