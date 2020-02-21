#include "./jt_lib/jt_string.h"
#include "./jt_lib/jt_fichier.h"
#include "./jt_arbre/jt_arbre.h"
#include "./jt_lib/macro.h"
#include "./jt_lib/jt_aleatoire.h"
#include "./jt_arbre/jt_Iprime.h"
#include "./jt_arbre/jt_shao.h"
#include "./jt_arbre/MeanFeuilleMin.h" 

boolean Global_CalcIprime;
boolean Global_CalcShao;
void TesterTabIntClasseMax(){
   int tab[10]={9,4,7,6,3,4,3,8,8,0};
  int cmt;
  classeIntMethodeMax(tab, 10, 9);
  for(cmt=0; cmt<10; cmt++)printf("%d ",tab[cmt] );
  PAUSE();    
     
}
/**
void AnalyserArbres(FILE* sortie, Tab_String* tab, int nbRepPvalueIprime, boolean BaliseBinaire)


*/

void AnalyserArbres(FILE* sortie, Tab_String* tab, int nbRepPvalueIprime, boolean BaliseBinaire){
     int cmt, cmtArbre=0;
     double Iprime[4]={0,0,0,0};
     Arbre* arbre;
     Noeud* noeud;
     double *ArbrePvaluePurvis, *ArbrePvalueJT;
     ArbrePvaluePurvis = d_allocate(nbRepPvalueIprime);
     ArbrePvalueJT = d_allocate(nbRepPvalueIprime);
     fprintf(sortie,"Num\tLongeurTotal\tLongeurExterne\tLongeurInterne\tEchantillon\tTMRCA\tnbNoeudNonNUll\tnbBrancheNonNull");
     if(Global_CalcIprime)fprintf(sortie, "\tIprime\tNbNoeudIprime\tPVIpPur\tnbNoeudDeseq\tnbRepPvalue");
     if(Global_CalcShao){
                         fprintf(sortie, "\tShao\tPvalueShao\tNbNoeudShao");
                        /* fprintf(sortie,"\tShaoV2\tIShao\tIShaoPvaluePur\tSIShao");*/
     }
     fprintf(sortie,"\n");
     for(cmt=0; cmt<tab->nb_string; cmt++){
            arbre = Lire_arbre_String((tab->Get(tab, cmt)));
            
            if(arbre!=NULL){
                            
                            fprintf(sortie, "%d\t%f\t%f\t%f\t%d\t%f\t%d",cmtArbre, arbre->longeur, arbre->longeurExterne, arbre->longeurInterne, arbre->nb_feuilles, arbre->TMRCA, arbre->nbVraiNoeuds);      
                           /* HauteursBranchesDeuxADeux(arbre);*/
                           if(Global_CalcIprime)CalculerIprimeArbreBinaire(sortie, arbre, Iprime, nbRepPvalueIprime, ArbrePvaluePurvis, ArbrePvalueJT, BaliseBinaire);
                           if(Global_CalcShao){
                                CalculerShaoBinaire(sortie,arbre,nbRepPvalueIprime);
                              /*  CalculerShaoBinaireV2(sortie,arbre,nbRepPvalueIprime);*/
                            }
                            noeud = arbre->noeuds;
                            fprintf(sortie,"\n");
                            freeArbre(arbre);
                            arbre = NULL;
                            cmtArbre++;

            } 
     }
     free_tab_double(ArbrePvaluePurvis);
     free_tab_double(ArbrePvalueJT);
}

void AnalyserArbres2(FILE* sortie, Tab_String* tab, int nbRepPvalueIprime,int MinFeuille, double LimiteHauteur){
     int cmt, cmtArbre=0, NbNoeud=0;
     double IprimeBin[4]={0,0,0,0}, IprimeNonBin2N[4]={0,0,0,0}, IprimeNonBinKp1[4]={0,0,0,0}, IprimePurvis[4]={0,0,0,0}, IprimePurvisPerm[4]={0,0,0,0}, IprimeNonBinPerm[4]={0,0,0,0};
     Arbre* arbre;
     Noeud* noeud;
     double *ArbrePvaluePurvisBin, *ArbrePvaluePurvisNonBin2N, *ArbrePvaluePurvisNonBinKp1, *ArbrePvalueJT,*ArbrePvaluePurvisPurvis,*ArbrePvaluePurvisPerm,*ArbrePvaluePurvisPurvisPerm ;
     int * TabnbFeuille=NULL,*TempnbFeuille=NULL, nbHaplotype;
     ArbrePvaluePurvisBin = d_allocate(nbRepPvalueIprime);
     ArbrePvaluePurvisNonBin2N = d_allocate(nbRepPvalueIprime);
     ArbrePvaluePurvisNonBinKp1 = d_allocate(nbRepPvalueIprime);
     ArbrePvalueJT = d_allocate(nbRepPvalueIprime);
     ArbrePvaluePurvisPurvis = d_allocate(nbRepPvalueIprime);
     ArbrePvaluePurvisPerm = d_allocate(nbRepPvalueIprime);
     ArbrePvaluePurvisPurvisPerm = d_allocate(nbRepPvalueIprime);     
     fprintf(sortie,"Num\tLongeurTotal\tLongeurExterne\tLongeurInterne\tEchantillon\tTMRCA\tnbNoeudNonNUll\tnbBrancheNonNull\tnbHaplotype");
     if(Global_CalcIprime)fprintf(sortie, "\tIprimeBin\tNbNoeudIprimeBin\tPVIpPurBin\tIprimeNonBin2N\tNbNoeudIprimeNonBin2N\tPVIpPurNonBin2N\tIprimeNonBinKp1\tNbNoeudIprimeNonBinKp1\tPVIpPurNonBinKp1\tIprimeNonBinPerm\tNbNoeudIprimeNonBinPerm\tPVIpPurNonBinPerm\tIprimePurvis\tNbNoeudIprimePurvis\tPVIpPurPurvis\tIprimePurvisPerm\tNbNoeudIprimePurvisPerm\tPVIpPurPurvisPerm\tnbRepPvalue");
     if(Global_CalcShao){
                         fprintf(sortie, "\tShao\tPvalueShao\tNbNoeudShao");
                        /* fprintf(sortie,"\tShaoV2\tIShao\tIShaoPvaluePur\tSIShao");*/
     }
     fprintf(sortie,"\n");
     for(cmt=0; cmt<tab->nb_string; cmt++){
            arbre = Lire_arbre_String((tab->Get(tab, cmt)));
            
            if(arbre!=NULL){
                            if(cmtArbre==0){
                                   TabnbFeuille = i_allocate(arbre->nb_noeuds*2);
                                   TempnbFeuille = i_allocate(arbre->nb_noeuds*2);     
                                   NbNoeud =  arbre->nb_noeuds;          
                            }
                            if(NbNoeud!=arbre->nb_noeuds){
                                    free(TabnbFeuille);       
                                    free(TempnbFeuille);                                     
                                    TabnbFeuille = i_allocate(arbre->nb_noeuds*2);
                                    TempnbFeuille = i_allocate(arbre->nb_noeuds*2);     
                                    NbNoeud =  arbre->nb_noeuds;      
                                        
                                                                                 
                            }
                            nbHaplotype = GetnbHaplotype(arbre);
                            fprintf(sortie, "%d\t%f\t%f\t%f\t%d\t%f\t%d\t%d\t%d",cmtArbre, arbre->longeur, arbre->longeurExterne, arbre->longeurInterne, arbre->nb_feuilles, arbre->TMRCA, arbre->nbVraiNoeuds,arbre->nbVraiBranches, nbHaplotype);      
                           /* HauteursBranchesDeuxADeux(arbre);*/
                           if(Global_CalcIprime)CalculerIprimeArbreBinaireNew2(sortie, arbre, IprimeBin, IprimeNonBin2N, IprimeNonBinKp1,IprimeNonBinPerm,IprimePurvis,IprimePurvisPerm,  nbRepPvalueIprime, ArbrePvaluePurvisBin, ArbrePvaluePurvisNonBin2N, ArbrePvaluePurvisNonBinKp1, ArbrePvaluePurvisPerm,ArbrePvaluePurvisPurvis,ArbrePvaluePurvisPurvisPerm ,ArbrePvalueJT, TabnbFeuille,TempnbFeuille, MinFeuille,LimiteHauteur);
                           /*calculerIprimeArbreBinaireNew2(sortie, arbre, Iprime, nbRepPvalueIprime, ArbrePvaluePurvis, ArbrePvalueJT, BaliseBinaire);
                           */if(Global_CalcShao){
                                CalculerShaoBinaire(sortie,arbre,nbRepPvalueIprime);
                              /*  CalculerShaoBinaireV2(sortie,arbre,nbRepPvalueIprime);*/
                            }
                            
                            noeud = arbre->noeuds;
                            fprintf(sortie,"\n");
                            freeArbre(arbre);
                            arbre = NULL;
                            cmtArbre++;

            } 
     }
     free_tab_double(ArbrePvaluePurvisBin);
     free_tab_double(ArbrePvaluePurvisNonBin2N);
     free_tab_double(ArbrePvaluePurvisNonBinKp1);
     free_tab_double(ArbrePvaluePurvisPerm);
     free_tab_double(ArbrePvaluePurvisPurvisPerm);
     free_tab_double(ArbrePvalueJT);
     free(TabnbFeuille);       
     free(TempnbFeuille);      
}

char* GetArgument(int argc, char** argv, char* argument){
      int cmt=0;
      boolean balise=TRUE;
      char* sortie=NULL;
      while(balise){
              if(strcmp(argument, argv[cmt])==0){
                     if(argc!=cmt+1){
                            balise =FALSE;
                            sortie =  argv[cmt+1];       
                     }             
              }
              
              if(cmt+1==argc){
                         balise=FALSE;
                         sortie=NULL;
              }      
              cmt++;
      }
      return sortie;
}
boolean verifArgument(int argc, char** argv, char* argument){
      int cmt=0;
      boolean balise=TRUE;
      while(balise){
              if(strcmp(argument, argv[cmt])==0){
                                  return TRUE;           
              }
              
              if(cmt+1==argc){
                         balise=FALSE;
              }      
              cmt++;
      }
      return FALSE;
}


/*
int main(int argc, char** argv){
    int cmt, cmt2;
    double valeur;
    FILE* ecrire=fopen("donneeMin.out", "w");
    fprintf(ecrire,"nbFeuille\t2\t3\t4\t5\n");
    for(cmt=3; cmt<2000; cmt++){
               fprintf(ecrire,"%d", cmt);
               for(cmt2=2; cmt2<6; cmt2++){
                              valeur =  GetMeanMeanFeuille(cmt,cmt2);                               
                              if(valeur==CONSTERREUR)valeur=-1;
                              fprintf(ecrire, "\t%f",valeur );                               
               }
               fprintf(ecrire,"\n");
    }
    
}*/
/*Main pour le cas ou le nombre de feuille minimum voulue est de 2N*/
#ifdef NBFEUILLE2N
int main(int argc, char** argv){
 Fichier* fichier;
  Tab_String* tab;
  init_aleatoire();
  FILE* sortie=NULL, *SortieRapport=stderr;
  int nbRepPvalueIprime = 10;
  Global_CalcIprime = TRUE;
  Global_CalcShao = FALSE;
  if(!BonBinaire(argv[0],"CalcIPrime2.exe")){
         erreur("Mauvais Binaire %s %s ",argv[0],"CalcIPrime2.exe" );                                                                           
  }
  fprintf(SortieRapport,"Rapport\n" );
  #ifdef MULTINOEUD
  erreur("Option de compilation : MULTINOEUD activee");
  #endif
  
  #ifdef IMFMETHODE2
  erreur("Option compilation IMFMETHODE2 present lors de la compilation");
  #endif
  
  if(argc==3){
              sortie=stdout;
              fprintf(SortieRapport,"Nomfichier sortie : stdout" );
  }
  else if (argc==4){
       fprintf(SortieRapport,"Nomfichier sortie : %s\n", argv[3] );
       sortie = fopen(argv[3], "w");
  }
  else erreur(" Ligne de commande : exe [tree] nbPvalue [sortie]");   
  nbRepPvalueIprime = atoi(argv[2]);
  fflush(sortie);
  fichier = Fichier_Create(String_Create(argv[1]), 'w');
  tab = fichier->Lire_Ligne(fichier);
  AnalyserArbres(sortie, tab, nbRepPvalueIprime, FALSE);
  tab->Free(tab);
  if (argc==3)fclose(sortie);
  return 0;   

}
#else

/*
int main(void){
 TestIprimeEquilibre();   
 PAUSE();   
}*/
/*Main pour le cas ou le nombre de feuille minimum voulue est de N+k-1*/
/*main_CalcIprime*/
int main(int argc, char** argv){
 Fichier* fichier;
  Tab_String* tab;
  char* MSGErreur = " Ligne de commande : exe [tree] -p [nbPvalue] -s [sortie (opt==> stdout)] -l limite";
  char* argTemp;
  init_aleatoire();
  FILE* sortie=NULL, *SortieRapport=stderr;
  int nbRepPvalueIprime = 10;
  int MinFeuille;
  boolean Binaire = FALSE; 
  Global_CalcIprime = TRUE;
  Global_CalcShao = FALSE;
  char* argLim;
  double LimiteHauteur;
  
  #ifdef IMFMETHODE2
  if(!BonBinaire(argv[0],"CalcIPrimeMF.exe")){
         erreur("Mauvais Binaire %s %s ",argv[0],"CalcIPrime.exe" );                                                                           
  }
  #else
  #ifndef IMFV2
  if(!BonBinaire(argv[0],"CalcIPrime.exe")){
         erreur("Mauvais Binaire %s %s ",argv[0],"CalcIPrime.exe" );                                                                           
  }
  #endif
  #endif
  fprintf(SortieRapport,"Rapport\n" );
  #ifdef MULTINOEUD
  erreur("Option de compilation : MULTINOEUD activee");
  #endif
  /*Recuperation des arguments*/
  /*Pvalue*/
  argTemp=GetArgument(argc,argv, "-p");
  if(argTemp==NULL)erreur(MSGErreur); 
  else nbRepPvalueIprime = atoi(argTemp);
  /*-s*/
  argTemp=GetArgument(argc,argv, "-s");
  if(argTemp==NULL){
                     fprintf(SortieRapport,"Nomfichier sortie : stdout" ); 
                     sortie=stdout;
  }
  else{
       fprintf(SortieRapport,"Nomfichier sortie : %s\n", argTemp );
       sortie = fopen(argTemp, "w");
  }
  
  if(verifArgument(argc,argv, "-shao")){
           Global_CalcShao = TRUE;                  
  }
  /*Pour le nombre maximum de feuille a analyser*/
  argTemp=GetArgument(argc,argv, "-mf");
  
  /*Pour la limite*/
  argLim=GetArgument(argc,argv, "-l");
  if(argLim!=NULL)LimiteHauteur=atof(argLim);
  else LimiteHauteur = -1;
  
  if(argTemp==NULL){
                     MinFeuille = 0;
  }
  MinFeuille = atoi(argTemp);
  fichier = Fichier_Create(String_Create(argv[1]), 'w');
  tab = fichier->Lire_Ligne(fichier);
  #ifndef IMFV2
   argTemp=GetArgument(argc,argv, "-b");
  if(argTemp!=NULL){
                    if(strcmp(argTemp,"B")==0)  Binaire    = TRUE; 
                    else  if(strcmp(argTemp,"N")==0)  Binaire    = FALSE; 
                    else erreur(MSGErreur);
  }else Binaire = TRUE;
  #endif
  #ifdef IMFV2
 /*  if(!BonBinaire(argv[0],"CalcIPrimeV2.exe")){
         erreur("Mauvais Binaire %s %s ",argv[0],"CalcIPrimeV2.exe" );                                                                           
  }*/
    AnalyserArbres2(sortie, tab, nbRepPvalueIprime, MinFeuille, LimiteHauteur);
  #else                  
  /*-b*/


  
  
  AnalyserArbres(sortie, tab, nbRepPvalueIprime, Binaire);
  #endif
  tab->Free(tab);
  if (sortie!=stdout)fclose(sortie);
  return 0;   
}
#endif

