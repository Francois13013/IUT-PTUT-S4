// -----------------------------------------------------------------------------
// Transformation d'une formule logique infixe en forme postfixe
// 10/02/2020, V. Risch, J. Pouzargues
//
// Le code initial a été conçu pour du C, l'utilisant en C++, il a été traduit
// et les piles ont été remplacés par des string afin de faciliter l'utilisation pour notre démonstrateur.
//
// Le programme recupere une formule logique en forme infixe donnee sous la
// forme d'une string formuleInfixe pour la transmettre a la fonction
// Infix2prefix qui la transforme en forme postfixe. Infix2Prefix gere deux
// string : une string des operateurs et formulePostfixe vue
// initialement comme string des operandes a laquelle les operateurs sont ajoutes
// au fur et a mesure qu'ils sont enlevés de operateurs. Les operandes sont
// tout caractere minuscule entre 'a' et 'z', les operateurs sont
// '#': modalite []
// '%': modalite <>
// '-': negation
// '&': et
// '|': ou
// '>': implique
// '=': equivalent
// issus de l'analyse syntaxique de la formule initialement entree par
// l'utilisateur (par exemple sous la forme a & (-[]b => <>c).
// -----------------------------------------------------------------------------

#include <iostream>
using namespace std;
// #include <stdlib.h>

// -----------------------------------------------------------------------------
// Transformation Infix2prefix
// -----------------------------------------------------------------------------

int Precedence(char c) {
  // Renvoie le degre de precedence de l'operateur c

  switch(c) {
    case '#':         // modalite []
    case '%':         // modalite <>
    case '-':         // negation
      return 1;
      break;
    case '&':         // et
    case '|':         // ou
    case '>':         // implique
    case '=':         // equivalent
      return 0;
      break;
  default : return 0;
  }
}

int IsOperator(char c) {
  // Vérifie que c est un operateur

  switch(c) {
    case '#':         // modalite []
    case '%':         // modalite <>
    case '-':         // negation
    case '&':         // et
    case '|':         // ou
    case '>':         // implique
    case '=':         // equivalent
      return 1;
      break;
  default : return 0;
  }
}

int IsProposition(char c) {
  // Vérifie que c est une lettre minuscule

  return ((c>='a')&&(c<='z'));
}

string infix2Postfix (string formuleInfixe) {
    string operandes;
    string operateurs;

    char c;

    for (int i = formuleInfixe.size() - 1; i >= 0; --i)
    {
        c = formuleInfixe[i];

        if (IsOperator(c))
        {
            while ((operateurs[operateurs.size() - 1] != ')') && (Precedence(operateurs[operateurs.size() - 1])>=Precedence(c)))
            {
                operandes.push_back(operateurs[operateurs.size()-1]);
                operateurs.pop_back();
            }
            operateurs.push_back(c);
        }
        else
        {
            if (IsProposition(c)) operandes.push_back(c);
            else // c'est une parenthèse
                if (c == ')') operateurs.push_back(c);
                else
                {
                    if (c == '(') {
                        while (operateurs[operateurs.size() - 1] != ')')
                        {
                            operandes.push_back(operateurs[operateurs.size()-1]);
                            operateurs.pop_back();
                        }
                        operateurs.pop_back();
                    }
                }
        }
    }
//    operandes.push_back('\');
    return operandes;
}

// -----------------------------------------------------------------------------
// Entree
// -----------------------------------------------------------------------------

//string Read () {
//    string formule;
//    getline(cin, formule);

//    formule.insert(0,"(");
//    formule.push_back(')');
//    formule.push_back('\n');

//    return formule;

//}

string changeCin (string formule) {

    formule.insert(0,"(");
    formule.push_back(')');
    formule.push_back('\n');

    formule = infix2Postfix(formule);
    return formule;

}


// fonction désormais inutile

//string transformToString (char* formule) {
//    // transforme une formule donnee en une chaîne de caractère

//    string stringFormule;

//    unsigned int i;

//    for(i=0;(formule[i] != '\n');++i) stringFormule.push_back(formule[i]);

//    cout << stringFormule << '\n';

//    return stringFormule;
//}
