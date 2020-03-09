#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree()
{
    unsigned cpt = 1;
    string equation;
    while(true)
    {
         cout << "Proposition " << cpt << " : ";
         getline(cin, equation);
         if(equation[0] == ':')
         {
             equation.erase(0,1);
             myProposalList.push_back(shared_ptr<Proposal>(new Proposal(equation)));
             break;
         }
         myProposalList.push_back(shared_ptr<Proposal>(new Proposal(equation)));
         ++ cpt;
    }

    //La dernière valeur rentré est celle qu'on cherche à démontrer
    //Pour faire une démonstration par l'absurde on transforme cette valeur par sa négation
    shared_ptr<Proposal> tmp = myProposalList.back();

    tmp->setData(tmp->getNegation());

    //On simplifie toutes les propositions
    for(shared_ptr<Proposal> p : myProposalList)
    {
        p.get()->simplify();
    }
    //Création de la racine
    myRoot = shared_ptr<Node> (new Node ((*getProposalList()[0])));

    //On ajoute ensuite toutes les propositions
    for (unsigned i(1); i < this->myProposalList.size(); ++i)
    {
        // permet d'ajouter à la fin
        myRoot->addSonToLastAlpha((*myProposalList[i]), this->myRoot);
    }


}//Tree()

const std::vector<std::shared_ptr<Proposal>> & Tree::getProposalList() {return myProposalList;}

bool Tree::solve()
{
    return this->myRoot->solve();
}//solve()

void Tree::display()
{
    //TODO
}
