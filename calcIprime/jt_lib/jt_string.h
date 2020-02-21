#ifndef _JTSTRING
#define _JTSTRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "macro.h"

#ifndef BOOLEAN
#define BOOLEAN
/*definition d'un type boolean*/
typedef enum {FALSE=0,TRUE} boolean;
#endif


typedef struct Tab_String{
        struct String** tab;
        int nb_string;
        void (*Set)(struct Tab_String* , struct String*  , int);        
        struct String* (*Get)(struct Tab_String* , int );
        void (*Afficher)(FILE* sortie, struct Tab_String*);
        void (*Ajouter)(struct Tab_String*,struct String* , int  );
        void (*Free)(struct Tab_String*);
        struct Tab_String* (*Dupliquer)(struct Tab_String*);
}Tab_String;

typedef struct String{
        char* chaine;
        
        int longeur;
        /*taille alloue*/
        size_t taille;
        /*methode */
        /*compare deux chaines*/
        boolean (*Comparer)(struct String *,struct String *);
        /*compare san prendre en compte les majuscules et miniscules*/
        boolean (*Comparer_Sans_Case)(struct String *,struct String *);
        /*concatene : concatene deux chaines*/
        void (*Concatener)(struct String*,struct String*);
        /*remplace un carectere par un autre*/
        void (*Remplacer)(struct String* , char, char);
        /*compte le nombre de caractere*/
        int (*Compter)(struct String* , char caractere);
        /*libere l'espace*/
        void (*Free) (struct String*);
        /*decoupe en fonction d'un caracter le chaine*/
        Tab_String* (*Split)(struct String* , char );
        /*affiche un caractere*/
        void (*Afficher)(FILE* sortie, struct String*);
        /*supprime un caractere*/
        void (*Supprimer)(struct String*, char);
        /*dupliqe la structure String*/
        struct String* (*Dupliquer)(struct String *);
        /*retourne si la dans la premiere chaine est presente la seconde*/
        boolean (*Est_Present)(struct String*,struct String*);
        void (*Set)(struct String*,char, int);
        void (*Reallouer)(struct String*, int);
        void (*Ajuster_Taille)(struct String*);
        /*compte le nombre de difference entre deux structures*/
        int (*Nombre_Diff)(struct String*, struct String*);
}String;



String* String_Create_int(int );
Tab_String* Tab_String_Create(int );
String* String_Create(char* );
#endif
