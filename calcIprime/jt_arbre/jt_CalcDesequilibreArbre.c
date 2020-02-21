#include "./jt_CalcDesequilibreArbre.h"

double HauteursBranchesDeuxFeuilles(Noeud* feuille1,Noeud* feuille2 ){
     double hauteur=feuille1->hauteur;
     Noeud* parc1=feuille1->pere,*parc2;
     if(feuille1->hauteur<0||feuille2->hauteur<0)erreur("HauteursBranchesDeuxFeuilles");
     boolean balise=TRUE;
     while(balise){
            parc2=feuille2->pere; 
            while(parc2!=NULL && balise){
                  if(parc1==parc2)balise=FALSE;
                  else parc2 = parc2->pere;
            }
            if(balise && parc1->hauteur!=-1){
                      hauteur+=parc1->hauteur;
            }
            parc1 = parc1->pere;
            if(parc1==NULL && balise)erreur("HauteursBranchesDeuxFeuilles Pere non trouve");
     }
     return hauteur;
}

void HauteursBranchesDeuxADeux(Arbre* arbre){
     int cmtIndividu,cmt2Individu;
     Noeud* feuille1, * feuille2;
     double temp;
/*     double** hauteur = tableau_rec_allocate(arbre->nb_feuilles, arbre->nb_feuilles);
  */   feuille1 = arbre->feuilles;
     cmtIndividu = 0;
     printf("%f ", feuille1->hauteur);
     while(feuille1!=NULL){
                           
          feuille2 = feuille1->suiv; 
          cmt2Individu = 0;
          while(feuille2!=NULL){
                             temp = HauteursBranchesDeuxFeuilles(feuille1,feuille2);
                             printf("\n%f\n ",temp );   
                             cmt2Individu++; 
                             feuille2 = feuille2->suiv;
          }
          PAUSE();
          cmtIndividu++;
          feuille1= feuille1->suiv;
     }     
}
