#ifndef PROPOSITION_H
#define PROPOSITION_H
#include <iostream>
#include <utility>
#include <memory>

class Proposition
{
private:
    std::string proposition;
public:
    Proposition();
    Proposition(const std::string & proposition);
    void simplify();
    std::string getProposition();
    std::string getNegation();
    void setProposition(const std::string & proposition);
    std::pair<std::shared_ptr<Proposition>,std::shared_ptr<Proposition>> transformInto2Proposition();

};

#endif // PROPOSITION_H
