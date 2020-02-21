#include "./jt_shao.h"
/*Nombre de noeud entre le root et la feuille sans prendre en compte les noeuds inferieur a zero*/
int NbNoeudFeuilleRoot(Noeud* Feuille){
       int nbNoeud=0;
       Feuille =Feuille->pere;
       while(Feuille!=NULL){
                            /*Si la longeur de la branche n'est pas nulle*/
               if(!Feuille->EstNull)nbNoeud++;                            
                            
                            /**/
                            Feuille = Feuille->pere;
       }
    return nbNoeud;
}

int NbSousNoeudParNoeud(Noeud* noeud){
         int nbNoeudDessous = 1;                      
         if(noeud->fils_1==NULL)return 0;
         nbNoeudDessous+=NbSousNoeudParNoeud(noeud->fils_1);
         nbNoeudDessous+=NbSousNoeudParNoeud(noeud->fils_2);
         
        
         if(noeud->hauteur>0){
                              noeud->nbNoeud = nbNoeudDessous;
                              return nbNoeudDessous;
         }
         else{
               noeud->nbNoeud = nbNoeudDessous-1;   
               return nbNoeudDessous-1;
         }
}
/*Retourne la position maximal d'un double pour un tableau double*/
int PositionMaxDouble(double* tableau,int nbCase){
    int cmt,posMax = 0;
    double nbMax=tableau[0];
    if(nbCase==1)return(posMax);
    for(cmt=1; cmt<nbCase; cmt++){
               if(nbMax<tableau[cmt]){
                                     posMax = cmt;
                                     nbMax = tableau[cmt];                        
               }         
               
    }
    return(posMax);
}
/*Classe le nombre d'embranchement de facon croissante*/
void ClassernbEmbranchement(int* NbEmbranchement,double* listehauteur,int nbNoeud, int nbNoeudVrai){
        int NewNbEmbranchement[nbNoeud];
        double NewListeHauteur[nbNoeud];
        int position, cmt;
        int sommeNoeud = 0;
        /*Pour chacun des noeuds */
         for(cmt=0; cmt<nbNoeud ; cmt++){
                      /*On recupere la */
                      position = PositionMaxDouble(listehauteur,nbNoeud-cmt);    
                      NewNbEmbranchement[cmt] = NbEmbranchement[position]; 
                      NewListeHauteur[cmt] = listehauteur[position];
                      NbEmbranchement[position] = NbEmbranchement[nbNoeud-cmt-1];
                      listehauteur[position] = listehauteur[nbNoeud-cmt-1]; 
                      
   
         }

          for(cmt=0; cmt<nbNoeud ; cmt++){
                     NbEmbranchement[cmt] = NewNbEmbranchement[cmt];
                     listehauteur[cmt] =  NewListeHauteur[cmt];
                     #ifdef ERREUR
                     if(NbEmbranchement[cmt]!=-1)sommeNoeud++;
                     #endif

          }
          #ifdef ERREUR
          if(sommeNoeud!=nbNoeudVrai)erreur("ClassernbEmbranchement : sommeNoeud!=nbNoeud sommeNoeud %d nbNoeudVrai %d ",sommeNoeud,nbNoeudVrai  );
          #endif  
}
int GlobalNbNum;
boolean nbEmbranchementArbre(Noeud* noeud, int* NbEmbranchement,double* listehauteur, int Num, int nbVraiNoeud){
     boolean Balise = TRUE;
     if(noeud->fils_1==NULL && noeud->fils_2==NULL )return FALSE;
     if(Num>=nbVraiNoeud)erreur("Num=>nbVraiNoeud %d %d ",Num, nbVraiNoeud);
     if(noeud->fils_1->EstNull){ 
                                NbEmbranchement[Num]++;
                                nbEmbranchementArbre(noeud->fils_1, NbEmbranchement,listehauteur, Num, nbVraiNoeud);
                                
     }else if(noeud->fils_1->fils_1!=NULL && noeud->fils_1->fils_2!=NULL ){ 
            GlobalNbNum++;
            if(NbEmbranchement[GlobalNbNum]!=1 && NbEmbranchement[GlobalNbNum]!=-1)erreur("Vous ecrivez sur NbEmbranchement[NewNum+1] %d %d", NbEmbranchement[GlobalNbNum], GlobalNbNum);              
            listehauteur[GlobalNbNum]=noeud->fils_1->hauteurTotal;
            NbEmbranchement[GlobalNbNum]=1;
            Balise=nbEmbranchementArbre(noeud->fils_1, NbEmbranchement,listehauteur, GlobalNbNum, nbVraiNoeud);      
            if(Balise==FALSE)GlobalNbNum--;
     }
     if(noeud->fils_2->EstNull){
                             NbEmbranchement[Num]++;
                             nbEmbranchementArbre(noeud->fils_2, NbEmbranchement, listehauteur, Num, nbVraiNoeud);   
     }else if(noeud->fils_2->fils_1!=NULL &&noeud->fils_2->fils_2!=NULL ){
            GlobalNbNum++;
            if(NbEmbranchement[GlobalNbNum]!=1 && NbEmbranchement[GlobalNbNum]!=-1)erreur("Vous ecrivez sur NbEmbranchement[NewNum+1] %d %d", NbEmbranchement[GlobalNbNum], GlobalNbNum);        
            listehauteur[GlobalNbNum]=noeud->fils_2->hauteurTotal;
            NbEmbranchement[GlobalNbNum]=1;
            Balise = nbEmbranchementArbre(noeud->fils_2, NbEmbranchement,listehauteur,  GlobalNbNum, nbVraiNoeud);      
            if(Balise==FALSE)GlobalNbNum--;
     }
     return TRUE;
}

int NbNoeudSousArbreAleatoire(int nbFeuilles,int nbNoeud, int* NbEmbranchements){
     int noeud[nbFeuilles], cmtNoeud, cmtMultiEmbranchement, PosNoeud1, cmt2Noeud, PosNoeud2;
     int   nbNoeudSous2 =0, nbFeuilles2,cmtNoeud3;
     int nbEmbranchement;
     for(cmtNoeud=0; cmtNoeud<nbFeuilles; cmtNoeud++){
                    noeud[cmtNoeud] = 1;   
                    
     }
     /*On classe les noeuds*/
     cmtMultiEmbranchement = 0;
     cmtNoeud = nbFeuilles;
     cmtNoeud3 = nbNoeud-1;
     nbNoeudSous2 =0;
     while(cmtNoeud>1){
                             /*Je choisit le premier noeud*/
                             PosNoeud1 = (int)(aleatoire()*cmtNoeud);
                             /*je recupere le Nombre de feuille sous le premier embr*/
                             nbFeuilles2 = noeud[PosNoeud1];
                             /*On met a la place du noeud le dernier*/
                             noeud[PosNoeud1] = noeud[cmtNoeud-1];
                             noeud[cmtNoeud-1] = -1;
                             cmtNoeud--;
                             nbEmbranchement = NbEmbranchements[cmtNoeud3];
                             if(nbEmbranchement<=0)erreur("NbNoeudSousArbreAleatoire : nbEmbranchement<0 %d %d %d %d",nbEmbranchement,cmtNoeud, nbNoeud,cmtNoeud3);
                             for(cmt2Noeud=0;cmt2Noeud<nbEmbranchement;cmt2Noeud++){
                                     PosNoeud2 =(int)(aleatoire()*cmtNoeud);
                                     nbFeuilles2+= noeud[PosNoeud2];
                                     if(cmt2Noeud+1==nbEmbranchement){
                                            noeud[PosNoeud2] = nbFeuilles2;    
                                            nbNoeudSous2+=  nbFeuilles2;                                                                                  
                                            cmtNoeud3--;
                                     }
                                     else{
                                          noeud[PosNoeud2] = noeud[cmtNoeud-1];
                                          noeud[cmtNoeud-1] = -1;                                         
                                          cmtNoeud--;
                                     }
                             }   

                                                     
     }
     return nbNoeudSous2;
}
/*Calcule la valeur d'un arbre Shao Binaire*/
void CalculerShaoBinaire(FILE* ecrire,Arbre* arbre,int nbRepPvalueShao){
    Noeud* parc=arbre->feuilles;
    int NbNoeud2 = arbre->nb_noeuds, cmt2temp;
    int NbEmbranchements[NbNoeud2];
    double ListeHauteur[NbNoeud2];
    int nbFeuilles = 0, nbNoeudTotal=0, listeNbNoeud[arbre->nb_feuilles], cmtFeuilles, cmtPvalue, cmt, cmtemp;
    double varShao, Shao, temp, MinShao, MaxShao, cmtBPvalue, ShaoPvalue;
    while(parc!=NULL){
                                  listeNbNoeud[nbFeuilles]=NbNoeudFeuilleRoot(parc);
                                  nbNoeudTotal+=listeNbNoeud[nbFeuilles];
                                  nbFeuilles++;
             parc = parc->suiv;        
    }           
    varShao=0;
    MinShao = MinNoeudShao(nbFeuilles, arbre->nbVraiNoeuds);
    MaxShao = MaxNoeudShao(nbFeuilles, arbre->nbVraiNoeuds);
    #ifdef ERREUR
    if(MaxShao<=MinShao)erreur("MaxShao<=MinShao nbFeuilles %d nbVraiNoeuds %d MaxShao %d MinShao %d",nbFeuilles,arbre->nbVraiNoeuds,MaxShao,MinShao );
    #endif
     Shao = (nbNoeudTotal - MinShao)/(MaxShao -MinShao);         
     cmtBPvalue = 0;        
    for(cmt=0;cmt<NbNoeud2; cmt++){
                            NbEmbranchements[cmt]=-1; 
                            ListeHauteur[cmt] = -1;
    }
    NbEmbranchements[0] = 1;
    ListeHauteur[0] = arbre->sommet->hauteurTotal;
    GlobalNbNum = 0;
    nbEmbranchementArbre(arbre->sommet,NbEmbranchements,ListeHauteur,GlobalNbNum,NbNoeud2);  
    ClassernbEmbranchement(NbEmbranchements,ListeHauteur,NbNoeud2, arbre->nbVraiNoeuds);
    cmtemp = 0;
    cmt2temp = 0;
  /*  for(cmt=0;cmt<NbNoeud2; cmt++){
                            if(NbEmbranchements[cmt]>-1){
                                                         cmtemp++;
                                                         cmt2temp+=NbEmbranchements[cmt];
                            }
                            printf("%d ",NbEmbranchements[cmt] );
    }                       
    printf("%d %d ",cmtemp, cmt2temp );      
    PAUSE();      */  
    for(cmtPvalue=0; cmtPvalue<nbRepPvalueShao; cmtPvalue++){    
    ShaoPvalue =(NbNoeudSousArbreAleatoire(nbFeuilles,arbre->nbVraiNoeuds,NbEmbranchements ) -MinShao)/(MaxShao -MinShao);
       if(ShaoPvalue>Shao)cmtBPvalue++;          
    }
    
    for(cmtFeuilles=0; cmtFeuilles<nbFeuilles; cmtFeuilles++){
              temp=(listeNbNoeud[cmtFeuilles]-nbNoeudTotal);
              varShao+=(temp*temp);
    }
    
    varShao/=(double)nbFeuilles;
    if(nbRepPvalueShao>0)cmtBPvalue/=(double)nbRepPvalueShao;
    else cmtBPvalue = -1;
    fprintf(ecrire, "\t%f\t%f\t%d",Shao,cmtBPvalue,nbNoeudTotal );
                         
}

/*cALCULE la valeur minimale de shao ==> arbre le plus desequilibre */
double MaxNoeudShao(int nbFeuille, int nbNoeud){
        double maxIs = nbFeuille;
        int cmt;
        for(cmt=1; cmt<=nbNoeud
        
        
        ; cmt++)maxIs+=(nbFeuille-cmt);
        return maxIs;
}
/*cALCULE la valeur minimale de shao ==> arbre le plus equilibre */
double MinNoeudShao(int nbFeuille, int nbNoeud){
        double minIs = nbFeuille, tempIs;
        int l, mi, cmt, cmt2;
        int deuxPuissancecmt ;
        int deuxPuissancecmtMoinsUn;
        int cmtNoeud=1;
        l = (int)(log(nbFeuille)/log(2)+0.9999);
        for(cmt=1; cmt<=l-1; cmt++){
          deuxPuissancecmt = (int)pow(2.0,(float)cmt);
          deuxPuissancecmtMoinsUn = (int)(((double)deuxPuissancecmt)/2.0);
          mi = (int)((nbFeuille+deuxPuissancecmtMoinsUn-1)/(deuxPuissancecmt));
          for(cmt2=1; cmt2<=mi; cmt2++){
                 /*si le nombre de feuille est paire*/
                 if(cmtNoeud<nbNoeud){  
                                  if((nbFeuille%deuxPuissancecmtMoinsUn)==0) tempIs=deuxPuissancecmt;
                                  else if( cmt2< mi)tempIs=deuxPuissancecmt;
                                  else tempIs=(nbFeuille%deuxPuissancecmtMoinsUn + deuxPuissancecmtMoinsUn);
                                  minIs+=tempIs;
                 }
                 cmtNoeud++;

           }
     }
     return minIs;   
}

void CalculerShao(FILE* ecrire,Arbre* Listearbre,int nbRepPvalueIprime){
    Noeud* parc;
    int nbFeuilles = 0, nbNoeudTotal=0, *listeNbNoeud, cmtFeuilles;
    double varShao, Shao, temp, MinShao, MaxShao;
    Arbre* parcArbre;
    parcArbre = Listearbre;
    nbFeuilles=0;
    while(parcArbre!=NULL){
                           nbFeuilles+=parcArbre->nb_feuilles;
                           parcArbre = parcArbre->suiv;                         
    }
    listeNbNoeud = i_allocate(nbFeuilles);
    parcArbre = Listearbre;
    nbFeuilles = 0;
    while(parcArbre!=NULL){
       parc = parcArbre->feuilles;
        while(parc!=NULL){
                          listeNbNoeud[nbFeuilles]=NbNoeudFeuilleRoot(parc);
                          nbNoeudTotal+=listeNbNoeud[nbFeuilles];
                          nbFeuilles++;         
             parc = parc->suiv;        
        }   
        parcArbre = parcArbre->suiv;       
    }
     varShao=0;
     MinShao = MinNoeudShao(nbFeuilles, parcArbre->nbVraiNoeuds);
     MaxShao = MaxNoeudShao(nbFeuilles, parcArbre->nbVraiNoeuds);
     #ifdef ERREUR
     if(MaxShao<MinShao)erreur("MaxShao<=MinShao nbFeuilles %d nbVraiNoeuds %d MaxShao %d MinShao %d",nbFeuilles,parcArbre->nbVraiNoeuds,MaxShao,MinShao );
     #endif
     Shao = (MaxShao - nbNoeudTotal)/(MaxShao -MinShao);                              
     for(cmtFeuilles=0; cmtFeuilles<nbFeuilles; cmtFeuilles++){
              temp=(listeNbNoeud[cmtFeuilles]-nbNoeudTotal);
              varShao+=(temp*temp);        
     }
    varShao/=(double)nbFeuilles;
    if(ecrire!=NULL)fprintf(ecrire, "\t%f\t%f",Shao,varShao);
    free_tab_int(listeNbNoeud);
}
int GetMaxNoeudBinaire(Noeud* noeud, int* nbMultifurcation){
        int noeud1, noeud2;
        if(noeud->fils_1==NULL){
                                (*nbMultifurcation)+=1;  
                                return 1;
        }
        /*si la hauteur du fil est different de zero on retourne le nombre de feuille */
        else if(!noeud->EstNull){
                (*nbMultifurcation)+=1;    
                return noeud->nbNoeud;
        }
        else{
            noeud1 = GetMaxNoeudBinaire(noeud->fils_1, nbMultifurcation);
            noeud2 = GetMaxNoeudBinaire(noeud->fils_2, nbMultifurcation);
            return MAX(noeud1,noeud2);           
        }
}
double PvaluePurvisIShaoNoeud(double IShao){
       if(aleatoire()<0.5)return (1.0-IShao);
       else return IShao;
}

void CalculerShaoBinaireV2(FILE* ecrire,Arbre* arbre,int nbRepPvalueIprime){
        Noeud* parc=arbre->noeuds ;
        double Shao=0, IShao=0, IShaoTemp=0, sommeNoeud,meannbNoeud, nbNoeud2=0;
        double Pvalue, AutreDesequilibre=0, MinNoeud, tabPvalue[nbRepPvalueIprime];
        int nbMultifurcation,MaxNoeud1,MaxNoeud2, MaxNoeud, cmtPvalue;
        boolean BaliseIShao = TRUE;
        NbSousNoeudParNoeud(arbre->sommet);
        for(cmtPvalue=0; cmtPvalue<nbRepPvalueIprime; cmtPvalue++)tabPvalue[cmtPvalue]=0;
        while(parc!=NULL){
            if(parc->fils_1!=NULL && parc->fils_2!=NULL) sommeNoeud = parc->fils_1->nbNoeud+parc->fils_2->nbNoeud;
            else sommeNoeud=0;
            if(sommeNoeud>1 && (parc->hauteur>0 || parc->hauteur<-0.99)){
                if(sommeNoeud>parc->nbFeuille-2)erreur("sommeNoeud>parc->nbFeuille-2 sommeNoeud %f parc->nbFeuille-2 %d",sommeNoeud,parc->nbFeuille-2 );
                nbMultifurcation = 0;             
                MaxNoeud1 = GetMaxNoeudBinaire(parc->fils_1,&nbMultifurcation );             
                MaxNoeud2 = GetMaxNoeudBinaire(parc->fils_2,&nbMultifurcation );             
                MaxNoeud = MAX(MaxNoeud1,MaxNoeud2);
                #ifdef ERREUR
                if(MaxNoeud>sommeNoeud)erreur("MaxNoeud>sommeNoeud");
                #endif
                meannbNoeud = GetMeanMeanNoeud((int)sommeNoeud, nbMultifurcation) ;
                MinNoeud = (double)(MIN(parc->fils_1->nbNoeud, parc->fils_2->nbNoeud));
                Shao += 1.0/MaxNoeud; 
                if(sommeNoeud>1){
                                 if(EstErreur(meannbNoeud)){
                                                            IShao=CONSTERREUR;
                                                            BaliseIShao=FALSE;
                                                            IShaoTemp = CONSTERREUR;
                                 }
                                 else if(BaliseIShao && sommeNoeud>nbMultifurcation-1 && parc->nbFeuille>nbMultifurcation*2-1){
                                      IShaoTemp=(MaxNoeud-(double)meannbNoeud)/(sommeNoeud- (double)meannbNoeud);
                                      for(cmtPvalue=0; cmtPvalue<nbRepPvalueIprime; cmtPvalue++)tabPvalue[cmtPvalue]+=PvaluePurvisIShaoNoeud(IShaoTemp);
                                      IShao+=IShaoTemp;/*
                                      fprintf(stderr, "%d %d %f %f %f %d\n", nbMultifurcation, MaxNoeud,meannbNoeud,sommeNoeud,IShaoTemp, parc->nbFeuille);
                                */
                                 }
                                 AutreDesequilibre+=(MaxNoeud-MinNoeud)/sommeNoeud;
                                 nbNoeud2++;
                }
            }
            parc = parc->suiv;
       }
      Pvalue = 0.0; 
     for(cmtPvalue=0; cmtPvalue<nbRepPvalueIprime; cmtPvalue++)if(tabPvalue[cmtPvalue]>IShao)Pvalue+=1.0;  
     if(ecrire!=NULL){
                      if(BaliseIShao)fprintf(ecrire, "\t%f\t%f\t%f\t%f",Shao, IShao/nbNoeud2 ,Pvalue/(double)nbRepPvalueIprime, AutreDesequilibre/nbNoeud2);
                      else fprintf(ecrire, "\t%f\t%f\t%f\t%f",Shao, -1.0 ,-1.0, AutreDesequilibre/nbNoeud2);
     }                 
}
