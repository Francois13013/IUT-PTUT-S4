#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;


int main()
{
  Tree arbre = Tree();

  if(arbre.solve())
      cout << "La resolution est verifiee" << endl;
  else
      cout << "La resolution n'est pas verifiee" << endl;

  arbre.display();
  return 0;
}



