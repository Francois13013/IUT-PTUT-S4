#ifndef NODE_H
#define NODE_H
#include <vector>
#include "Proposition.h"


class Node
{
private:
    std::shared_ptr<Proposition> proposition;
    std::shared_ptr<Node> father;
    std::vector<std::shared_ptr<Node>> sons;
public:
    Node();
    Node(const std::shared_ptr<Proposition> & proposition, const std::shared_ptr<Node> & father);
    ~Node(){}
    std::shared_ptr<Proposition>       getProposition();
    std::shared_ptr<Node>              getFather();
    std::vector<std::shared_ptr<Node>> getSons();
    void                               addSon(const std::shared_ptr<Node> & son);
    void addSonToLastAlpha(const std::shared_ptr<Proposition> & proposition,
                           const std::shared_ptr<Node> & himself);
    void addSonToLastBeta(const std::shared_ptr<Proposition> & proposition1,
                          const std::shared_ptr<Proposition> & proposition2,
                          const std::shared_ptr<Node> & himself);
    bool checkNegationInFathers(const std::string & proposition);
    bool solve();
    void display();
};

#endif // NODE_H
