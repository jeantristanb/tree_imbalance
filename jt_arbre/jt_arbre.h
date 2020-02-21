#ifndef _JTARBRE
#define _JTARBRE
/*
#define MULTINOEUD
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../jt_lib/jt_string.h"
#include "../jt_lib/utilitaire.h"


typedef struct Noeud{
        String* nom;
        struct Noeud* suiv, *fils_1, *fils_2, *pere, *prec ;
        double longeur_fils_1, longeur_fils_2;
        int numero, nbFeuille, nbNoeud;
        double hauteur;
        double hauteurTotal;
        int nbEmbranchement;
        /*permet de dire si le noeud est null ou pas*/
        boolean EstNull;
        /*Nombre de vrai noeud en comprenant ce noeud*/
        int nbNoeudVrai;
        #ifdef MULTINOEUD
        struct Noeud* ListeFils;
        struct Noeud* FrereSuiv;        
        #endif
        boolean Balise;
        
}Noeud;
typedef struct Noeud Feuille;
typedef struct Arbre{
                double tx_mutation;
                int nbSnp;
                double partition;
                struct Noeud* sommet;  
                struct Noeud* feuilles;
                struct Noeud* noeuds;
                int nb_noeuds;
                int nb_feuilles;
                double longeur;
                double partition_normalise;
                double *longeur_branche_cumule;
                struct Arbre* suiv;
                double longeurExterne;
                double longeurInterne;
                int* ListeEmbranchement;
                double Iprime;
                double Imn;
                int nbVraiNoeuds;
                int nbVraiBranches;
                double TMRCA;
}Arbre;

Arbre* Lire_arbre_String(String* str_arbre);
void init_longeur_de_branches_cumulee(Arbre* arbre);
Noeud* recuperer_noeud(int position,Arbre* arbre);
void freelisteNoeud(Noeud* noeud);
void freeNoeud(Noeud* noeud);
void freeArbre(Arbre* arbre);
void freelisteArbre(Arbre* arbre);
boolean isFeuille(Noeud* noeud) ;
void NormaliserLongeurListeArbre(Arbre* arbre, int longeur_total);
Noeud* NewNoeud();
void ecrireArbre(FILE* ecrire, Arbre* arbre);
void AjouterNoeud(Arbre* arbre, Noeud* noeud);
void ecrireArbreSansOutPut(FILE* ecrire, Arbre* arbre, String* NomOutPut);
int* recuperernbEmbranchementNoeud(Arbre* arbre);
Arbre* NewArbre();
void AjouterFeuille(Arbre* arbre, Noeud* feuille);
void AjouterNoeudPere(Noeud* pere, Noeud* fils, int position);
void ecrireNoeudArbre(FILE* ecrire, Noeud* noeud);
void AjouterHauteurTotalNoeudArbre(Arbre* arbre);
double CalcTMRCAArbre(Arbre* arbre);
void AjouterNbFeuille(Arbre* arbre);
int GetNbVraiSommet(Noeud* noeud);
Arbre* CopierArbre(Arbre* arbre);
double* GetTabBranche(Arbre* arbre);
int GetnbHaplotype(Arbre* arbre);
#endif
