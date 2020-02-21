#include "./jt_arbre.h"
Noeud* LireNoeud(char** ch, Arbre* arbre);
Noeud* LireMultiNoeud(char** ch, Arbre* arbre);
double CalTMRCANoeudOld(Noeud* noeud){
     double TMRCA=0, TMRCATemp=0, nbNoeud = 0;  
     if(noeud->hauteur!=-1)TMRCA=noeud->hauteur;
     #ifdef MULTINOEUD
     Noeud* ParcFils=noeud->ListeFils;
     while(ParcFils!=NULL){
          TMRCATemp+=CalTMRCANoeudOld(ParcFils);
          ParcFils = ParcFils->FrereSuiv;
          nbNoeud++;
     }
     #else
     if(noeud->fils_1!=NULL){
                             TMRCATemp+=CalTMRCANoeudOld(noeud->fils_1);
                             nbNoeud++;
     }
     if(noeud->fils_2!=NULL){
                             TMRCATemp+=CalTMRCANoeudOld(noeud->fils_2);
                             nbNoeud++;
     }
     #endif      
     if(nbNoeud>0)TMRCATemp/=nbNoeud;
     TMRCA+=TMRCATemp;
     return TMRCA;
}

double CalcTMRCAArbreOld(Arbre* arbre){
       return CalTMRCANoeudOld(arbre->sommet);
}

/*Permet de calculer le TMRCA de l'ARbre*/
double CalcTMRCAArbre(Arbre* arbre){
       Noeud* feuille, *noeud;
       double TMRCA;
       int nbFeuille = 0;    
       feuille = arbre->feuilles;
       /*Pour calculer le TMRCA on fait la moyenne entre chacune des feuilles et le MRCA*/
       TMRCA = 0.0;
       while(feuille!=NULL){
             noeud = feuille;
             while(noeud!=NULL){  
                   if(noeud->hauteur>0)TMRCA+= noeud->hauteur;                                   
                   noeud = noeud->pere;
             }
             feuille =feuille->suiv;
             nbFeuille++;
       }  
       TMRCA/=nbFeuille;
       return TMRCA;
}

void freeNoeud(Noeud* noeud){
     if(noeud->nom!=NULL)(noeud->nom)->Free(noeud->nom);
     free(noeud);
     #ifdef TESTMEMOIRE
     jt_mem->noeud--;
     #endif
}
void freelisteNoeud(Noeud* noeud){
     Noeud* parcourir = noeud;
     while(noeud!=NULL){
               parcourir = noeud->suiv;
               freeNoeud(noeud);
               noeud = parcourir;        
     }
     
}
void freeArbre(Arbre* arbre){
     if(arbre==NULL)return;
     freelisteNoeud(arbre->noeuds);
     freelisteNoeud(arbre->feuilles);
     if(arbre->longeur_branche_cumule!=NULL)free_tab_double(arbre->longeur_branche_cumule);
     free(arbre);
     #ifdef TESTMEMOIRE
     jt_mem->arbre--;
     #endif
}
void NormaliserLongeurListeArbre(Arbre* arbre, int longeur_total){     
     Arbre* parc_arbre=arbre;
     parc_arbre->partition_normalise = 0;
     while(parc_arbre!=NULL){
                             parc_arbre->partition_normalise=parc_arbre->partition/longeur_total;                        
                             parc_arbre = parc_arbre->suiv;
     }
}

void freelisteArbre(Arbre* arbre){
     Arbre* parcourir =arbre;
     while(arbre!=NULL){
              parcourir = arbre->suiv;         
              freeArbre(arbre);                             
              arbre = parcourir;          
     }     
     
}


boolean isFeuille(Noeud* noeud){
        if(noeud->nom!=NULL && noeud->fils_1==NULL)return TRUE;
        else return FALSE;
        
}



/*pour recuperer l'arbre*/
char* ProchChar(char* ch)
{
	ch++;
	while (*ch!='\0' && isspace(*ch)) ch++;
	return ch;
}

Noeud* recuperer_noeud(int position,Arbre* arbre){
       int cmt=0;
       Noeud* parcourir = arbre->noeuds;
       #ifdef ERREUR
       if(position>=arbre->nb_noeuds)erreur("position>=arbre->nb_noeuds %d %d", arbre->nb_noeuds, position);
       #endif
       while(cmt<position){
                           parcourir = parcourir->suiv;
                           cmt++;
       }
       return parcourir;
       
}

double* GetTabBranche(Arbre* arbre){
      int nb_branches=arbre->nb_noeuds*2,cmt=0;
      Noeud* parc_noeud = arbre->noeuds;  
      double * longeur = d_allocate(nb_branches);
      while(parc_noeud!=NULL){
           longeur[cmt]=parc_noeud->longeur_fils_1;
           cmt++;
           longeur[cmt]=parc_noeud->longeur_fils_2;
           cmt++;
           parc_noeud =parc_noeud->suiv;
       }
       return longeur;
}

void init_longeur_de_branches_cumulee(Arbre* arbre){
        int nb_branches=arbre->nb_noeuds*2,cmt=0;
        double* longeur = d_allocate(nb_branches), longeur_totale=0.0;
        Noeud* parc_noeud = arbre->noeuds;
       cmt=0;
        while(parc_noeud!=NULL){
                #ifdef ERREUR
                if(cmt>=nb_branches)erreur("init_longeur_de_branches_cumulee cmt>=nb_branches");
                #endif                
                longeur_totale+=parc_noeud->longeur_fils_1;
                longeur[cmt] =  longeur_totale;
                cmt++;
                longeur_totale+=parc_noeud->longeur_fils_2;
                longeur[cmt] =longeur_totale;
                cmt++;
                parc_noeud =parc_noeud->suiv;
        }
        #ifdef ERREUR
        if(cmt<nb_branches)erreur("init_longeur_de_branches_cumulee: cmt<nb_branches cmt %d nb_branches %d",cmt,nb_branches); 
        #endif
        arbre->longeur_branche_cumule = longeur;
        
}       

char* LireJusqua(char *ch, char stopChar, char *message)
{	
	while (*ch!='\0' && *ch!=stopChar && *ch!='(' && *ch!=',' && *ch!=':' && *ch!=')' && *ch!=';'){
          ch++;
    
    }
    if (*ch=='\0' || *ch!=stopChar) {
        while(*ch!='\0'){
             printf("%c", *ch);
             ch++;            
        }          
		erreur("pas de %c pour %s",stopChar,message );
	}
	return ch;
}

void AjouterFeuille(Arbre* arbre, Noeud* feuille){
     if( arbre->feuilles!=NULL)arbre->feuilles->prec = feuille;
     feuille->suiv =  arbre->feuilles;
     arbre->feuilles = feuille;
     arbre->nb_feuilles++;
}
void AjouterNoeud(Arbre* arbre, Noeud* noeud){
     if(arbre->noeuds!=NULL)arbre->noeuds->prec = noeud;
     noeud->suiv =  arbre->noeuds;
     arbre->noeuds = noeud;
     arbre->nb_noeuds++;   
}

Noeud* NewNoeud(){
       Noeud* noeud = (Noeud*)calloc(1, sizeof(Noeud));
       if(noeud==NULL)erreur_allocation("NewNoeud");
       noeud->nom = NULL;
       noeud->numero = -1;
       noeud->suiv = NULL;
       noeud->hauteur = -1;
       noeud->fils_1 = NULL;
       noeud->fils_2 = NULL;
       noeud->longeur_fils_1 = -1;
       noeud->longeur_fils_2 = -1;
       noeud->pere = NULL;
       noeud->nbFeuille =0;
       noeud->prec = NULL;
       noeud->nbNoeud=0;
       noeud->nbEmbranchement = 0;
       noeud->hauteurTotal = 0;
       noeud->Balise = TRUE;
       noeud->EstNull = FALSE;
       #ifdef MULTINOEUD
       noeud->ListeFils=NULL;
       noeud->FrereSuiv=NULL;
       #endif
       #ifdef TESTMEMOIRE
       jt_mem->noeud++;
       #endif
       return noeud;
}

Arbre* NewArbre(){
       Arbre* arbre = (Arbre*)calloc(1, sizeof(Arbre));
       if(arbre==NULL)erreur_allocation("NewArbre");
       arbre->sommet =NULL;
       arbre->partition = -1;
       arbre->tx_mutation =-1.0;
       arbre->nb_feuilles =0;
       arbre->nb_noeuds = 0;
       arbre->noeuds = NULL;
       arbre->feuilles =NULL;
       arbre->longeur=0;
       arbre->suiv = NULL;
       arbre->longeur_branche_cumule = NULL;
       arbre->longeurInterne = 0;
       arbre->longeurExterne = 0;
       arbre->nbSnp = -1;
       arbre->nbVraiNoeuds = 0;
       arbre->nbVraiBranches= 0;
       #ifdef TESTMEMOIRE
       jt_mem->arbre++;
       #endif
       return arbre;
}

double AjouterHauteurTotalNoeud(Noeud* noeud){
     double hauteur=0;
     #ifdef MULTINOEUD
     Noeud* enfant;
     int nbNoeud = 0;
     #endif
     if(noeud==NULL)return 0;
     #ifdef MULTINOEUD
     enfant = noeud->ListeFils;
     while(enfant!=NULL){
           hauteur +=AjouterHauteurTotalNoeud(enfant);  
           nbNoeud++;
           enfant = enfant->FrereSuiv;    
               
     }
     if(noeud->nbEmbranchement!=nbNoeud)erreur("noeud->nbEmbranchement!=nbNoeud)");
     #else
     hauteur = AjouterHauteurTotalNoeud(noeud->fils_1);
     hauteur += AjouterHauteurTotalNoeud(noeud->fils_2);
     #endif
     if(hauteur>0){
          noeud->hauteurTotal = hauteur;
          noeud->hauteurTotal/=noeud->nbEmbranchement;
     }else noeud->hauteurTotal =0;

     return noeud->hauteurTotal+noeud->hauteur;
}
void AjouterHauteurTotalNoeudArbre(Arbre* arbre){
     AjouterHauteurTotalNoeud(arbre->sommet); 
}
/*permet de lire une feuille et de recuperer les parametre*/
Noeud* lireFeuille(char**ch , Arbre* arbre){
       Noeud* noeud = NewNoeud(); 
       char nom[ARBRE_MAX_NAME_LEN];
       int cmt= 0;
       /*on recopie le nom*/
      while ( **ch!='\0' && **ch!=':' && **ch!=',' && **ch!=')' && cmt<ARBRE_MAX_NAME_LEN) {
             if(**ch!=' '){
                        nom[cmt] = **ch;
                        cmt++;
                        
             }
             (*ch)++;
       }
       nom[cmt]='\0';
       

       noeud->nom = String_Create(nom);
       /*notre numero*/
       noeud->numero = arbre->nb_feuilles;
/*       noeud->numero = atoi(nom);
  */     AjouterFeuille(arbre, noeud);
       /*on revient au caractere precedent*/
       (*ch)--;
       return noeud;
}
Noeud* LireBranche(char**ch , Arbre* arbre){
      Noeud* noeud;
     /*on recupere le prochain caractere*/
     *ch = ProchChar(*ch);
     /*si il s'agit d'une parenthes on est dans un noeud*/
     if(**ch=='('){
                #ifdef MULTINOEUD
                noeud =  LireMultiNoeud(ch, arbre);
                #else   
                noeud =  LireNoeud(ch, arbre);
                #endif
                /*on recupere la fin du noeud et on verifie que ca se finit bien par une parenthes fermante*/
                *ch = LireJusqua(*ch, ')', "noeud non ferme");
     }
     /*sinon on est dans une feuille*/
     else {
          noeud=lireFeuille(ch, arbre);
     }
     
     *ch=(ProchChar(*ch));
     /*on recupere la hauteur associe a la branche*/
     if (**ch==':') {
                    (*ch)++;
                    if (sscanf(*ch, "%lf", &(noeud->hauteur))!=1) {  
                            erreur("impossible de recuperer la hauteur du noeud");
                    }
                    /*if(LONGEURBRANCHENULLE(noeud->hauteur))noeud->hauteur=0;
                    */
                    while ( **ch!='\0' && **ch!=':' && **ch!=',' && **ch!=')')(*ch)++;     
                    (*ch)--;
                    arbre->longeur+=noeud->hauteur;
                    if(isFeuille(noeud))arbre->longeurExterne+=noeud->hauteur;
                    else {
                        arbre->longeurInterne+=noeud->hauteur;
                       
                    }
     }else {(*ch)--;}
     /*on passe tous les caractere jusqu'au prochain element*/
     return noeud;
}
void AjouterNoeudPere(Noeud* pere, Noeud* fils, int position){
     #ifdef MULTINOEUD
     fils->FrereSuiv = pere->ListeFils;
     pere->ListeFils = fils;
     pere->nbEmbranchement++;
     fils->pere = pere;
     #else
     if(position==1){
                     pere->fils_1 = fils;
                     pere->longeur_fils_1 = fils->hauteur;
     }else{
                     pere->fils_2 = fils;
                     pere->longeur_fils_2 = fils->hauteur;      
     }
     #endif
     fils->pere = pere;
}
#ifdef MULTINOEUD
int recupererhauteur(Noeud* noeud, int  *ClassementNoeud, int* HauteurNoeud, int numClassement, int Hauteur){
         Noeud* fils=noeud->ListeFils;
         if(noeud->nbEmbranchement==0)return numClassement;
         HauteurNoeud[numClassement]=Hauteur;
         ClassementNoeud[numClassement]=noeud->nbEmbranchement;
         while(fils!=NULL){
                           if(fils->nbEmbranchement>0){
                                                       numClassement++;
                                                       numClassement = recupererhauteur(fils, ClassementNoeud, HauteurNoeud, numClassement, Hauteur+1);
                                                         
                           }    
                           fils = fils->FrereSuiv;           
         }
         return numClassement;
}

int recupererHauteurEtLongeur(Noeud* noeud, int  *ClassementNoeud, int* HauteurNoeud,double* Longeur, int numClassement, int Hauteur){
         Noeud* fils=noeud->ListeFils;
         if(noeud->nbEmbranchement==0)return numClassement;
         HauteurNoeud[numClassement]=Hauteur;
         ClassementNoeud[numClassement]=noeud->nbEmbranchement;
         Longeur[numClassement]=noeud->hauteur;
         while(fils!=NULL){
                           if(fils->nbEmbranchement>0){
                                                       numClassement++;
                                                       numClassement = recupererhauteur(fils, ClassementNoeud, HauteurNoeud, numClassement, Hauteur+1);
                                                         
                           }    
                           fils = fils->FrereSuiv;           
         }
         return numClassement;
}

int* recuperernbEmbranchementNoeud(Arbre* arbre){
    int ClassementNoeudtemp[arbre->nb_noeuds], *ClassementNoeud=i_allocate(arbre->nb_noeuds+1), cmt ;
    int HauteurNoeudtemp[arbre->nb_noeuds], temphauteur, position, cmt2;

    for(cmt2=0; cmt2<arbre->nb_noeuds; cmt2++)ClassementNoeudtemp[cmt2]=-1;
    recupererhauteur(arbre->sommet, ClassementNoeudtemp, HauteurNoeudtemp,0,  0);
    for(cmt2=0; cmt2<arbre->nb_noeuds; cmt2++)if(ClassementNoeudtemp[cmt2]==-1)erreur("recuperernbEmbranchementNoeud");
    /*on classe le tableau*/
    for(cmt=0; cmt<arbre->nb_noeuds; cmt++){
           temphauteur = HauteurNoeudtemp[cmt];
           position = cmt;
           for(cmt2=cmt+1; cmt2<arbre->nb_noeuds; cmt2++){
                             if(temphauteur<HauteurNoeudtemp[cmt2]){
                                            position=cmt2;
                                            temphauteur = HauteurNoeudtemp[cmt2];                   
                             }  
               }

               HauteurNoeudtemp[position]=HauteurNoeudtemp[cmt];
               ClassementNoeud[cmt] = ClassementNoeudtemp[position];
               ClassementNoeudtemp[position] = ClassementNoeudtemp[cmt];
    }
    return ClassementNoeud;
}
void recuperernbEmbranchementNoeud2(Arbre* arbre){
    int ClassementNoeudtemp[arbre->nb_noeuds], cmt;
    int HauteurNoeudtemp[arbre->nb_noeuds], temphauteur, position, cmt2, *HauteurNoeud=i_allocate(arbre->nb_noeuds);
    int nbHauteur=1, *NbNoeudHauteur;    
    double Hauteurtemp[arbre->nb_noeuds];
    for(cmt2=0; cmt2<arbre->nb_noeuds; cmt2++)ClassementNoeudtemp[cmt2]=-1;
    recupererHauteurEtLongeur(arbre->sommet, ClassementNoeudtemp, HauteurNoeudtemp,Hauteurtemp, 0,  0);
    for(cmt2=0; cmt2<arbre->nb_noeuds; cmt2++)if(ClassementNoeudtemp[cmt2]==-1)erreur("recuperernbEmbranchementNoeud");
    /*on classe le tableau*/
    for(cmt=0; cmt<arbre->nb_noeuds; cmt++){
           temphauteur = HauteurNoeudtemp[cmt];
           position = cmt;
           for(cmt2=cmt+1; cmt2<arbre->nb_noeuds; cmt2++){
                             if(temphauteur<HauteurNoeudtemp[cmt2]){
                                            position=cmt2;
                                            temphauteur = HauteurNoeudtemp[cmt2];                   
                             }  
               }
               HauteurNoeud[cmt]=temphauteur;
               if(cmt>0 &&  HauteurNoeud[cmt]!=HauteurNoeud[cmt-1])nbHauteur++;
               HauteurNoeudtemp[position]=HauteurNoeudtemp[cmt];
    }
    NbNoeudHauteur = i_allocate(nbHauteur);
    
}

#endif
/*permet de lire un noeud a partir d'un pointeur sur le caractere*/
Noeud* LireMultiNoeud(char** ch, Arbre* arbre){
       Noeud *pere = NewNoeud(), *fils;
       /*on lit la premiere branche*/
       while(**ch!=')'){
              fils = LireBranche(ch, arbre);
              #ifdef MULTINOEUD
              AjouterNoeudPere(pere, fils, -1);
              #endif
              fils->pere  = pere;
              *ch=(ProchChar(*ch));
       }
       pere->numero = arbre->nb_noeuds;
       AjouterNoeud(arbre, pere);
       return pere;
}

void RecupererNbVraiNoeud(Arbre* arbre){
    Noeud* noeud =arbre->noeuds;
    int nbNoeud = 0;
    arbre->nbVraiBranches = 0;
    while(noeud!=NULL){
        if(!noeud->EstNull)nbNoeud++; 
        if(!noeud->fils_1->EstNull)arbre->nbVraiBranches++;
        if(!noeud->fils_2->EstNull)arbre->nbVraiBranches++;
        noeud = noeud->suiv;                                 
    }
    arbre->nbVraiNoeuds = nbNoeud;
       
}
/*Permet de recalibrer un arbre en fonction d'une limite tout noeud qui a une hauteur inferieu a limite est considerer comme null*/
void RecalibrerHauteurArbre(Arbre* arbre, double Limite){
     Noeud* noeud = arbre->noeuds;
     while(noeud!=NULL){
                        if(LONGEURBRANCHENULLE(noeud->hauteur, Limite) ){
                             noeud->hauteur = 0;
                             noeud->EstNull = TRUE; 
                        }else noeud->EstNull = FALSE; 
                        noeud = noeud->suiv;
     }  
     noeud = arbre->feuilles;
     while(noeud!=NULL){
                        if(LONGEURBRANCHENULLE(noeud->hauteur, Limite) ){
                             noeud->hauteur = 0;
                             noeud->EstNull = TRUE; 
                        }else noeud->EstNull = FALSE; 
                        noeud = noeud->suiv;
     }  
     
}

/*permet de lire un noeud a partir d'un pointeur sur le caractere*/
Noeud* LireNoeud(char** ch, Arbre* arbre){
       Noeud *pere = NewNoeud(), *fils;
       /*on lit la premiere branche*/
       fils = LireBranche(ch, arbre);
       pere->fils_1 = fils;
       pere->longeur_fils_1 = fils->hauteur;
       fils->pere  = pere;
       *ch=(ProchChar(*ch));
       /*on recupere la longeur de l'arbre*/
       *ch = LireJusqua(*ch, ',', "LireNoeud");
       fils = LireBranche(ch, arbre);
       pere->fils_2 = fils;
       fils->pere  = pere;
       pere->longeur_fils_2 = fils->hauteur;
       pere->numero = arbre->nb_noeuds;
       AjouterNoeud(arbre, pere);
       pere->nbEmbranchement = 2;
       return pere;
}

/*lecture d'un arbre sous forme de*/
Arbre* Lire_arbre_String(String* str_arbre){
     char* ch = &(str_arbre->chaine[0]);
     Arbre* arbre;
     int  longeur;
     /*tant qu'on est pas arrive a un caractere*/
     while (*ch!='\0' && *ch!='(' && *ch!='[')ch++;
     if(*ch=='\0')return NULL;
     arbre = NewArbre();
     /*cas ou l'arbre est constitue de plusieurs locus*/
     if(*ch=='['){
                  /*on va a l'element suivant*/
                  ch++;
                  /*on recupere la portion d'adn de l'arbre*/
                  if (sscanf(ch, "%d", &(longeur))!=1) {
			         erreur("impossible de lire la longeur de la partition de l'arbre");
                  }
                  arbre->partition= (double)longeur;
		       /*on va jusqu'a l'element suivant de l'arbre*/
		        while (*ch!='\0' && *ch!='(' && *ch!=',')ch++;
		        /*si il s'agit d'une virgule il existe un taux de mutation different pour la partition*/
		        if(*ch==','){
                             ch++;
                             if (sscanf(ch, "%lf", &(arbre->tx_mutation))!=1){
                                            erreur("taux de mutation impossible a lire");               
                             }
                             /*on va jusqu'au caractere suivant*/
			                 while (*ch!='\0' && *ch!='(') ch++;
               }
               

     }
     if (*ch!='(') {
        erreur("arbre impossible a lire");
     }	/*on lit le noeud*/
     #ifdef MULTINOEUD
     else arbre->sommet=LireMultiNoeud(&ch, arbre);
     #else
     else arbre->sommet=LireNoeud(&ch, arbre);
     #endif
     /*Calcul du TMRCA sur l'ensemble des noeuds positifs*/
     arbre->TMRCA = CalcTMRCAArbre(arbre);
     /*On recalibre le TMRCA pour definir les Noeud dont la hauteur est dite Null est non nulll pour tout noeud qui est 1000 fois plus petit que TMRCA*/
     RecalibrerHauteurArbre(arbre, arbre->TMRCA/5000.0);
     /*On recupere le nouveau TMRCA*/
     arbre->TMRCA = CalcTMRCAArbre(arbre);
     RecupererNbVraiNoeud(arbre);
     /*Pour le noeud sommet */
     AjouterHauteurTotalNoeudArbre(arbre);
     return arbre;
}
/*Ecrit un arbre Binaire*/
void ecrireNoeudArbre(FILE* ecrire, Noeud* noeud){
          #ifdef MULTINOEUD
          erreur("ecrireNoeudArbre ne traite pas les arbres a multinoeuds");
          #endif
          double Hauteur;
          if(noeud->fils_1==NULL && noeud->fils_2!=NULL )erreur("ecrireNoeudArbre");
          if(noeud->fils_2==NULL && noeud->fils_1!=NULL )erreur("ecrireNoeudArbre");
          if(noeud->fils_1==NULL){
                                 Hauteur = noeud->hauteur;
                                 if(noeud->EstNull)Hauteur=0; 
                                 if(noeud->nom!=NULL)fprintf(ecrire,"%s:%g" ,noeud->nom->chaine, Hauteur);
                                 else fprintf(ecrire,"%d:%g" ,noeud->numero, Hauteur);
                                 return;
         }
         fprintf(ecrire,"(" );
         ecrireNoeudArbre(ecrire, noeud->fils_1);
         fprintf(ecrire,"," );
         ecrireNoeudArbre(ecrire, noeud->fils_2);
         Hauteur = noeud->hauteur;
         if(noeud->EstNull)Hauteur=0; 
         if(noeud->pere!=NULL)fprintf(ecrire,"):%g", Hauteur);
         else fprintf(ecrire,");\n");
}

void ecrireArbre(FILE* ecrire, Arbre* arbre){
     ecrireNoeudArbre( ecrire,arbre->sommet);
}

void ecrireArbreSansOutPut(FILE* ecrire, Arbre* arbre, String* NomOutPut){
     if(arbre->sommet->fils_1->nom->Comparer(arbre->sommet->fils_1->nom,NomOutPut))ecrireNoeudArbre( ecrire,arbre->sommet->fils_2);
     else if(arbre->sommet->fils_2->nom->Comparer(arbre->sommet->fils_2->nom,NomOutPut))ecrireNoeudArbre( ecrire,arbre->sommet->fils_2);
     else erreur("erreur dans le programme : ecrireArbreSansOutPut");
}
/*Permet d'ajouter le nombre de feuille a l'arbre*/
void AjouterNbFeuille(Arbre* arbre){
     Noeud* parFeuille, * parNoeud;
     parNoeud =arbre->noeuds;
     while(parNoeud!=NULL){
            parNoeud->nbFeuille = 0;               
            parNoeud =parNoeud->suiv;                                       
     }    
     parFeuille = arbre->feuilles;
     while(parFeuille!=NULL){
          parNoeud = parFeuille->pere;
          while(parNoeud!=NULL){
               parNoeud->nbFeuille++;                
               parNoeud = parNoeud->pere;                                      
          }                   
           parFeuille = parFeuille->suiv;                 
     }
     
}
/*Ajoute a l'arbre le nombre de vrai Noeud*/
int GetNbVraiSommet(Noeud* noeud){
    if(isFeuille(noeud))return 0;
    noeud->nbNoeudVrai = GetNbVraiSommet(noeud->fils_1);
    noeud->nbNoeudVrai += GetNbVraiSommet(noeud->fils_2);
    if(!noeud->EstNull)noeud->nbNoeudVrai++;
    return noeud->nbNoeudVrai;
}
/*permet de copier un noeud recursivement
arbre : Nouveau arbre cree
NewNoeudPere : Nouveau noeud pere cree
noeud : Ancien noeud

*/
Noeud* CopierNoeud(Arbre* arbre,Noeud* NewNoeudPere ,Noeud* noeud){
       Noeud* NouveauNoeud = NewNoeud();
       NouveauNoeud->Balise =noeud->Balise;
       NouveauNoeud->EstNull =  noeud->EstNull;
       NouveauNoeud->hauteur = noeud->hauteur;
       NouveauNoeud->hauteurTotal =  noeud->hauteurTotal;
       NouveauNoeud->longeur_fils_1 =  noeud->longeur_fils_1;
       NouveauNoeud->longeur_fils_2 = noeud->longeur_fils_2;
       NouveauNoeud->nbEmbranchement = noeud->nbEmbranchement;
       NouveauNoeud->nbFeuille = noeud->nbFeuille;
       NouveauNoeud->nbNoeud = noeud->nbNoeud;
       NouveauNoeud->nbNoeudVrai =  noeud->nbNoeudVrai;
       if(noeud->nom!=NULL) {
          NouveauNoeud->nom=noeud->nom->Dupliquer(noeud->nom);
       }
       NouveauNoeud->pere = NewNoeudPere;
       
       if(isFeuille(noeud)){                      
            AjouterFeuille(arbre, NouveauNoeud);
       }else{
            AjouterNoeud(arbre, NouveauNoeud);
            NouveauNoeud->fils_1 = CopierNoeud(arbre,NouveauNoeud ,noeud->fils_1);
            NouveauNoeud->fils_2 = CopierNoeud(arbre,NouveauNoeud ,noeud->fils_2);
       }
       return NouveauNoeud ;
}
Arbre* CopierArbre(Arbre* arbre){
    Arbre* NouveauArbre =   NewArbre();
    int cmt;
    /*On copier les informations*/
    NouveauArbre->Imn = arbre->Imn;
    NouveauArbre->Iprime = arbre->Iprime;
    NouveauArbre->longeur = arbre->longeur;
    NouveauArbre->longeurExterne = arbre->longeurExterne  ;       
    NouveauArbre->longeurInterne =  arbre->longeurInterne;
    NouveauArbre->nbSnp = arbre->nbSnp;
    NouveauArbre->nbVraiNoeuds =  arbre->nbVraiNoeuds;
    NouveauArbre->partition = arbre->partition;
    NouveauArbre->partition_normalise = arbre->partition_normalise;
    NouveauArbre->TMRCA = arbre->TMRCA;
    NouveauArbre->tx_mutation = arbre->tx_mutation;

    if(NouveauArbre->longeur_branche_cumule!=NULL){
        NouveauArbre->longeur_branche_cumule = d_allocate(NouveauArbre->nb_noeuds*2);
        for(cmt=0; cmt<NouveauArbre->nb_noeuds*2; cmt++ )NouveauArbre->longeur_branche_cumule[cmt] = arbre->longeur_branche_cumule[cmt];
    }        
    NouveauArbre->sommet =CopierNoeud(NouveauArbre,NULL ,arbre->sommet);
    return NouveauArbre;
              
}
/**
Fonction permettant de calculer le nombre d'haplotype d'un arbre 
On définit un haplotype : 
           * Une feuille dont la longeur de branche externe est non nul
           * Un noeud non null dont une des deux branche dessous a que des longeurs null jusqu'à la feuille

*/
int GetnbHaplotype(Arbre* arbre){
    int nbHaplotype=0;
    Noeud* Parcourir;
    
    /*Pour toutes les feuilles */
    Parcourir = arbre->feuilles;
    while(Parcourir!=NULL){
      /*Si la hauteur est superieur a 0 on a un haplotype*/
      if(Parcourir->hauteur > 0)nbHaplotype++;
      Parcourir = Parcourir->suiv;
    }

    
    /*Pour tous les noeuds*/
    Parcourir = arbre->noeuds;
    while(Parcourir!=NULL){
      /*Si le noeud n'est pas null*/
      if(!Parcourir->EstNull){
        /*Cas numero 1 la hauteur est nulle*/                      
        if(Parcourir->hauteurTotal==0)nbHaplotype++;  
        /*Cas numero 2 Une des deux feuilles n'a pas de hauteur*/
        else if((Parcourir->fils_1->fils_1==NULL && Parcourir->fils_1->hauteur==0) || (Parcourir->fils_2->fils_1==NULL && Parcourir->fils_2->hauteur==0)) nbHaplotype++;  
        /*Cas numero 3 : Un de mes deux fils a une hauteur null, sont des noeuds et ont une hauteur total null*/
        else if((Parcourir->fils_1->fils_1!=NULL && Parcourir->fils_1->hauteur==0 && Parcourir->fils_1->hauteurTotal==0) || (Parcourir->fils_2->fils_1!=NULL && Parcourir->fils_2->hauteur==0 && Parcourir->fils_2->hauteurTotal==0) )nbHaplotype++;                 
      }
      Parcourir = Parcourir->suiv;                           
    }
    return nbHaplotype;
}
