#include "jt_Iprime.h"
double PvaluePurvisIprimeNoeud(double IprimeNoeud);
double calculerIprimeBinaire(int nbFeuilles,int maxfeuille ){
       int nbfeuillemoyen = (int)(ceil((float)nbFeuilles/2.0));
       int maxfeuilletheo = (int)(nbFeuilles-1);
       double IprimeNoeud;
       if(nbFeuilles<=3)return -1.0;
       IprimeNoeud= ((double)(maxfeuille - nbfeuillemoyen)/(double)(maxfeuilletheo - nbfeuillemoyen));
       if(nbFeuilles%2==0)IprimeNoeud = ((double)(nbFeuilles-1))/(double)nbFeuilles*IprimeNoeud;
       return IprimeNoeud;
}

double calculerIinvprimeBinaire(int nbFeuilles,int minFeuille ){
       int nbfeuillemoyen = (int)(ceil((float)nbFeuilles/2.0));
       int minfeuilletheo = (int)(1);
       double IprimeNoeud;
       if(nbFeuilles<=3)return -1.0;
       IprimeNoeud= ((double)(nbfeuillemoyen - minFeuille)/(double)(nbfeuillemoyen - minfeuilletheo));
       if(nbFeuilles%2==0)IprimeNoeud = ((double)(nbFeuilles-1))/(double)nbFeuilles*IprimeNoeud;
       return IprimeNoeud;
}

double calculerIprimeNonBinaire(int nbFeuilles,int maxfeuille,int nbNoeud){
       /*int nbfeuillemoyen = (int)(ceil((float)nbFeuilles/(double)nbNoeud));  */
       double nbfeuillemoyen;   
       int maxfeuilletheo = nbFeuilles-nbNoeud+1;
       double IprimeNoeud;
       #ifdef ERREUR
       if(maxfeuille>maxfeuilletheo)erreur("calculerIprimeNonBinaire : maxfeuille>maxfeuilletheo %d %d ",nbFeuilles, maxfeuille );
       #endif
       #ifdef NBFEUILLE2N
       if(nbFeuilles<= 2*nbNoeud-1 || nbNoeud<=1){ 
       #else  
       if(nbFeuilles<=nbNoeud+1|| nbNoeud<=1){     
       #endif
         return CONSTERREUR;
       }
       nbfeuillemoyen=(GetMeanMeanFeuille(nbFeuilles,nbNoeud ));
       
       if(nbfeuillemoyen==CONSTERREUR){
                                       return (double)CONSTERREUR;
       }
       /*
       if(nbfeuillemoyen>maxfeuille)return -1;
       */
       IprimeNoeud= ((double)(maxfeuille - nbfeuillemoyen)/(double)(maxfeuilletheo - nbfeuillemoyen));
/*       fprintf(stderr,"%.3f %d %d %d %f\n", nbfeuillemoyen,nbFeuilles,nbNoeud,maxfeuille,IprimeNoeud  );
  */ /*    if(IprimeNoeud<0)erreur("calculerIprime : IprimeNoeud < 0 : Rapport : \nNombre de feuille : %d Nombre de noeud %d Max Observe %d Max theorique %d : ",nbFeuilles ,nbNoeud,maxfeuille,maxfeuilletheo );
*/
      /* if(nbFeuilles%2==0)IprimeNoeud = ((double)(nbFeuilles-1)/(double)nbFeuilles)*IprimeNoeud; 
       */
       return IprimeNoeud;
}

double calculerIprimeNonBinaireKp1(int nbFeuilles,int maxfeuille,int nbNoeud){
       /*int nbfeuillemoyen = (int)(ceil((float)nbFeuilles/(double)nbNoeud));  */
       double nbfeuillemoyen;   
       int maxfeuilletheo = nbFeuilles-nbNoeud+1;
       double IprimeNoeud;
       #ifdef ERREUR
       if(maxfeuille>maxfeuilletheo)erreur("calculerIprimeNonBinaire : maxfeuille>maxfeuilletheo %d %d ",nbFeuilles, maxfeuille );
       #endif
       if(nbFeuilles<=nbNoeud+1|| nbNoeud<=1){ 
         return CONSTERREUR;
       }
       nbfeuillemoyen=(GetMeanMeanFeuille(nbFeuilles,nbNoeud ));
       
       if(nbfeuillemoyen==CONSTERREUR){
                                       return (double)CONSTERREUR;
       }
       IprimeNoeud= ((double)(maxfeuille - nbfeuillemoyen)/(double)(maxfeuilletheo - nbfeuillemoyen));
       return IprimeNoeud;
}
double calculerIprimeNonBinaire2N(int nbFeuilles,int maxfeuille,int nbNoeud){
       /*int nbfeuillemoyen = (int)(ceil((float)nbFeuilles/(double)nbNoeud));  */
       double nbfeuillemoyen;   
       int maxfeuilletheo = nbFeuilles-nbNoeud+1;
       double IprimeNoeud;
       #ifdef ERREUR
       if(maxfeuille>maxfeuilletheo)erreur("calculerIprimeNonBinaire : maxfeuille>maxfeuilletheo %d %d ",nbFeuilles, maxfeuille );
       #endif
       if(nbFeuilles<= 2*nbNoeud-1 || nbNoeud<=1){ 
         return CONSTERREUR;
       }
       nbfeuillemoyen=(GetMeanMeanFeuille(nbFeuilles,nbNoeud ));
       
       if(nbfeuillemoyen==CONSTERREUR){
                                       return (double)CONSTERREUR;
       }
       IprimeNoeud= ((double)(maxfeuille - nbfeuillemoyen)/(double)(maxfeuilletheo - nbfeuillemoyen));
       return IprimeNoeud;
}

void TestIprimeEquilibre(){
     int cmt,nbFeuille;
     for(cmt=4; cmt<200; cmt++){
          nbFeuille =(int)((double)(cmt+1.0)/2.0); 
          printf("%d %f %f\n",cmt, calculerIprimeNonBinaire(cmt,nbFeuille,2) , calculerIprimeNonBinaire(cmt,cmt-1,2));     
     }    
     
}

/***********************************Méthode 2 utilisant les multifurcations***************************************************/
/*Retourne le nombre de feuille par noeud*/
void GetNbFeuilleBinaire(Noeud* noeud, int* nbMultifurcation, int* TabnbFeuille, int* countNumNoeud,int* sommeFeuille){

        /*Cas d'une feuille*/
        if(noeud->fils_1==NULL){
                                (*nbMultifurcation)+=1; 
                                TabnbFeuille[*countNumNoeud] = 1;
                                (*countNumNoeud)++; 
                                (*sommeFeuille)++;
        }
        /*si la hauteur du fil est different de zero on ajoute le nombre de feuille */
        else if(!noeud->EstNull || noeud->hauteur==-1){
                (*nbMultifurcation)+=1;    
                /*On recupere le nombre de feuille*/
                TabnbFeuille[*countNumNoeud] = noeud->nbFeuille;
                (*sommeFeuille)+=noeud->nbFeuille;
                (*countNumNoeud)++;
        }
        /**/
        else{
            GetNbFeuilleBinaire(noeud->fils_1, nbMultifurcation, TabnbFeuille, countNumNoeud,sommeFeuille);
            GetNbFeuilleBinaire(noeud->fils_2, nbMultifurcation, TabnbFeuille, countNumNoeud,sommeFeuille);           
        }
}
/*Melange les feuilles et retourne le maximum de feuille*/
int GetSimulationMaxFeuilleAleatoire( int* TabnbFeuille,int countNumNoeud){
      int  Noeud1, Noeud2,temp;
      /*Tant qu'on a pas deux noeud*/
      while(countNumNoeud>2){
            Noeud2 = (int)(aleatoire()*countNumNoeud);
            temp = TabnbFeuille[Noeud2];
            if(TabnbFeuille[Noeud2]==-1)erreur("TabnbFeuille[Noeud2]==-1");
            TabnbFeuille[Noeud2] = TabnbFeuille[countNumNoeud-1];
            
            TabnbFeuille[countNumNoeud-1] = -1;
            countNumNoeud--;
            Noeud1 = (int)(aleatoire()*countNumNoeud);
            TabnbFeuille[Noeud1]+=temp;
            /*On intervertit le dernier avec le noeud2*/         
      } 
      return(MAX(TabnbFeuille[0], TabnbFeuille[1]));
       
}
/*Calcul le Imf en permutant les feuilles lorsqu'il y a des polytonies*/
double GetSimulationsMaxFeuilleAleatoirePurvis( int* TabnbFeuille,int countNumNoeud, int nbSimulation, int* TempTable, int sommeFeuille ){
       int cmtPolytomie, cmtSimulation, nbSimulation2=0, MaxFeuille;
       double Imf=0, sommeImf=0;
       for(cmtSimulation=0; cmtSimulation<nbSimulation; cmtSimulation++){
           for(cmtPolytomie=0; cmtPolytomie<countNumNoeud; cmtPolytomie++){
                               TempTable[cmtPolytomie]=TabnbFeuille[cmtPolytomie];
           }
           MaxFeuille = GetSimulationMaxFeuilleAleatoire( TempTable,countNumNoeud);
           Imf=calculerIprimeBinaire(sommeFeuille,MaxFeuille);            
           if(Imf!=-1){
                      sommeImf+=Imf;
                      nbSimulation2++;
           }
       }
       if(nbSimulation2==0)return CONSTERREUR;
       sommeImf/=(double)nbSimulation2;
       return(sommeImf);
       
}
/*Calcul le I purvis lors d'une multifurcation en melangeant les noeuds */
double CalcImfMethode2Purvis(Noeud* noeud, int* TabnbFeuille, int* TempTable){
       int nbMultifurcation=0, countNumNoeud=0, nbSimulation=1000, sommeFeuille=0;
       double Imf;
       /*On recupere le nombre de multifurcation et le nombre de feykke*/
       GetNbFeuilleBinaire(noeud->fils_1, &nbMultifurcation, TabnbFeuille, &countNumNoeud, &sommeFeuille);
       GetNbFeuilleBinaire(noeud->fils_2, &nbMultifurcation, TabnbFeuille, &countNumNoeud, &sommeFeuille);
       
       Imf = GetSimulationsMaxFeuilleAleatoirePurvis(TabnbFeuille,countNumNoeud,  nbSimulation, TempTable, sommeFeuille);
       return Imf;
       
}
/*Calcul le Imf en permutant les feuilles lorsqu'il y a des polytonies*/
double GetSimulationsMaxFeuilleAleatoire( int* TabnbFeuille,int countNumNoeud, int nbSimulation, int* TempTable, int sommeFeuille ){
       int cmtPolytomie, cmtSimulation, nbSimulation2=0, MaxFeuille;
       double Imf=0, sommeImf=0;
       for(cmtSimulation=0; cmtSimulation<nbSimulation; cmtSimulation++){
           for(cmtPolytomie=0; cmtPolytomie<countNumNoeud; cmtPolytomie++){
                               TempTable[cmtPolytomie]=TabnbFeuille[cmtPolytomie];
           }
           MaxFeuille = GetSimulationMaxFeuilleAleatoire( TempTable,countNumNoeud);
           Imf=calculerIprimeNonBinaire(sommeFeuille,MaxFeuille,2);            
           if(!EstErreur(Imf)){
                      sommeImf+=Imf;
                      nbSimulation2++;
           }
       }
       if(nbSimulation2==0)return CONSTERREUR;
       sommeImf/=(double)nbSimulation2;
       return(sommeImf);
       
}
/*Calcul le Imf lors d'une multifurcation en melangeant les noeuds */
double CalcImfMethode2(Noeud* noeud, int* TabnbFeuille, int* TempTable){
       int nbMultifurcation=0, countNumNoeud=0, nbSimulation=1000, sommeFeuille=0;
       double Imf;
       /*On recupere le nombre de multifurcation et le nombre de feykke*/
       GetNbFeuilleBinaire(noeud->fils_1, &nbMultifurcation, TabnbFeuille, &countNumNoeud, &sommeFeuille);
       GetNbFeuilleBinaire(noeud->fils_2, &nbMultifurcation, TabnbFeuille, &countNumNoeud, &sommeFeuille);
       
       Imf = GetSimulationsMaxFeuilleAleatoire(TabnbFeuille,countNumNoeud,  nbSimulation, TempTable, sommeFeuille);
       return Imf;
       
}


/***********************************Méthode 1 utilisant les multifurcations***************************************************/



int GetMaxFeuilleBinaire(Noeud* noeud, int* nbMultifurcation, int* nbFeuilleAccrocheeANoeud){
int noeud1, noeud2;
        if(noeud->fils_1==NULL){
                                if(noeud->hauteur==0)(*nbFeuilleAccrocheeANoeud)++;
                                (*nbMultifurcation)+=1;  
                                return 1;
        }
        /*si la hauteur du fil est different de zero on retourne le nombre de feuille */
        else if(!noeud->EstNull || noeud->hauteur==-1){
                (*nbMultifurcation)+=1;    
                return noeud->nbFeuille;
        }
        else{
            noeud1 = GetMaxFeuilleBinaire(noeud->fils_1, nbMultifurcation, nbFeuilleAccrocheeANoeud);
            noeud2 = GetMaxFeuilleBinaire(noeud->fils_2, nbMultifurcation, nbFeuilleAccrocheeANoeud);
            return MAX(noeud1,noeud2);           
        }
}
/*Permet de calculer une pvalue en utilisant des coalescent Binaire*/
void PvalueJTIprimeNoeudNonBinaire(int nbFeuilles, int nbMultifurcation, int nbRepPvalue, double* tabPvalue){
        int listeNoeud[nbFeuilles];
        int cmtPvalue, MaxFeuilleObs, cmtMultifurcation;
        for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){ 
                        GenererCoalecensceNnoeud2(nbFeuilles, nbMultifurcation, listeNoeud);
                        MaxFeuilleObs = listeNoeud[0];
                        for(cmtMultifurcation=1; cmtMultifurcation<nbMultifurcation;cmtMultifurcation++ )MaxFeuilleObs = MAX(MaxFeuilleObs, listeNoeud[cmtMultifurcation]);
                        tabPvalue[cmtPvalue]+=calculerIprimeNonBinaire(nbFeuilles,MaxFeuilleObs,nbMultifurcation );                
        }       
}
/***********************************************Lancer les methodes******************************************************************/
void calculerIprimeArbreBinaireNoeudNonBinaire(Noeud* noeud, double* Iprime, int* nbNoeud, int nbRepPvalue, double* ArbrePvaluePurvis, boolean BaliseBinaire, int* nbNoeudDeseq  
/*Methode 2 : range aleatoiremenent les noeud en fonctions des multifurcation*/
#ifdef IMFMETHODE2
, int* TabnbFeuille, int* TempnbFeuille
#endif
){
     int cmtPvalue, MaxFeuilleObs, nbFeuilles, nbMultifurcation = 0, nbNoeud1, nbNoeud2;
     double IprimeNoeud;
     nbFeuilles = noeud->nbFeuille;
     boolean FeuilleAccrocheeANoeud;
     int nbFeuilleAccrocheeANoeud =0;
     /*Si le noeud est de hauteur null on ne clacule pas le Iprime*/
     if(noeud->EstNull)return;
     FeuilleAccrocheeANoeud =FALSE;
     /*On recherche le Maximal du noeud*/
     nbNoeud1 = GetMaxFeuilleBinaire(noeud->fils_1, &nbMultifurcation,&nbFeuilleAccrocheeANoeud);
     nbNoeud2 = GetMaxFeuilleBinaire(noeud->fils_2, &nbMultifurcation,&nbFeuilleAccrocheeANoeud);
     if(nbFeuilleAccrocheeANoeud>1)FeuilleAccrocheeANoeud=TRUE; else FeuilleAccrocheeANoeud=FALSE;
    /*Si l'option Seulement binaire est calcule et qu'on a plus de 2 multifurcation on retourne rien*/
     if(nbMultifurcation>2 && BaliseBinaire)return;
     
     #ifdef IMFMETHODE2
     if(nbMultifurcation>2){
          IprimeNoeud = CalcImfMethode2(noeud,TabnbFeuille,TempnbFeuille);                
     }
     else{
     /*Methode 1*/
     #endif
     MaxFeuilleObs = MAX(nbNoeud1,nbNoeud2) ;
     #ifdef ERREUR
     if((nbNoeud1+nbNoeud2)>noeud->nbFeuille || nbNoeud1==0 || nbNoeud2==0)erreur("(nbNoeud1+nbNoeud2)>noeud->nbFeuille || nbNoeud1==0 || nbNoeud2==0");
     if(nbMultifurcation==2 && (nbNoeud1!=noeud->fils_1->nbFeuille || nbNoeud2!=noeud->fils_2->nbFeuille))erreur("nbMultifurcation==2 && (nbNoeud1!=noeud->fils_1->nbFeuille || nbNoeud2!=noeud->fils_2->nbFeuille)");
     #endif
     IprimeNoeud = calculerIprimeNonBinaire(nbFeuilles,MaxFeuilleObs,nbMultifurcation );/*
     printf("%f %d %d %d %d %d\n",   IprimeNoeud,nbNoeud1,nbNoeud2,nbFeuilles,MaxFeuilleObs,nbMultifurcation    );  */
     #ifdef IMFMETHODE2    
     }
     #endif
     if(EstErreur(IprimeNoeud))return;
     if(IprimeNoeud<-99)return;
    
     if(IprimeNoeud>0.5)(*nbNoeudDeseq)++;
     (*Iprime)+=IprimeNoeud;
     (*nbNoeud)++;
     #ifdef PVALUECOALESCENT
     PvalueJTIprimeNoeudNonBinaire(nbFeuilles, nbMultifurcation, nbRepPvalue, ArbrePvaluePurvis);
     #else
     for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      ArbrePvaluePurvis[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);

     }
     #endif
}
/*Permet de calculer sur un noeud 3 formes de I :
         IprimeBin : que sur les noeuds binaire
         IprimeNonBin2N : Iprime sur les multifurcation avec au min 2N -1 feuilles
         IprimeNonBinKp1: Iprime sur les multifurcation avec au min K+1 feuilles
         IprimePurvis :  
         */

void calculerIprimeArbreBinaireNoeud2(Noeud* noeud, double* IprimeBin, int* nbNoeudBin, 
                                                    double* IprimeNonBin2N, int* nbNoeudNonBin2N, 
                                                    double* IprimeNonBinKp1, int* nbNoeudNonBinKp1, 
                                                    double* IprimeNonBinPerm, int* nbNoeudNonBinPerm,
                                                    double* IprimePurvis, int* nbNoeudPurvis, 
                                                    double* IprimePurvisPerm, int* nbNoeudPurvisPerm  , int nbRepPvalue, double* ArbrePvaluePurvisBin, double* ArbrePvaluePurvisNonBin2N, double* ArbrePvaluePurvisNonBinKp1, double* ArbrePvaluePurvisPerm, double* ArbrePvaluePurvisPurvis ,double* ArbrePvaluePurvisPurvisPerm,int* TabnbFeuille, int* TempnbFeuille, int MinFeuille){
     int cmtPvalue, MaxFeuilleObs, nbFeuilles, nbMultifurcation = 0, nbNoeud1, nbNoeud2, nbFeuilleAccrocheeANoeud;
     double IprimeNoeud;
     boolean FeuilleAccrocheeANoeud;

     nbFeuilles = noeud->nbFeuille;
     nbFeuilleAccrocheeANoeud = 0;
     /*Si le noeud est de hauteur null on ne clacule pas le Iprime*/
     if(noeud->EstNull || nbFeuilles<MinFeuille)return;
    #ifdef  SORTIENOEUD
     FILE* sortie = fopen("SortieNoeud2N.out", "a");
     FILE* sortieK = fopen("SortieNoeudK.out", "a");
     FILE* sortieP = fopen("SortieNoeudP.out", "a");
     #endif
     FeuilleAccrocheeANoeud =FALSE;
     
     /*On recherche le Maximal du noeud*/
     nbNoeud1 = GetMaxFeuilleBinaire(noeud->fils_1, &nbMultifurcation,&nbFeuilleAccrocheeANoeud);
     nbNoeud2 = GetMaxFeuilleBinaire(noeud->fils_2, &nbMultifurcation,&nbFeuilleAccrocheeANoeud);
     if(nbFeuilleAccrocheeANoeud>1)FeuilleAccrocheeANoeud=TRUE; else FeuilleAccrocheeANoeud =FALSE;
    /*Si l'option Seulement binaire est calcule et qu'on a plus de 2 multifurcation on retourne rien*/
     
     MaxFeuilleObs = MAX(nbNoeud1,nbNoeud2);
     #ifdef ERREUR
     if((nbNoeud1+nbNoeud2)>noeud->nbFeuille || nbNoeud1==0 || nbNoeud2==0)erreur("(nbNoeud1+nbNoeud2)>noeud->nbFeuille || nbNoeud1==0 || nbNoeud2==0");
     if(nbMultifurcation==2 && (nbNoeud1!=noeud->fils_1->nbFeuille || nbNoeud2!=noeud->fils_2->nbFeuille))erreur("nbMultifurcation==2 && (nbNoeud1!=noeud->fils_1->nbFeuille || nbNoeud2!=noeud->fils_2->nbFeuille)");
     #endif
     /*Ca ou c'est une bifurcation*/
      if(nbMultifurcation==2){
           IprimeNoeud = calculerIprimeNonBinaire(nbFeuilles,MaxFeuilleObs,nbMultifurcation );    

           if(!(EstErreur(IprimeNoeud) || IprimeNoeud<-99)){
           #ifdef  SORTIENOEUD
           fprintf(sortie, "%f %d %d %d %f\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation,noeud->hauteurTotal  );
           fprintf(sortieK, "%f %d %d %d %f\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation,noeud->hauteurTotal  );
           #endif
                  (*IprimeBin)+=IprimeNoeud;
                  (*nbNoeudBin)++;
                  (*IprimeNonBin2N)+=IprimeNoeud;
                  (*nbNoeudNonBin2N)++;
                  (*IprimeNonBinKp1)+=IprimeNoeud;
                  (*nbNoeudNonBinKp1)++;
                        /*Dans le cas des permutations*/
                  (*IprimeNonBinPerm)+=IprimeNoeud;
                  (*nbNoeudNonBinPerm)++;
                  for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                            ArbrePvaluePurvisBin[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                            ArbrePvaluePurvisNonBin2N[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                            ArbrePvaluePurvisNonBinKp1[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                                  /*Dans le cas des permutations*/
                            ArbrePvaluePurvisPerm[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                  }           
           }                                            
                             /*Pour l'iprime Initiale*/
           if(nbFeuilles>3){
                  IprimeNoeud=calculerIprimeBinaire(nbFeuilles,MaxFeuilleObs );
                  #ifdef  SORTIENOEUD
                  fprintf(sortieP, "%f %d %d %d %f\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation,noeud->hauteurTotal  );
                  #endif
                  if(IprimeNoeud==-1)erreur("IprimeNoeud==-1");
                  (*IprimePurvis)+=IprimeNoeud;
                  (*nbNoeudPurvis)++;
                  /*Dans le cas des permutations*/
                  (*IprimePurvisPerm)+=IprimeNoeud;
                  (*nbNoeudPurvisPerm)++;
                  for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                            ArbrePvaluePurvisPurvis[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                            /*Dans le cas des permutations*/
                            ArbrePvaluePurvisPurvisPerm[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                  }
                  
                  
           }

     }else{
           IprimeNoeud = calculerIprimeNonBinaire2N(nbFeuilles,MaxFeuilleObs,nbMultifurcation );  

           if(FeuilleAccrocheeANoeud==FALSE && !(EstErreur(IprimeNoeud) || IprimeNoeud<-99)){
                             #ifdef  SORTIENOEUD
                             fprintf(sortie, "%f %d %d %d %f\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation,noeud->hauteurTotal  );
                             #endif
                         (*IprimeNonBin2N)+=IprimeNoeud;
                         (*nbNoeudNonBin2N)++;
                          for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                                   ArbrePvaluePurvisNonBin2N[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                          }
           }
           IprimeNoeud = calculerIprimeNonBinaireKp1(nbFeuilles,MaxFeuilleObs,nbMultifurcation );  
           if(FeuilleAccrocheeANoeud==FALSE && !(EstErreur(IprimeNoeud) || IprimeNoeud<-99)){
                          #ifdef SORTIENOEUD
                      /*    fprintf(stderr, "%f %d %d %d\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation  );
                        */  fprintf(sortieK, "%f %d %d %d %f\n",IprimeNoeud,nbFeuilles, MaxFeuilleObs,nbMultifurcation,noeud->hauteurTotal  );
                           #endif

                          (*IprimeNonBinKp1)+=IprimeNoeud;
                          (*nbNoeudNonBinKp1)++;
                          for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                                          ArbrePvaluePurvisNonBinKp1[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                          }
           }
           /*Avec permutation pour Imf*/
           IprimeNoeud = CalcImfMethode2(noeud,TabnbFeuille,TempnbFeuille );  
           if(!(EstErreur(IprimeNoeud) || IprimeNoeud<-99)){
                    (*IprimeNonBinPerm)+=IprimeNoeud;  
                    (*nbNoeudNonBinPerm)++; 
                    for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){  
                         ArbrePvaluePurvisPerm[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                    }            
           }
           /*Avec Permutation pour Iprime*/
           IprimeNoeud = CalcImfMethode2Purvis(noeud,TabnbFeuille,TempnbFeuille );  
           if(!(EstErreur(IprimeNoeud) || IprimeNoeud<-99)){
                    (*IprimePurvisPerm)+=IprimeNoeud;  
                    (*nbNoeudPurvisPerm)++; 
                    for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){  
                         ArbrePvaluePurvisPurvisPerm[cmtPvalue]+= PvaluePurvisIprimeNoeud(IprimeNoeud);
                    }            
           }
     
     } 
     #ifdef  SORTIENOEUD
     fclose(sortie);
     fclose(sortieK);
     fclose(sortieP);
     #endif
}


/*calcul une valeur de Iprime en fonction du nombre de feuille au noeud*/
/*double PvalueJTIprimeNoeud(int nbFeuilles){
       int maxfeuille;
       if(nbFeuilles<=3)erreur("PvalueJTIprime nbFeuilles<=3");
       maxfeuille = 1 + (int)(aleatoire()*(nbFeuilles-1));
       maxfeuille = MAX(maxfeuille,(nbFeuilles-maxfeuille));
       if(maxfeuille>=nbFeuilles || maxfeuille<=0 )erreur("maxfeuille==nbFeuilles ou maxfeuille<=0");
       return calculerIprimeBinaire(nbFeuilles,maxfeuille);
}*/
/*Permet de calculer une pvalue en simulant n coalescents Binaire*/
void PvalueJTIprimeNoeudBinaire(int nbFeuilles, int nbRepPvalue, double* tabPvalue){
        int listeNoeud[nbFeuilles];
        int cmtPvalue, MaxNoeud;
        for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){ 
                        GenererCoalecensceNnoeud2(nbFeuilles, 2, listeNoeud);
                        MaxNoeud = MAX(listeNoeud[0], listeNoeud[1]);
                        tabPvalue[cmtPvalue]+=calculerIprimeBinaire(nbFeuilles,MaxNoeud);                
        }       
}


double PvaluePurvisIprimeNoeud(double IprimeNoeud){
       if(aleatoire()<0.5)return (1.0-IprimeNoeud);
       else return IprimeNoeud;
}
void calculerIprimeBinaireNoeud(Noeud* noeud, double* Iprime, int* nbNoeud, int nbRepPvalue, double* ArbrePvaluePurvis,double* ArbrePvalueJT ){
     double maxFeuille, nbFeuilleMoyen, maxFeuilleTheo, INoeud;
     int cmtPvalue;
     if(noeud->nbFeuille<=3)return;
     if(noeud->fils_1->EstNull ||noeud->fils_1->EstNull )return;
     maxFeuille = (double)(MAX(noeud->fils_1->nbFeuille,noeud->fils_2->nbFeuille));
     nbFeuilleMoyen = (double)ceil(((double)noeud->nbFeuille)/2.0);
     maxFeuilleTheo = (double)(noeud->nbFeuille-1);
     if((maxFeuilleTheo-nbFeuilleMoyen)==0)erreur("calculerIprimeBinaireNoeud : (maxFeuilleTheo-nbFeuilleMoyen)==0");
     INoeud = (maxFeuille-nbFeuilleMoyen)/(maxFeuilleTheo-nbFeuilleMoyen);
     if(INoeud>1 || INoeud<0)erreur("calculerIprimeBinaireNoeud INoeud>1 || INoeud<0 %f", INoeud);
     if(noeud->nbFeuille%2==0)(*Iprime)+=(double)(noeud->nbFeuille-1)/((double)noeud->nbFeuille)*INoeud;
     else (*Iprime)+=INoeud;
     (*nbNoeud)++;
     PvalueJTIprimeNoeudBinaire(noeud->nbFeuille,nbRepPvalue,ArbrePvalueJT);
     for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      ArbrePvaluePurvis[cmtPvalue]+= PvaluePurvisIprimeNoeud(INoeud);

     }
}
/*permet de calculer le Iprime d'un arbre binaire*/
void CalculerIprimeArbreBinaire(FILE* sortie, Arbre* arbre, double* IprimeF, int nbRepPvalue, double* ArbrePvaluePurvis,double* ArbrePvalueJT, boolean BaliseBinaire){
       Noeud* feuille = arbre->feuilles,*noeud, *parcourir;
       double Iprime=0;
       int nbNoeud=0, cmtPvalue;
       int nbNoeudDeseq = 0;
       #ifdef IMFMETHODE2
       int* TabnbFeuille = i_allocate(arbre->nb_noeuds*2);
       int* TempnbFeuille = i_allocate(arbre->nb_noeuds*2);
       #endif
       noeud = arbre->noeuds;
       IprimeF[0]=0,IprimeF[1]=0,IprimeF[2]=0,IprimeF[3]=0;
       for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      ArbrePvaluePurvis[cmtPvalue]=0;
                      ArbrePvalueJT[cmtPvalue]=0;       
       }
       /*On nettoye l'arbre*/
       while(noeud!=NULL){
                           noeud->nbFeuille = 0;
                           noeud = noeud->suiv;                  
        }
        /*On marque le nombre de feuille*/
       while(feuille!=NULL){
                    feuille->nbFeuille = 1;        
                    parcourir = feuille->pere;
                    while(parcourir!=NULL){
                        parcourir->nbFeuille++;                  
                        parcourir = parcourir->pere;                                         
                    }                            
                    feuille = feuille->suiv;        
       }
       /*Pour chacun des noeuds*/
       noeud = arbre->noeuds;
       while(noeud!=NULL && EstErreur(Iprime)==FALSE){
                
                 calculerIprimeArbreBinaireNoeudNonBinaire(noeud,&Iprime, &nbNoeud, nbRepPvalue,ArbrePvaluePurvis,BaliseBinaire, &nbNoeudDeseq        
       #ifdef IMFMETHODE2
       , TabnbFeuille,TempnbFeuille
       #endif
       );
                 noeud = noeud->suiv;
       }
       if(nbNoeud==0 || Iprime==CONSTERREUR){
                      IprimeF[0]=-1;
                      IprimeF[1]=0;
                      IprimeF[2]=-1;
                      IprimeF[3]=-1;
                      if(sortie!=NULL)fprintf(sortie, "\t%f\t%d\t%f\t%f\t%d", -1.0, -1, -1.0,-1.0,nbRepPvalue );

       }else{
           IprimeF[0] =    Iprime/(double) nbNoeud;
           IprimeF[1] =    (double) nbNoeud;
           IprimeF[4] = (double)nbNoeudDeseq/(double)nbNoeud;
           for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      if(ArbrePvaluePurvis[cmtPvalue]>Iprime)IprimeF[2]++;
           }
           IprimeF[2]/=(double)nbRepPvalue;
           if(sortie!=NULL)fprintf(sortie, "\t%f\t%d\t%f\t%f\t%d", IprimeF[0], (int)IprimeF[1],IprimeF[2],IprimeF[4],nbRepPvalue );

       }
        #ifdef IMFMETHODE2
       free(TabnbFeuille);
       free(TempnbFeuille);
        #endif
}
void AfficherUnIprime(FILE* sortie, int nbNoeud, double Iprime, double* IprimeF, int nbRepPvalue, double* ArbrePvaluePurvis){
      int cmtPvalue;
     
       if(nbNoeud==0 || Iprime==CONSTERREUR){
                      IprimeF[0]=-1;
                      IprimeF[1]=0;
                      IprimeF[2]=-1;
                      IprimeF[3]=-1;
                      if(sortie!=NULL)fprintf(sortie, "\t%f\t%d\t%f", -1.0, -1, -1.0);

       }else{
           IprimeF[0] =    Iprime/(double) nbNoeud;
           IprimeF[1] =    (double) nbNoeud;
           for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      if(ArbrePvaluePurvis[cmtPvalue]>Iprime)IprimeF[2]++;
           }
           IprimeF[2]/=(double)nbRepPvalue;
           if(sortie!=NULL)fprintf(sortie, "\t%f\t%d\t%f", IprimeF[0], (int)IprimeF[1],IprimeF[2] );

       }
}
/*permet de calculer le Iprime d'un arbre binaire*/
void CalculerIprimeArbreBinaireNew2(FILE* sortie, Arbre* arbre, double* IprimeFBin, double* IprimeFNonBin2N, double* IprimeFNonBinKp1, double* IprimeFNonBinPerm, double* IprimeFPurvis, double* IprimeFPurvisPerm,  int nbRepPvalue, double* ArbrePvaluePurvisBin, double* ArbrePvaluePurvisNonBin2N, double* ArbrePvaluePurvisKp1, double* ArbrePvaluePurvisPerm, double* ArbrePvaluePurvisPurvis, double* ArbrePvaluePurvisPurvisPerm ,double* ArbrePvalueJT   ,int* TabnbFeuille,int* TempnbFeuille, int MinFeuille, double LimiteHauteur){
       Noeud* feuille = arbre->feuilles,*noeud, *parcourir;
       double IprimeBin=0, IprimeNonBin2N=0, IprimeNonBinKp1=0.0, IprimeNonBinPerm=0.0, IprimePurvis=0.0, IprimePurvisPerm=0.0;
       int cmtPvalue;
       int nbNoeudBin=0, nbNoeudNonBin2N=0, nbNoeudNonBinKp1=0, nbNoeudNonBinPerm=0, nbNoeudPurvis=0, nbNoeudPurvisPerm=0;
       noeud = arbre->noeuds;
       IprimeFBin[0]=0,IprimeFBin[1]=0,IprimeFBin[2]=0,IprimeFBin[3]=0;
       IprimeFNonBin2N[0]=0,IprimeFNonBin2N[1]=0,IprimeFNonBin2N[2]=0,IprimeFNonBin2N[3]=0;
       IprimeFNonBinKp1[0]=0,IprimeFNonBinKp1[1]=0,IprimeFNonBinKp1[2]=0,IprimeFNonBinKp1[3]=0;
       IprimeFNonBinPerm[0]=0,IprimeFNonBinPerm[1]=0,IprimeFNonBinPerm[2]=0,IprimeFNonBinPerm[3]=0;
       IprimeFPurvis[0]=0,IprimeFPurvis[1]=0,IprimeFPurvis[2]=0,IprimeFPurvis[3]=0;
       IprimeFPurvisPerm[0]=0,IprimeFPurvisPerm[1]=0,IprimeFPurvisPerm[2]=0,IprimeFPurvisPerm[3]=0;
       
       for(cmtPvalue=0; cmtPvalue<nbRepPvalue; cmtPvalue++){
                      ArbrePvaluePurvisBin[cmtPvalue]=0;
                      ArbrePvaluePurvisNonBin2N[cmtPvalue]=0;
                      ArbrePvaluePurvisKp1[cmtPvalue]=0;
                      ArbrePvaluePurvisPerm[cmtPvalue]=0;
                      ArbrePvalueJT[cmtPvalue]=0;    
                      ArbrePvaluePurvisPurvis[cmtPvalue]=0;
                      ArbrePvaluePurvisPurvisPerm[cmtPvalue]=0;  
       }
       /*On nettoye l'arbre*/
       while(noeud!=NULL){
                           noeud->nbFeuille = 0;
                           noeud = noeud->suiv;                  
        }
        /*On marque le nombre de feuille*/
       while(feuille!=NULL){
                    feuille->nbFeuille = 1;        
                    parcourir = feuille->pere;
                    while(parcourir!=NULL){
                        parcourir->nbFeuille++;                  
                        parcourir = parcourir->pere;                                         
                    }                            
                    feuille = feuille->suiv;        
       }
       /*Pour chacun des noeuds*/
       noeud = arbre->noeuds;
       while(noeud!=NULL){
                
                 if(noeud->hauteurTotal>LimiteHauteur)calculerIprimeArbreBinaireNoeud2(noeud, &IprimeBin, &nbNoeudBin, &IprimeNonBin2N, &nbNoeudNonBin2N,&IprimeNonBinKp1, &nbNoeudNonBinKp1,&IprimeNonBinPerm, &nbNoeudNonBinPerm ,&IprimePurvis, &nbNoeudPurvis,&IprimePurvisPerm, &nbNoeudPurvisPerm  , nbRepPvalue, ArbrePvaluePurvisBin, ArbrePvaluePurvisNonBin2N, ArbrePvaluePurvisKp1,ArbrePvaluePurvisPerm,ArbrePvaluePurvisPurvis,ArbrePvaluePurvisPurvisPerm,TabnbFeuille,TempnbFeuille, MinFeuille);
                 noeud = noeud->suiv;
       }
       AfficherUnIprime(sortie, nbNoeudBin, IprimeBin, IprimeFBin, nbRepPvalue, ArbrePvaluePurvisBin);
       AfficherUnIprime(sortie, nbNoeudNonBin2N, IprimeNonBin2N, IprimeFNonBin2N, nbRepPvalue, ArbrePvaluePurvisNonBin2N);
       AfficherUnIprime(sortie, nbNoeudNonBinKp1, IprimeNonBinKp1, IprimeFNonBinKp1, nbRepPvalue, ArbrePvaluePurvisKp1);
       AfficherUnIprime(sortie, nbNoeudNonBinPerm, IprimeNonBinPerm, IprimeFNonBinPerm, nbRepPvalue, ArbrePvaluePurvisPerm);
       AfficherUnIprime(sortie, nbNoeudPurvis, IprimePurvis, IprimeFPurvis, nbRepPvalue, ArbrePvaluePurvisPurvis);
       AfficherUnIprime(sortie, nbNoeudPurvisPerm, IprimePurvisPerm, IprimeFPurvisPerm, nbRepPvalue, ArbrePvaluePurvisPurvisPerm);
       if(sortie!=NULL)fprintf(sortie, "\t%d",nbRepPvalue);
}


void CalculerIprimeListeArbreBinaire(FILE* sortie, Arbre* arbre, double* IprimeF, int nbRepPvalue, double* ArbrePvaluePurvis,double* ArbrePvalueJT, boolean BaliseBinaire){
       Arbre* parc = arbre;
       int nbArbre=0; 
       double IprimeArbre[5]={0,0,0,0,0}, Iprime[5]={0,0,0,0,0};      
       while(parc!=NULL){
                 CalculerIprimeArbreBinaire(sortie,parc, IprimeArbre,nbRepPvalue,ArbrePvaluePurvis,ArbrePvalueJT, BaliseBinaire);                    
                 parc = parc->suiv;
                 if(IprimeArbre[0]!=-1){
                                     Iprime[0]+=IprimeArbre[0];
                                     Iprime[1]+=IprimeArbre[1];                                     
                                     nbArbre++;
                 }
                 
       }
       if(nbArbre==0){
                 IprimeF[0]=-1;
                 IprimeF[1]=-1;
                      
       }else{
             IprimeF[0]= Iprime[0]/nbArbre;
             IprimeF[1]= Iprime[1]/nbArbre;
       }

}
