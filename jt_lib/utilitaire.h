#ifndef _UTILITAIRE
#define _UTILITAIRE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include <stdarg.h>
#include <dirent.h>
#include <unistd.h>

#ifdef TESTMEMOIRE


/*#define somme_tab dsum
*/

typedef struct S_Memoire {
  int string;
  int tab_string;
  int direction;
  int fichier;       
  int arbre;
  int noeud;
  int longhaplo;
  int tablonghaplo;
  int snp;
  int tabdint;
  int tabint;
  int tabchar;
  int tabdouble;
}S_Memoire;
S_Memoire* jt_mem;
#endif



void erreur_allocation(char* nomdefonction, ...);
void erreur(char* message,...);
double*** t_d_allocate(int nb);
double** d_d_allocate(int nb);
double* d_allocate(int nb);
char* c_allocate(int nb);
void free_tab_double(double* tab);
void free_tab_int(int* tab);
void free_d_tab_int(int** tab);
void tableau_rec_free(double** rec, int nb_ligne, int nb_col);
double** tableau_rec_allocate(int nb_ligne, int nb_col);
double**** q_d_allocate(int nb);
double***** c_d_allocate(int nb);
void free_tab_char(char* tab);
void free_d_tab_char(char** tab);
void free_d_tab_double(double** tab);
void free_t_tab_double(double*** tab);
int* i_reallocate(int* ancien, int nb);
int** d_i_reallocate(int** ancienne, int (nb));
char** d_c_allocate(int (nb));
int* i_allocate(int nb);
int** d_i_allocate(int nb);
char* c_reallocate(char*ancienne, int (nb));
char** d_c_reallocate(char**ancienne, int (nb));
short int* short_i_allocate(int nb);
short int** tableau_rect_short_int_allocate(int nb_ligne, int nb_col);
void tableau_rect_short_int_free(short int** rec, int nb_ligne, int nb_col);
void free_tab_short_int(short int* tab);

FILE* ouvrirfichier(char* fichier,char* mode);
char* concatener(char* mot1,char* mot2);
int nb_chiffre_int(int num);
char* convert_int_char(int arg);

char* ajouter_int(char* message,int num);

int** tableau_rect_int_allocate(int nb_ligne, int nb_col);
void tableau_rect_int_free(int** rec, int nb_ligne, int nb_col);


int recherche_dicho(double* tab, double num_recherche, int borne_inf, int borne_sup);
void init_testmemoire();
void afficher_testmemoire();
void classeIntMethodeMax(int* tab, int nbElement, int maxElement);
void AfficherMatriceDouble(FILE* sortie, double** Matrice, int nb_ligne, int nb_col);
double dmean(double *table, int min, int max);
double imean(int *table, int min, int max);

int CreerRepertoire(const char* namerep);

void CopierMatriceDouble(double** a , double ** b , int col, int ligne);
void CopierTabInt(int* tab1, int* tab2, int nbElement);

boolean BonBinaire(char* BinaireArgV,char*  BinaireVoulue);
#endif
