/**
 *
 * Node.cpp
 *
 */

#include "Node.h"

using namespace std;
//---------------------------------------------------------------------------------------------------------
// CONSTRUCTEUR
//---------------------------------------------------------------------------------------------------------
Node::Node(const Proposal & proposal, const std::shared_ptr<Node> & father) : myProposal(proposal),
                                                                              myFather(father){}
//---------------------------------------------------------------------------------------------------------
// GETTERS / SETTERS
//---------------------------------------------------------------------------------------------------------
const Proposal 			    & Node::getProposal() 			{return myProposal;}
const std::shared_ptr<Node> & Node::getFather()   			{return myFather;}
const std::vector<std::shared_ptr<Node>> &  Node::getSons() {return mySons;}

void Node::setProposal(const Proposal & proposal) 							{myProposal = proposal;}
void Node::setSons	(const std::vector<std::shared_ptr<Node>> & newSons)	{mySons = newSons;}
//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------

void Node::addSon(const std::shared_ptr<Node> & son)
{
    vector<shared_ptr<Node>> tmp = this->getSons();
    tmp.push_back(son);
    this->setSons(tmp);
}//addSon()

//Fonction récursive, on passe en paramètre la proposition à ajouter aux feuilles ainsi que
//le pointeur du fils
void Node::addSonToLastAlpha(const Proposal & proposition,
                       const std::shared_ptr<Node> & himself)
{
    if(this->getSons().size() == 0)
        {
            this->addSon(shared_ptr<Node>(new Node(proposition,himself)));
        }
        else
        {
            for(shared_ptr<Node> s : this->getSons())
            {
                s.get()->addSonToLastAlpha(proposition,s);
            }
        }
}//addSonToLastAlpha()


void Node::addSonToLastBeta(const Proposal & proposition1,
                            const Proposal & proposition2,
                            const std::shared_ptr<Node> & himself)
{
    if(this->getSons().size() == 0)
        {
            this->addSon(shared_ptr<Node>(new Node(proposition1,himself)));
            this->addSon(shared_ptr<Node>(new Node(proposition2,himself)));
        }
        else
        {
            for(shared_ptr<Node> s : this->getSons())
            {
                s.get()->addSonToLastBeta(proposition1, proposition2,s);
            }
        }
}//addSonToLastBeta()

bool Node::checkNegationInFathers(const std::string & test)
{

    Proposal proposal = this->getProposal();
    string 	 data	  = proposal.getData();

    if(data == test) return true;
    if(myFather != nullptr)
    {
        bool a = myFather->checkNegationInFathers(test);
        return a;
    }
    return false;
}//checkNegationInFathers()

bool Node::solve()
{
        //Si il y a un '&' à droite = cas alpha
        //On rajoute les 2 expressions sur tout les fils
        Proposal proposal  = this->getProposal();
        string   data      = proposal.getData();
        if(data.back() == '&')
        {
            pair<Proposal, Proposal> newProposals
                    = proposal.transformInto2Proposal();


            for(shared_ptr<Node> s : this->getSons())
            {
                this->addSonToLastAlpha(newProposals.first, s);
                this->addSonToLastAlpha(newProposals.second, s);
            }
        }
        //Si il y a un '|' à droite = cas beta
        //On rajoute les 2 expressions séparés sur tout les fils
        else if(data.back() == '|')
        {
            pair<Proposal, Proposal> newProposals
                    = proposal.transformInto2Proposal();

            for(shared_ptr<Node> s : this->getSons())
            {
                 this->addSonToLastBeta(newProposals.first, newProposals.second, s);
            }
        }
        else if (myFather != nullptr)
        {
            if(myFather->checkNegationInFathers(proposal.getNegation()))
                return true;
        }


        unsigned cptSolve = 0;
        bool result;
        if(this->getSons().size() !=0)
        {
            for(shared_ptr<Node> son : this->getSons())
            {
                result = son->solve();
                if(result) ++cptSolve;
            }
            if(cptSolve == this->getSons().size()) return true;
        }
        return false;
}//solve()

void Node::nodeDisplay()
{
    for (shared_ptr<Node> ptr : mySons)
    {
        Proposal tmp = ptr->getProposal();
        cout << "\t" << tmp.getData() << endl;
    }
}//display()
