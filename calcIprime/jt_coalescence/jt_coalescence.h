#ifndef _JT_COALESCENCE
#define _JT_COALESCENCE

#include "../jt_arbre/jt_arbre.h"
#include <stdio.h>
#include <stdlib.h>
#include "../jt_lib/utilitaire.h"
#include "../jt_lib/jt_aleatoire.h"
int* GenererCoalecensceNnoeud(int nbFeuille, int nbNoeud);
int* GenererCoalecensceNnoeud2(int nbFeuille, int nbNoeud, int* listeNoeud);
Arbre* GenererArbreCoalescenceBinaire(int nbFeuille);
Arbre* GenererArbreCoalescenceBinaireDesequilibre(int nbFeuilleInitiale, double alphaDesequilibre, int);
double MeanNBFeuilleMoyenCoalescence(int nbFeuille, int nbNoeud, int nbRepetition);
double MeanNBNoeudMoyenCoalescence(int nbFeuille, int nbNoeud, int nbRepetition);
#endif
