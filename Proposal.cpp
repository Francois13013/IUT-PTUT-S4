/**
*
* Proposal.cpp
*
*/

#include "Proposal.h"
using namespace std;

//---------------------------------------------------------------------------------------------------------
// CONSTRUCTEUR
//---------------------------------------------------------------------------------------------------------
Proposal::Proposal(const string & proposal) :myData(proposal) {}



//---------------------------------------------------------------------------------------------------------
//  GETTERS / SETTERS
//---------------------------------------------------------------------------------------------------------
const string & Proposal::getData()                  {return myData;}
void Proposal::setData(const string & Proposal)     {myData = Proposal;}

const string & Proposal::getNegation()
{
    if(this->getData().back() == '-')
    {
        return this->getData().substr(0,this->getData().size()-1);
    }
    return (this->myData + "-");
}

const vector<shared_ptr<Node>> & Proposal::getProposalList() {}

//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------
void Proposal::simplify()
{


    //############## SIMPLIFIER LES > #############
    unsigned long i = this->myData.size();
    do
    {
        --i;
        if(this->myData[i] == '>')
        {
            this->myData[i] = '-';
            this->myData.insert(i+1,"|");
            ++i;
        }
        else if(this->myData[i] == '=')
        {
            string expression1;
            string expression2;
            unsigned cpt = 1;
            unsigned indice = i-1;
            while(cpt != 0)
            {
                expression1.insert(0,1,this->myData[indice]);
                if(this->myData[indice] == '&' || this->myData[indice] == '|') cpt +=1;
                else if(this->myData[indice] != '-') cpt -=1;
                --indice;
            }
            cpt = 1;
            while(cpt != 0)
            {
                expression2.insert(0,1,this->myData[indice]);
                if(this->myData[indice] == '&' || this->myData[indice] == '|') cpt +=1;
                else if(this->myData[indice] != '-') cpt -=1;
                --indice;
            }
            this->myData[i] = '&';
            this->myData.insert(i+1,expression2 + "-" + expression1 + "-&|");
        }
    }while(i != 0);
 //############## SIMPLIFIER LES - et operateur #############
    i = this->myData.size();
    do
    {
        --i;
        if(this->myData[i] == '-' && (this->myData[i-1] == '&' || this->myData[i-1] == '|'))
        {
            this->myData.erase(i,1);
            if(this->myData[i-1] == '|') this->myData[i-1] = '&';
            else this->myData[i-1] = '|';
            int cpt = 2;
            unsigned indice = i-2;
            while(cpt != 0)
            {
                if(this->myData[indice] == '&' || this->myData[indice] == '|')
                {
                    if(this->myData[indice] == '|') this->myData[indice] = '&';
                    else this->myData[indice] = '|';
                    cpt += 1;
                }
                else if(this->myData[indice] != '-')
                {
                    this->myData.insert(indice+1,"-");
                    ++i;
                    --cpt;
                }
                --indice;
            }
        }
    }while(i != 0);
    //############## SIMPLIFIER LES -- operateur #############
    i = 0;
    while(i < this->myData.size())
    {

        if(this->myData[i] == '-' && this->myData[i+1] == '-')
        {
            this->myData.erase(i,1);
            this->myData.erase(i,1);
            --i;
        }const std::string & getData();
        const std::string & getNegation();
        void  setData(const std::string & data);
        ++i;const std::string & getData();
        const std::string & getNegation();
        void  setData(const std::string & data);
    }const std::string & getData();
    const std::string & getNegation();
    void  setData(const std::string & data);
}//simplify()

const std::string & getData();
const std::string & getNegation();
void  setData(const std::string & data);


pair<Proposal,Proposal> Proposal::transformInto2Proposal()
{
    string expression1;
    string expression2;

    unsigned cpt = 1;
    unsigned long long indice = this->getData().size()-2;
    while(cpt != 0)
    {
        expression1.insert(0,1,this->myData[indice]);
        if(this->myData[indice] == '&' || this->myData[indice] == '|') cpt +=1;
        else if(this->myData[indice] != '-') cpt -=1;
        --indice;
    }
    cpt = 1;
    while(cpt != 0)
    {
        expression2.insert(0,1,this->myData[indice]);
        if(this->myData[indice] == '&' || this->myData[indice] == '|') cpt +=1;
        else if(this->myData[indice] != '-') cpt -=1;
        --indice;
    }

    pair<Proposal , Proposal> newProposals;
    newProposals.first  = /*shared_ptr<Proposal>*/Proposal(expression1);
    newProposals.second = /*shared_ptr<Proposal> */Proposal(expression2);
    return newProposals;
}

