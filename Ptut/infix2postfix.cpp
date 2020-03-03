// -----------------------------------------------------------------------------
// Transformation d'une formule logique infixe en forme postfixe
// 10/02/2020, V. Risch
//
// Le programme recupere une formule logique en forme infixe donnee sous la
// forme d'un tableau de caracteres f_infixe pour la transmettre a la fonction
// Infix2prefix qui la transforme en forme postfixe. Infix2Prefix gere deux
// piles : une pile des operateurs pile_operateurs et f_postfixe vue
// initialement comme pile des operandes a laquelle les operateurs sont ajoutes
// au fur et a mesure qu'ils sont depiles de pile_operateurs. Les operandes sont
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

#define F_SIZEMAX 51        // taille max d'une formule incluant '\n' comme
                            // caractere de fin de chaine

// -----------------------------------------------------------------------------
// Structures de donnees
// -----------------------------------------------------------------------------

typedef struct pile_symboles {
  unsigned int top;
  char symboles[F_SIZEMAX];
} PILE_SYMBOLES;            // pile de caracteres

PILE_SYMBOLES * f_postfixe;

char f_infixe[F_SIZEMAX];   // formule infixe sous forme d'un tableau de
                            // caracteres
unsigned int taille_infixe;

// -----------------------------------------------------------------------------
// Gestion de la pile
// -----------------------------------------------------------------------------

char NextChar (void) {
  // Renvoie le prochain caractere trouve sur l'entree standart
  // a l'exception des blancs

  char c;

  while ((c=getchar()) == ' ') {}
  return c;
}

void PushChar(char c, PILE_SYMBOLES * pile) {
  // Empile le caractere lu

  pile->symboles[pile->top++]=c;
}

char PopChar(PILE_SYMBOLES * pile) {
   // Depile le caractere lu */

  return pile->symboles[--pile->top];
}

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

PILE_SYMBOLES * Infix2Postfix (unsigned int taille_infixe, char * f_infixe) {
  // Transforme la formule infixe en expression postfixe, terminee par '\n'
  // La formule infixe initiale est lue de droite à gauche afin de preserver
  // l'associativité à gauche implicitement associée à l'absence de parentheses
  // La pile initiale des opérandes sert de pile de renvoi de la formule
  // sous forme postfixe et, comme variable locale, est donc declaree static

  static
  PILE_SYMBOLES tableau_operandes={0};               // sert a la fois de pile des operandes et
  PILE_SYMBOLES * pile_operandes=&tableau_operandes; // de pile de renvoi de la formule postfixe

  PILE_SYMBOLES tableau_operateurs={0};
  PILE_SYMBOLES * pile_operateurs=&tableau_operateurs;

  signed int i;
  char c;

  for (i=taille_infixe-1;(i>=0);--i) {
    c=f_infixe[i];
    if (IsOperator(c)) {
      while ((pile_operateurs->symboles[pile_operateurs->top-1] != ')') && (Precedence(pile_operateurs->symboles[pile_operateurs->top-1])>=Precedence(c)))
        PushChar(PopChar(pile_operateurs), pile_operandes);
      PushChar(c, pile_operateurs);
    }
    else
      if (IsProposition(c)) PushChar(c, pile_operandes);
      else // c est une parenthese
        if (c==')') PushChar(c, pile_operateurs);
    else
          if (c=='(') {
            while (pile_operateurs->symboles[pile_operateurs->top-1] != ')')
              PushChar(PopChar(pile_operateurs), pile_operandes);
        pile_operateurs->top--;
      }
  }
  PushChar('\n', pile_operandes);

  return pile_operandes;
}

// -----------------------------------------------------------------------------
// Entree-sortie
// -----------------------------------------------------------------------------

unsigned int Lire (char* formule) {
  // Lit une formule sous forme d'un tableau de caracteres, encadre par defaut
  // d'une parenthese gauche et d'une parenthese droite et se finissant par '\n'
  // Le parenthesage explicite de la formule assure la coherence des tests
  // ulterieurs et est conforme à la definition syntaxique de la notion de
  // formule

  unsigned int longueur=0;

  formule[F_SIZEMAX] = '\n';   // sentinelle
  formule[longueur]='(';
  while ((formule[++longueur]=NextChar()) != '\n') {}
  formule[longueur] = ')';
  formule[++longueur] = '\n';

  return longueur;
}

void Afficher (char* formule) {
  // Affiche une formule donnee sous forme d'un tableau de caracteres

  unsigned int i;

  for(i=0;(formule[i] != '\n');++i) printf("%c",formule[i]);
  printf("\n");
}


// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------

//int main (void) {
//  taille_infixe = Lire(f_infixe);

//  printf("taille_infixe = %d\n", taille_infixe);
//  Afficher(f_infixe);

//  f_postfixe=Infix2Postfix(taille_infixe, f_infixe);

//  Afficher(f_postfixe->symboles);

//  return 0;
//}
