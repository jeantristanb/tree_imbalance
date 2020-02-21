#include "jt_coalescence.h"
/*Genere un processus de coalecence jusqu'à obtenir n noued retourne 
le tableau constitue de la repartition des n dernier noeuds, alloue dynamiquement le tableau contenant
le nombre de feuille
*/
int* GenererCoalecensceNnoeud(int nbFeuille, int nbNoeud){
     int *listeNoeud=i_allocate(nbFeuille);
     int cmtFeuille;
     int Pos1,Pos2, nbFeuillePos1;
     /*Initialisation du tableau contenant les noeuds, intialement il contient une feuille*/
     for(cmtFeuille=0; cmtFeuille<nbFeuille; cmtFeuille++)listeNoeud[cmtFeuille]=1;
     cmtFeuille=nbFeuille;
     /*Tant qu'on apas le bon nombre de noeud*/
     while(cmtFeuille>nbNoeud){
                /*On tire le premier noeud formant la coalescence  */
                Pos1=(int)(aleatoire()*cmtFeuille);
                /*On recupere le nombre de feuille de la position 1*/
                nbFeuillePos1 = listeNoeud[Pos1];
                /*On enleve du tableau cette position ( on le remplace par le dernier element du tableau)*/
                listeNoeud[Pos1] = listeNoeud[cmtFeuille-1];
                listeNoeud[cmtFeuille-1] = -1;
                cmtFeuille--;
                /*On tire la seconde Position*/
                Pos2 = (int)(aleatoire()*cmtFeuille);
                /*On lui ajoute le nombre de feuille de premiere position*/
                listeNoeud[Pos2]+=nbFeuillePos1;
     }
                             
     return(listeNoeud);
     
}
/*Genere un processus de coalecence jusqu'à obtenir n noued retourne 
le tableau constitue de la repartition des n dernier noeuds, Demande en entrée un tableau contenant au moins le nombre de feuille
*/
int* GenererCoalecensceNnoeud2(int nbFeuille, int nbNoeud, int* listeNoeud){
     int cmtFeuille;
     int Pos1,Pos2, nbFeuillePos1;
     /*Initialisation du tableau contenant les noeuds, intialement il contient une feuille*/
     for(cmtFeuille=0; cmtFeuille<nbFeuille; cmtFeuille++)listeNoeud[cmtFeuille]=1;
     cmtFeuille=nbFeuille;
     /*Tant qu'on apas le bon nombre de noeud*/
     while(cmtFeuille>nbNoeud){
                /*On tire le premier noeud formant la coalescence  */
                Pos1=(int)(aleatoire()*cmtFeuille);
                /*On recupere le nombre de feuille de la position 1*/
                nbFeuillePos1 = listeNoeud[Pos1];
                /*On enleve du tableau cette position ( on le remplace par le dernier element du tableau)*/
                listeNoeud[Pos1] = listeNoeud[cmtFeuille-1];
                listeNoeud[cmtFeuille-1] = -1;
                cmtFeuille--;
                /*On tire la seconde Position*/
                Pos2 = (int)(aleatoire()*cmtFeuille);
                /*On lui ajoute le nombre de feuille de premiere position*/
                listeNoeud[Pos2]+=nbFeuillePos1;
     }                        
     return(listeNoeud);
}

/*Genere un processus de coalecence jusqu'à obtenir n noued retourne 
le tableau constitue de la repartition des n dernier noeuds, Demande en entrée un tableau contenant au moins le nombre de feuille
*/
int* GenererCoalecensceNnoeudNbNoeud(int nbFeuille, int nbNoeud, int* listeNoeud){
     int cmtFeuille;
     int Pos1,Pos2, nbNoeudPos1;
     /*Initialisation du tableau contenant les noeuds, intialement il contient une feuille*/
     for(cmtFeuille=0; cmtFeuille<nbFeuille; cmtFeuille++)listeNoeud[cmtFeuille]=0;
     cmtFeuille=nbFeuille;
     /*Tant qu'on apas le bon nombre de noeud*/
     while(cmtFeuille>nbNoeud){
                /*On tire le premier noeud formant la coalescence  */
                Pos1=(int)(aleatoire()*cmtFeuille);
                /*On recupere le nombre de feuille de la position 1*/
                nbNoeudPos1 = listeNoeud[Pos1];
                /*On enleve du tableau cette position ( on le remplace par le dernier element du tableau)*/
                listeNoeud[Pos1] = listeNoeud[cmtFeuille-1];
                listeNoeud[cmtFeuille-1] = -1;
                cmtFeuille--;
                /*On tire la seconde Position*/
                Pos2 = (int)(aleatoire()*cmtFeuille);
                /*On lui ajoute le nombre de feuille de premiere position*/
                listeNoeud[Pos2]+=(nbNoeudPos1+1);
     }                        
     return(listeNoeud);
}

/*NbFeuilleMoyen2<-function(nbNoeud, nbFeuille, RapMaxObsFeuille){
maxobs<-(RapMaxObsFeuille*nbFeuille)
maxtheo<-nbFeuille-nbNoeud+1
return(ceiling(2*maxobs-maxtheo-1))
}*/
double MeanNBFeuilleMoyenCoalescence(int nbFeuille, int nbNoeud, int nbRepetition){
       int cmtRepetition, cmtNoeud, *listeNoeud = i_allocate(nbFeuille), MaxTemp;
       double MoyenneMaxObs=0.0, MaxTheo=nbFeuille-nbNoeud+1 ;
       double nbFeuilleMoyen;
       if(nbFeuille<nbNoeud)return -1;
       for(cmtRepetition=0; cmtRepetition<nbRepetition; cmtRepetition++){
                     listeNoeud =    GenererCoalecensceNnoeud2(nbFeuille,nbNoeud,listeNoeud );  
                     MaxTemp = 0;
                     /*On recupere le max*/
                     for(cmtNoeud=0; cmtNoeud<nbNoeud; cmtNoeud++){

                             MaxTemp=MAX(MaxTemp,listeNoeud[cmtNoeud] ); 
                     }
                     MoyenneMaxObs+=MaxTemp;
                          
       }
       MoyenneMaxObs/=(double)nbRepetition;
       nbFeuilleMoyen = 2*MoyenneMaxObs - MaxTheo;
       free_tab_int(listeNoeud);
       return nbFeuilleMoyen;
}
double MeanNBNoeudMoyenCoalescence(int nbNoeud, int nbMultifurcation, int nbRepetition){
       int cmtRepetition, cmtNoeud, *listeNoeud = i_allocate(nbNoeud+nbMultifurcation), MaxTemp;
       double MoyenneMaxObs=0.0, MaxTheo=nbNoeud;
       double nbNoeudMoyen;
       int SommeNoeud;
       if(nbNoeud+1<nbMultifurcation)return -1.0;
       for(cmtRepetition=0; cmtRepetition<nbRepetition; cmtRepetition++){
                     listeNoeud =    GenererCoalecensceNnoeudNbNoeud(nbNoeud+nbMultifurcation,nbMultifurcation,listeNoeud );  
                     MaxTemp = 0;
                     /*On recupere le max*/
                     SommeNoeud = 0;
                     for(cmtNoeud=0; cmtNoeud<nbMultifurcation; cmtNoeud++){
                             MaxTemp=MAX(MaxTemp,listeNoeud[cmtNoeud] );    
                             SommeNoeud+=  listeNoeud[cmtNoeud];
                     }
                      if(SommeNoeud!=nbNoeud) erreur("MeanNBNoeudMoyenCoalescence SommeNoeud!=nbNoeud");                       

                     MoyenneMaxObs+=MaxTemp;
       }
       MoyenneMaxObs/=(double)nbRepetition;
       nbNoeudMoyen = 2*MoyenneMaxObs - MaxTheo;
       free_tab_int(listeNoeud);
       return nbNoeudMoyen;
}
/*Permet de GenererUn arbre de Coalescence*/
Arbre* GenererArbreCoalescenceBinaire(int nbFeuilleInitiale){
       Arbre* arbre = NewArbre();
       /*Tableau contenant les Noeuds a coalescer*/
       Noeud* TabNoeud[nbFeuilleInitiale];
       Noeud* noeud=NULL;
       double TempsCoalescence[nbFeuilleInitiale+1];
       double TMRCA;
       int cmtFeuille, cmtNoeud, position;
       int nbFeuille = nbFeuilleInitiale;
       int nbCoalescence = nbFeuille+1, numCoalescence;
       /*On initialise le tableau avec les feuilles a coalescer*/
       for(cmtFeuille=0;cmtFeuille<nbFeuille; cmtFeuille++){
              TabNoeud[cmtFeuille] = NewNoeud();   
              TabNoeud[cmtFeuille]->numero =   cmtFeuille;
              AjouterFeuille(arbre, TabNoeud[cmtFeuille]);                                                                       
       }
       
       /*On tire les temps de coalescence */
        for(cmtNoeud=0;cmtNoeud<nbFeuille; cmtNoeud++){
                 numCoalescence = nbCoalescence-cmtNoeud;
                 TempsCoalescence[cmtNoeud] = aleatoireExpo((double)numCoalescence*((double)numCoalescence-1)/(4.0));                         
        }
       cmtNoeud=0;
       TMRCA = 0.0;
       nbFeuille = nbFeuilleInitiale;
       while(nbFeuille>1){            
           TMRCA+=TempsCoalescence[cmtNoeud];
          /*Nouvelle coalescence*/
            noeud = NewNoeud();
            /*On ajoute le noeud a l'arbre*/
            AjouterNoeud(arbre, noeud);
            /*On choisit une premiere position*/
            position = (int)(aleatoire()*nbFeuille);
            if(TabNoeud[position]==NULL)erreur("GenererArbreCoalescenceBinaire TabNoeud[position]== NULL 1 ");
            /*Si il s'agit d'une feuille alors la hauteur du noeud est le tmrca*/
            if(TabNoeud[position]->fils_1==NULL){
                                                 TabNoeud[position]->hauteur = TMRCA;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }else{
                                                 TabNoeud[position]->hauteur = TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }
            AjouterNoeudPere(noeud, TabNoeud[position], 1);
            /*On change la position choisit par la derniere position*/
            TabNoeud[position]= TabNoeud[nbFeuille-1];
            TabNoeud[nbFeuille-1]=NULL;
            /*On tire une seconde position*/
             nbFeuille--;
             position = (int)(aleatoire()*nbFeuille);
             if(TabNoeud[position]==NULL)erreur("GenererArbreCoalescenceBinaire TabNoeud[position]== NULL 2 ");
             /*Si il s'agit d'une feuille alors la hauteur du noeud est le tmrca*/
            if(TabNoeud[position]->fils_1==NULL){
                                                 TabNoeud[position]->hauteur = TMRCA;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }else{
                                                 TabNoeud[position]->hauteur = TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }
             AjouterNoeudPere(noeud, TabNoeud[position], 2);
             /*On remplace cette position par le nouveau noeud*/
             TabNoeud[position]=noeud;
             cmtNoeud++;
       }
       if(TabNoeud[1]!=NULL ||TabNoeud[0]==NULL)erreur("GenererArbreCoalescenceBinaire : TabNoeud[1]!=NULL ||TabNoeud[0]==NULL");
       if(noeud!=NULL)arbre->sommet = noeud;
       else erreur("GenererArbreCoalescenceBinaire : noeud==NULL");
       return arbre;
}
int GetPosition(Noeud** TabNoeud,int nbNoeud, int nbFeuille, double alphaDesequilibre){
    double Probabilite[nbNoeud],sommeProb=0.0;
    int cmtNoeud;
    for(cmtNoeud=0; cmtNoeud<nbNoeud; cmtNoeud++){
                    Probabilite[cmtNoeud]=pow((double)TabNoeud[cmtNoeud]->nbFeuille, alphaDesequilibre);
                    sommeProb+= Probabilite[cmtNoeud];
    }
    Probabilite[0]=Probabilite[0]/sommeProb;
    for(cmtNoeud=1; cmtNoeud<nbNoeud; cmtNoeud++){
                    Probabilite[cmtNoeud]=((Probabilite[cmtNoeud]/sommeProb)+Probabilite[cmtNoeud-1]);

    }
    return(recherche_dicho(Probabilite, aleatoire(), 0, nbNoeud));
}

/*Permet de GenererUn arbre de Coalescence*/
Arbre* GenererArbreCoalescenceBinaireDesequilibre(int nbFeuilleInitiale, double alphaDesequilibre, int nbNoeudNull){
       Arbre* arbre = NewArbre();
       /*Tableau contenant les Noeuds a coalescer*/
       Noeud* TabNoeud[nbFeuilleInitiale];
       Noeud* noeud=NULL;
       double TempsCoalescence[nbFeuilleInitiale+1];
       double TMRCA;
       double PropNoeudNull = nbNoeudNull/(double)nbFeuilleInitiale;
       int cmtFeuille, cmtNoeud, position;
       int nbFeuille = nbFeuilleInitiale;
       int nbCoalescence = nbFeuille+1, numCoalescence;
       /*On initialise le tableau avec les feuilles a coalescer*/
       for(cmtFeuille=0;cmtFeuille<nbFeuille; cmtFeuille++){
              TabNoeud[cmtFeuille] = NewNoeud();   
              TabNoeud[cmtFeuille]->numero =   cmtFeuille;
              AjouterFeuille(arbre, TabNoeud[cmtFeuille]);  
              TabNoeud[cmtFeuille]->nbFeuille = 1;                                                                
       }
       /*On tire les temps de coalescence */
        for(cmtNoeud=0;cmtNoeud<nbFeuille; cmtNoeud++){
                 numCoalescence = nbCoalescence-cmtNoeud;
                 TempsCoalescence[cmtNoeud] = aleatoireExpo((double)numCoalescence*((double)numCoalescence-1)/(4.0));
        }
       cmtNoeud=0;
       TMRCA = 0.0;
       nbFeuille = nbFeuilleInitiale;
       while(nbFeuille>1){            
           TMRCA+=TempsCoalescence[cmtNoeud];
          /*Nouvelle coalescence*/
            noeud = NewNoeud();
            /*On ajoute le noeud a l'arbre*/
            AjouterNoeud(arbre, noeud);
            /*On choisit une premiere position*/
            position = GetPosition(TabNoeud,nbFeuille,nbFeuilleInitiale ,  -alphaDesequilibre);
            if(TabNoeud[position]==NULL)erreur("GenererArbreCoalescenceBinaire TabNoeud[position]== NULL 1 ");
            /*Si il s'agit d'une feuille alors la hauteur du noeud est le tmrca*/
            if(TabNoeud[position]->fils_1==NULL){
                                                 TabNoeud[position]->hauteur = TMRCA;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }else{
                                                 
                                                 if(PropNoeudNull<aleatoire()){
                                                                    TabNoeud[position]->hauteur = TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                                    TabNoeud[position]->hauteurTotal = TMRCA;
                                                 }else{
                                                      TabNoeud[position]->hauteur = 0;
                                                      TabNoeud[position]->hauteurTotal = TMRCA;
                                                      TabNoeud[position]->fils_1->hauteur+=TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                      TabNoeud[position]->fils_2->hauteur+=TMRCA - TabNoeud[position]->fils_2->hauteurTotal;                   
                                                      
                                                 } 
            }
            AjouterNoeudPere(noeud, TabNoeud[position], 1);
            /*On change la position choisit par la derniere position*/
            TabNoeud[position]= TabNoeud[nbFeuille-1];
            TabNoeud[nbFeuille-1]=NULL;
            /*On tire une seconde position*/
            nbFeuille--;
            /*position = *//*GetPosition(TabNoeud,nbFeuille,nbFeuilleInitiale ,  alphaDesequilibre);*/
            position =  GetPosition(TabNoeud,nbFeuille,nbFeuilleInitiale ,  alphaDesequilibre);
            if(TabNoeud[position]==NULL)erreur("GenererArbreCoalescenceBinaire TabNoeud[position]== NULL 2 ");
             /*Si il s'agit d'une feuille alors la hauteur du noeud est le tmrca*/
            if(TabNoeud[position]->fils_1==NULL){
                                                 TabNoeud[position]->hauteur = TMRCA;
                                                 TabNoeud[position]->hauteurTotal = TMRCA;
            }else{
                                                 if(PropNoeudNull<aleatoire()){
                                                                    TabNoeud[position]->hauteur = TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                                    TabNoeud[position]->hauteurTotal = TMRCA;
                                                 }else{
                                                      TabNoeud[position]->hauteur = 0;
                                                      TabNoeud[position]->hauteurTotal = TMRCA;
                                                      TabNoeud[position]->fils_1->hauteur+=TMRCA - TabNoeud[position]->fils_1->hauteurTotal;
                                                      TabNoeud[position]->fils_2->hauteur+=TMRCA - TabNoeud[position]->fils_2->hauteurTotal;                   
                                                      
                                                 }     
            }
             AjouterNoeudPere(noeud, TabNoeud[position], 2);
             /*On remplace cette position par le nouveau noeud*/
             TabNoeud[position]=noeud;
             cmtNoeud++;
             noeud->nbFeuille = noeud->fils_1->nbFeuille+noeud->fils_2->nbFeuille;
       }
       if(TabNoeud[1]!=NULL || TabNoeud[0]==NULL)erreur("GenererArbreCoalescenceBinaire : TabNoeud[1]!=NULL ||TabNoeud[0]==NULL");
       if(noeud!=NULL)arbre->sommet = noeud;
       else erreur("GenererArbreCoalescenceBinaire : noeud==NULL");
       return arbre;
}
