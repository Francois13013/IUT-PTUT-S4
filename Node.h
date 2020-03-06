/*
 * Node.h
 *
 * 03/03/2020
 *
 * v1.1
 *
 **/
#ifndef NODE_H
#define NODE_H
//--------------------------------------------------------------------------------------------------------
//  INCLUDES
//--------------------------------------------------------------------------------------------------------
#include <vector>
#include "Proposal.h"
/**
 * classe Node
 * noeud d'un arbre
 *
 * myPropostion : pointeur  vers la propostion propositions
 * myFather     : prointeur vers le Noeud père du noeud actuel
 * mySons       : propositon contenue dans le noeud
 *
 */
class Node
{
private:
    Proposal                           myProposal;
    std::shared_ptr<Node>              myFather;
    std::vector<std::shared_ptr<Node>> mySons;
public:
//---------------------------------------------------------------------------------------------------------
//  CONSTRUCTEUR / DESTRUCTEUR
//---------------------------------------------------------------------------------------------------------
    Node(const Proposal & proposal, const std::shared_ptr<Node> & father = nullptr);
    ~Node(){}
//---------------------------------------------------------------------------------------------------------
// GETTERS / SETTERS
//---------------------------------------------------------------------------------------------------------
    const Proposal               &      getProposal();
    const std::shared_ptr<Node>  &      getFather();
    const std::vector<std::shared_ptr<Node>> &  getSons();

    void setProposal(const Proposal & newProposal);
    void setFather  (const std::vector<std::shared_ptr<Node>> & newFather);
    void setSons	(const std::vector<std::shared_ptr<Node>> & newSons);
//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------
    /**
     * ajoute un fils au noeud
     */
    void addSon(const std::shared_ptr<Node> & son);

    void addSonToLastAlpha(const Proposal & proposition,
                           const std::shared_ptr<Node> & himself);

    void addSonToLastBeta(const Proposal & proposition1,
                          const Proposal & proposition2,
                         const std::shared_ptr<Node> & himself);

    bool checkNegationInFathers(const std::string & proposition);

    bool solve();

    void display();
};

#endif // NODE_H
