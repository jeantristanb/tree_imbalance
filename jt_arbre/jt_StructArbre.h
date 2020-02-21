#ifndef _STRUCTARBRE
#define _STRUCTARBRE

#include"../jt_lib/macro.h"

typedef struct FrequenceHaplotype{
        double** frequencehaplotype;
        double frequenceUn;
          double frequenceZero;
}FrequenceHaplotype;


typedef struct LongHaplo{
        double debut;
        double fin;
        boolean balise;
        
}LongHaplo;

typedef struct Snp{
      /*nombre de sequences*/
     int nb_sequences;
     /*polymorphisme pour le snp de chacun des feuilles*/ 
     short int* polymorphisme;
     /*position dans la sequence*/
     double position;
     /*pointeur vers le snp suivant*/ 
     struct Snp* suiv;
     /*pointeur vers le snp precedent*/
     struct Snp*prec;
}Snp;
#endif
