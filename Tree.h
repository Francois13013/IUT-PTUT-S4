/**
 * Tree.h
 *
 * 03/03/2020
 *
 * v1.1
 *
 */
#ifndef TREE_H
#define TREE_H
//--------------------------------------------------------------------------------------------------------
//  INCLUDES
//--------------------------------------------------------------------------------------------------------
#include "Node.h"
/**
 * Classe Tree
 * classe d'un arbre composé de noeuds de propositions
 *
 * myRoot : racine de l'abre
 * myProposallist : liste des propositions
 */
class Tree
{
private:
    std::shared_ptr<Node> 				   myRoot;
    std::vector<std::shared_ptr<Proposal>> myProposalList;
public:
//---------------------------------------------------------------------------------------------------------
//  CONSTRUCTEUR / DESTRUCTEUR
//---------------------------------------------------------------------------------------------------------
    Tree();
    ~Tree(){}
//---------------------------------------------------------------------------------------------------------
//  GETTERS / SETTERS
//---------------------------------------------------------------------------------------------------------
    const std::shared_ptr<Node> & getRoot();
    const std::vector<std::shared_ptr<Proposal>> & getProposalList();
    void setRoot(std::shared_ptr<Node> & root);
//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------
    bool solve();
    void display();
};
#endif // TREE_H
