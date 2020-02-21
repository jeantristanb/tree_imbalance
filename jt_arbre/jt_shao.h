#ifndef _CALCSHAO
#define _CALCSHAO
#include <math.h>
#include "jt_arbre.h"
#include "./MeanMeanNoeud.h" 
#include "../jt_lib/jt_aleatoire.h"
void CalculerShaoBinaire(FILE* sortie,Arbre* arbre,int nbRepPvalueIprime);
void CalculerShao(FILE* ecrire,Arbre* arbre,int nbRepPvalueIprime);
void CalculerShaoBinaireV2(FILE* ecrire,Arbre* arbre,int nbRepPvalueIprime);
double MinNoeudShao(int nbFeuille, int nbNoeud);
double MaxNoeudShao(int nbFeuille, int nbNoeud);
int NbNoeudFeuilleRoot(Noeud* Feuille);
#endif
