/**
* Proposal.h
*
* 03/03/2020
*
* v1.1
*/
#ifndef PROPOSAL_H
#define PROPOSAL_H
//--------------------------------------------------------------------------------------------------------
//  INCLUDES
//--------------------------------------------------------------------------------------------------------
#include <iostream>
#include <utility>
#include <memory>

/**
 * classe Proposition
 * proposition logique du type -(a|b)>c&d
 *
 * myData : proposition logique
 */
class Proposal
{
private:
    std::string myData;
public:
//---------------------------------------------------------------------------------------------------------
//  CONSTRUCTEUR / DESTRUCTEUR
//---------------------------------------------------------------------------------------------------------
    Proposal(const std::string & data = "");
    ~Proposal() {}
//---------------------------------------------------------------------------------------------------------
// GETTERS / SETTERS
//---------------------------------------------------------------------------------------------------------
    const std::string & getData();
    const std::string & getNegation();
    void  setData(const std::string & data);
//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------
    void simplify();

    // /!\ plus de pointeurs
    std::pair<Proposal,Proposal> transformInto2Proposal();

};

#endif // PROPOSAL_H
