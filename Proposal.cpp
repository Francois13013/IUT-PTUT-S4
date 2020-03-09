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

string  Proposal::getNegation()
{
    if(this->getData().back() == '-')
    {
        return this->getData().substr(0,this->getData().size()-1);
    }
    return (myData + "-");
}

//const vector<shared_ptr<Node>> & Proposal::getProposalList() {}

//---------------------------------------------------------------------------------------------------------
// METHODES
//---------------------------------------------------------------------------------------------------------
void Proposal::simplify()
{


    //############## SIMPLIFIER LES > #############
    unsigned long i = myData.size();
    do
    {
        --i;
        if(myData[i] == '>')
        {
            myData[i] = '-';
            myData.insert(i+1,"|");
            ++i;
        }
        else if(myData[i] == '=')
        {
            string expression1;
            string expression2;
            unsigned cpt = 1;
            unsigned indice = i-1;
            while(cpt != 0)
            {
                expression1.insert(0,1,myData[indice]);
                if(myData[indice] == '&' || myData[indice] == '|') cpt +=1;
                else if(myData[indice] != '-') cpt -=1;
                --indice;
            }
            cpt = 1;
            while(cpt != 0)
            {
                expression2.insert(0,1,myData[indice]);
                if(myData[indice] == '&' || myData[indice] == '|') cpt +=1;
                else if(myData[indice] != '-') cpt -=1;
                --indice;
            }
            myData[i] = '&';
            myData.insert(i+1,expression2 + "-" + expression1 + "-&|");
        }
    }while(i != 0);
 //############## SIMPLIFIER LES - et operateur #############
    i = myData.size();
    do
    {
        --i;
        if(myData[i] == '-' && (myData[i-1] == '&' || myData[i-1] == '|'))
        {
            myData.erase(i,1);
            if(myData[i-1] == '|') myData[i-1] = '&';
            else myData[i-1] = '|';
            int cpt = 2;
            unsigned indice = i-2;
            while(cpt != 0)
            {
                if(this->myData[indice] == '&' ||this->myData[indice] == '|')
                {
                    if(this->myData[indice] == '|') myData[indice] = '&';
                    else myData[indice] = '|';
                    cpt += 1;
                }
                else if(myData[indice] != '-')
                {
                    myData.insert(indice+1,"-");
                    ++i;
                    --cpt;
                }
                --indice;
            }
        }
    }while(i != 0);
    //############## SIMPLIFIER LES -- operateur #############
    i = 0;
    while(i < myData.size())
    {

        if(myData[i] == '-' && myData[i+1] == '-')
        {
            myData.erase(i,1);
            myData.erase(i,1);
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
        expression1.insert(0,1,myData[indice]);
        if(myData[indice] == '&' || myData[indice] == '|') cpt +=1;
        else if(myData[indice] != '-') cpt -=1;
        --indice;
    }
    cpt = 1;
    while(cpt != 0)
    {
        expression2.insert(0,1,myData[indice]);
        if(myData[indice] == '&' || myData[indice] == '|') cpt +=1;
        else if(myData[indice] != '-') cpt -=1;
        --indice;
    }

    pair<Proposal , Proposal> newProposals;
    newProposals.first  = /*shared_ptr<Proposal>*/Proposal(expression1);
    newProposals.second = /*shared_ptr<Proposal> */Proposal(expression2);
    return newProposals;
}

