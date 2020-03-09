// Example program
#include <iostream>
#include <string>
#include "Tree.h"
#include "infix2postfix.cpp"
using namespace std;


int main()
{
  Tree arbre = Tree();
  arbre.display();
  if(arbre.solve()) cout << "La resolution est verifiee" << endl;
  else              cout << "La resolution n'est pas verifiee" << endl;

  return 0;


}
