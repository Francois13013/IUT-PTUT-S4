#ifndef TREE_H
#define TREE_H
#include "Node.h"


class Tree
{
private:
    std::shared_ptr<Node> root;
    std::vector<std::shared_ptr<Proposition>> propositionList;

public:
    Tree();
    bool solve();
    void display();

};

#endif // TREE_H
