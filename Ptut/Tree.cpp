#include <iostream>
#include "Tree.h"

#include <limits>

#include "infix2postfix.cpp"

using namespace std;

Tree::Tree()
{
    cout << "Rentrez le nombre de proposition que vous voulez les unes apres les autres" << endl
         << "la proposition a demontrer doit commencer par ':' " << endl << endl;

    unsigned cpt = 1;
    string equation;

    while(true)
    {
         cout << "Proposition " << cpt << " : ";
         getline(cin, equation);

         if(equation[0] == ':')
         {
             equation.erase(0,1);
             equation = changeCin(equation);

             myProposalList.push_back(shared_ptr<Proposal>(new Proposal(equation)));
             break;
         }
         equation = changeCin(equation);
         cout << equation << endl;

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
    return myRoot->solve();
}//solve()

void Tree::display()
{
    myRoot->nodeDisplay();
}
