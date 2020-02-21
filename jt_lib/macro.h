#ifndef _MACRO
#define _MACRO

#define MAX_CHRO 2

#define MAX_SEXE 2

#define ARBRE_MAX_NAME_LEN 10000

#include <stdio.h>

#define ERREUR
/*pour la pause quel que soit la version*/
#define PAUSE() \
(void)fprintf(stderr,"\nappuyer sur entree\n ");\
getchar()
#define PAUSE_MSG(message) \
printf("\n%s \nappuyer sur entree\n", message);\
getchar()

/*
#define TESTMEMOIRE
*/
#define CONSTERREUR -1222223335
#define CONSTERRERMIN -1222223335.0001
#define CONSTERRERMAX -1222223334.9999

#define EstErreur(x) ((((double)x)<CONSTERRERMAX && ((double)x)>CONSTERRERMIN)?TRUE:FALSE)
#ifndef BOOLEAN
#define BOOLEAN
/*definition d'un type boolean*/
typedef enum {FALSE=0,TRUE} boolean;
#endif

#define MAX(A,B) ((A>B)?(A):(B))
#define MIN(x, y) ((x)<(y)?(x):(y))
#define ABS(A) ((A>0)?(A):(-A))
#define CMP(A,B) (((A)==(B))?FALSE:TRUE)
#define ROUND(x) (int)((x)>0?(x)+0.5:(x)-0.5)
#define DOUBLEEGALEAZERO(x)((x<1e-7 && x>-1e-7)?TRUE:FALSE)
#define LONGEURBRANCHENULLE(x, y)((x<y && (x!=-1))?TRUE:FALSE)

/*
#define PVALUECOALESCENT
*/
#define IMFV2
/*
#define NBFEUILLE2N
*/
#endif
