#include "Proposition.h"
using namespace std;

Proposition::Proposition(const string & proposition)
{
    this->proposition = proposition;
}
Proposition::Proposition()
{
    this->proposition = "";
}

string Proposition::getNegation()
{
    if(this->getProposition().back() == '-')
    {
        return this->getProposition().substr(0,this->getProposition().size()-1);
    }
    return (this->proposition + "-");
}

string Proposition::getProposition(){ return this->proposition;}
void Proposition::setProposition(const string & proposition) { this->proposition = proposition;}
void Proposition::simplify()
{


    //############## SIMPLIFIER LES > #############
    unsigned long i = this->proposition.size();
    do
    {
        --i;
        if(this->proposition[i] == '>')
        {
            this->proposition[i] = '-';
            this->proposition.insert(i+1,"|");
            ++i;
        }
        else if(this->proposition[i] == '=')
        {
            string expression1;
            string expression2;
            unsigned cpt = 1;
            unsigned indice = i-1;
            while(cpt != 0)
            {
                expression1.insert(0,1,this->proposition[indice]);
                if(this->proposition[indice] == '&' || this->proposition[indice] == '|') cpt +=1;
                else if(this->proposition[indice] != '-') cpt -=1;
                --indice;
            }
            cpt = 1;
            while(cpt != 0)
            {
                expression2.insert(0,1,this->proposition[indice]);
                if(this->proposition[indice] == '&' || this->proposition[indice] == '|') cpt +=1;
                else if(this->proposition[indice] != '-') cpt -=1;
                --indice;
            }
            this->proposition[i] = '&';
            this->proposition.insert(i+1,expression2 + "-" + expression1 + "-&|");
        }
    }while(i != 0);
 //############## SIMPLIFIER LES - et operateur #############
    i = this->proposition.size();
    do
    {
        --i;
        if(this->proposition[i] == '-' && (this->proposition[i-1] == '&' || this->proposition[i-1] == '|'))
        {
            this->proposition.erase(i,1);
            if(this->proposition[i-1] == '|') this->proposition[i-1] = '&';
            else this->proposition[i-1] = '|';
            int cpt = 2;
            unsigned indice = i-2;
            while(cpt != 0)
            {
                if(this->proposition[indice] == '&' || this->proposition[indice] == '|')
                {
                    if(this->proposition[indice] == '|') this->proposition[indice] = '&';
                    else this->proposition[indice] = '|';
                    cpt += 1;
                }
                else if(this->proposition[indice] != '-')
                {
                    this->proposition.insert(indice+1,"-");
                    ++i;
                    --cpt;
                }
                --indice;
            }
        }
    }while(i != 0);
    //############## SIMPLIFIER LES -- operateur #############
    i = 0;
    while(i < this->proposition.size())
    {

        if(this->proposition[i] == '-' && this->proposition[i+1] == '-')
        {
            this->proposition.erase(i,1);
            this->proposition.erase(i,1);
            --i;
        }
        ++i;
    }
}//simplify()

pair<std::shared_ptr<Proposition>,std::shared_ptr<Proposition>> Proposition::transformInto2Proposition()
{
    string expression1;
    string expression2;


    unsigned cpt = 1;
    unsigned long long indice = this->getProposition().size()-2;
    while(cpt != 0)
    {
        expression1.insert(0,1,this->proposition[indice]);
        if(this->proposition[indice] == '&' || this->proposition[indice] == '|') cpt +=1;
        else if(this->proposition[indice] != '-') cpt -=1;
        --indice;
    }
    cpt = 1;
    while(cpt != 0)
    {
        expression2.insert(0,1,this->proposition[indice]);
        if(this->proposition[indice] == '&' || this->proposition[indice] == '|') cpt +=1;
        else if(this->proposition[indice] != '-') cpt -=1;
        --indice;
    }

    pair<shared_ptr<Proposition> , shared_ptr<Proposition>> newPropositions;
    newPropositions.first = shared_ptr<Proposition>(new Proposition(expression1));
    newPropositions.second = shared_ptr<Proposition>(new Proposition(expression2));
    return newPropositions;
}

