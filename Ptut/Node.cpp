#include "Node.h"
using namespace std;

Node::Node()
{
    this->proposition = shared_ptr<Proposition> (new Proposition());
    this->father = nullptr;
}

Node::Node(const std::shared_ptr<Proposition> & proposition, const shared_ptr<Node> & father)
{
    this->proposition = proposition;
    this->father = father;
}

void Node::addSon(const shared_ptr<Node> & son)
{
    this->sons.push_back(son);
}

//Fonction récursive, on passe en paramètre la proposition à ajouter aux feuilles ainsi que
//le pointeur du fils
void Node::addSonToLastAlpha(const std::shared_ptr<Proposition> & proposition, const shared_ptr<Node> & himself)
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

void Node::addSonToLastBeta(const std::shared_ptr<Proposition> & proposition1,
                            const std::shared_ptr<Proposition> & proposition2,
                            const shared_ptr<Node> & himself)
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
}

bool Node::solve()
{
    //Si il y a un '&' à droite = cas alpha
    //On rajoute les 2 expressions sur tout les fils
    if(this->getProposition().get()->getProposition().back() == '&')
    {
        pair<shared_ptr<Proposition>, shared_ptr<Proposition>> newPropositions
                = this->getProposition().get()->transformInto2Proposition();

        for(shared_ptr<Node> s : this->getSons())
        {
            this->addSonToLastAlpha(newPropositions.first, s);
            this->addSonToLastAlpha(newPropositions.second, s);
        }
    }
    //Si il y a un '|' à droite = cas beta
    //On rajoute les 2 expressions séparés sur tout les fils
    else if(this->getProposition().get()->getProposition().back() == '|')
    {
        pair<shared_ptr<Proposition>, shared_ptr<Proposition>> newPropositions
                = this->getProposition().get()->transformInto2Proposition();

        for(shared_ptr<Node> s : this->getSons())
        {
             this->addSonToLastBeta(newPropositions.first, newPropositions.second, s);
        }
    }
    else if (this->father != nullptr)
    {
        if(this->father->checkNegationInFathers(this->getProposition().get()->getNegation()))return true;

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
        cout << cptSolve << " sur " << this->getSons().size() << "    " << this->getSons()[0]->getProposition()->getProposition() << endl;
        if(cptSolve == this->getSons().size()) return true;
    }
    return false;
}//solve()

bool Node::checkNegationInFathers(const string & test)
{


    if(this->getProposition().get()->getProposition() == test) return true;
    if(this->father != nullptr)
    {
        bool a = this->father->checkNegationInFathers(test);
        return a;
    }
    return false;
}

void Node::display()
{
    cout << this->getProposition().get()->getProposition() << endl;
    for(shared_ptr<Node> s : this->getSons())
    {
        s.get()->display();
    }
}

std::shared_ptr<Proposition>                     Node::getProposition(){return this->proposition;}
std::shared_ptr<Node>              Node::getFather()       {return this->father;}
std::vector<std::shared_ptr<Node>> Node::getSons()         {return this->sons;}
