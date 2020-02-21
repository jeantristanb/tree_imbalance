#ifndef _IPRIME
#define _IPRIME
#include "./jt_arbre.h"
#include <math.h>
#include "../jt_lib/jt_aleatoire.h"
#include "../jt_coalescence/jt_coalescence.h"
#include "./MeanFeuilleMin.h"
void CalculerIprimeArbreBinaire(FILE* sortie, Arbre* arbre, double* IprimeF, int nbRepPvalue, double* ArbrePvaluePurvis,double* ArbrePvalueJT, boolean BaliseBinaire);
void CalculerIprimeListeArbreBinaire(FILE* sortie,Arbre* arbre, double* IprimeF, int nbRepPvalue, double* ArbrePvaluePurvis,double* ArbrePvalueJT, boolean BaliseBinaire );
double calculerIprimeNonBinaire(int nbFeuilles,int maxfeuille,int nbNoeud);
double calculerIinvprimeBinaire(int nbFeuilles,int minFeuille );
double calculerIprimeBinaire(int nbFeuilles,int maxfeuille );
double PvaluePurvisIprimeNoeud(double IprimeNoeud);
void CalculerIprimeArbreBinaireNew2(FILE* sortie, Arbre* arbre, double* IprimeFBin, double* IprimeFNonBin2N, double* IprimeFNonBinKp1, double* IprimeFNonBinPerm, double* IprimeFPurvis, double* IprimeFPurvisPerm,  int nbRepPvalue, double* ArbrePvaluePurvisBin, double* ArbrePvaluePurvisNonBin2N, double* ArbrePvaluePurvisKp1, double* ArbrePvaluePurvisPerm, double* ArbrePvaluePurvisPurvis, double* ArbrePvaluePurvisPurvisPerm ,double* ArbrePvalueJT   ,int* TabnbFeuille,int* TempnbFeuille, int MinFeuille, double HauteurMin);
void GetNbFeuilleBinaire(Noeud* noeud, int* nbMultifurcation, int* TabnbFeuille, int* countNumNoeud,int* sommeFeuille);
#endif
