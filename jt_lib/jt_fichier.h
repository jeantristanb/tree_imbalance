#ifndef TRAITER_FICHIER
#define TRAITER_FICHIER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "jt_string.h"
/*Structure d'un fichier*/
typedef struct Fichier{
        /*emplacement du fichier*/
        String* emplacement;
        /*nombre de caractere total*/
        int nb_lignes;
        int ligne_en_cours;
        int type_ouverture;
        Tab_String* (*Lire_Ligne)(struct Fichier*);
        char* (*Get_Ligne)(struct Fichier*,int);
        char (*Get_Caractere)(struct Fichier*,int);
        void (*Ajouter_Ligne)(struct Fichier* , char* );
        void (*Free)(struct Fichier*);
        int (*Nb_Lignes)(struct Fichier*);
}Fichier;
Fichier* Fichier_Create(String* emplacement, char type);
#endif

