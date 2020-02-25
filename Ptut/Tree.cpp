#include "Tree.h"
#include <iostream>
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
             this->propositionList.push_back(shared_ptr<Proposition>(new Proposition(equation)));
             break;
         }
         this->propositionList.push_back(shared_ptr<Proposition>(new Proposition(equation)));
         ++ cpt;
    }

    //La dernière valeur rentré est celle qu'on cherche à démontrer
    //Pour faire une démonstration par l'absurde on transforme cette valeur par sa négation
    this->propositionList.back().get()->setProposition(this->propositionList.back().get()->getNegation());

    //On simplifie toutes les propositions
    for(shared_ptr<Proposition> p : this->propositionList)
    {
        p.get()->simplify();
    }
    //Création de la racine
    this->root = shared_ptr<Node> (new Node (this->propositionList[0],nullptr));

    //On ajoute ensuite toutes les propositions
    for (unsigned i(1); i < this->propositionList.size(); ++i)
    {
        // permet d'ajouter à la fin
        this->root->addSonToLastAlpha(this->propositionList[i], this->root);
    }


}

bool Tree::solve()
{
    return this->root->solve();
}

void Tree::display(){ this->root->display(); }

