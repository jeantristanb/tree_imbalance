#include "jt_fichier.h"

FILE* Fichier_Open(String* nomfichier,char* mode){
       FILE* fichier =  fopen(nomfichier->chaine, mode);
       if(fichier==NULL)erreur("impossibilite d'ouvrir le fichier %s", nomfichier->chaine );
       return fichier;
}
int  Fichier_nb_ligne(Fichier* fich){
      FILE* lire = Fichier_Open(fich->emplacement, "r");
      int nb_ligne = 0 ;  
      char car;
      while((car =fgetc(lire))!=EOF){
          if(car=='\n')nb_ligne++;
      }
      nb_ligne++;
      fich->nb_lignes =nb_ligne ;
      fclose(lire);
      return nb_ligne;
}

Tab_String* Fichier_lire_ligne(Fichier* fich){
            Tab_String*tab;
            String* ligne;
            FILE* lire;
            char car;
            int nb_caractere, cmt=0,  nb_max_caractere,cmt_max_caractere; 
            int nb_ligne =  Fichier_nb_ligne(fich);
            tab = Tab_String_Create(nb_ligne);
            lire = Fichier_Open(fich->emplacement, "r");
            nb_caractere = 0;
            
            nb_max_caractere = 50000;
            cmt_max_caractere =nb_max_caractere;
            ligne = String_Create_int(nb_max_caractere);
            /*tant que le fichier n'est pas termine*/
            while((car =fgetc(lire))!=EOF){
                     /*on realloue 1000 caractere a la ligne*/
                      if(nb_caractere>=cmt_max_caractere){
                                                         ligne->Reallouer(ligne, cmt_max_caractere+1);
                                                         cmt_max_caractere+=nb_max_caractere;
                      }
                      if(car=='\n'){
                           /*on finalise la ligne*/ 
                          ligne->Set(ligne, '\0',nb_caractere);  
                          ligne->Ajuster_Taille(ligne);
                          tab->Set(tab, ligne, cmt);
                          ligne=String_Create_int(nb_max_caractere);
                          nb_caractere = 0;   
                          cmt_max_caractere=nb_max_caractere;
                          cmt++;   
                          
                      }
                      else{
                            ligne->Set(ligne, car,nb_caractere);
                            nb_caractere++;
                      }

            } 
            ligne->Set(ligne, '\0',nb_caractere);
            ligne->Ajuster_Taille(ligne);
            tab->Set(tab, ligne, cmt);
            fich->nb_lignes = tab->nb_string;
            fclose(lire);
            return tab;
}



boolean Fichier_Recherche(){
/*char *strstr (const char *meule_de_foin, const char *aiguille);*/
 return TRUE;
}
void Fichier_free(Fichier* fich){
          fich->emplacement->Free(fich->emplacement);
          free(fich);
         #ifdef TESTMEMOIRE
        jt_mem->fichier--;
        #endif
     
}

/*Constructeur de fichier*/
Fichier* Fichier_Create(String* emplacement, char type){
        Fichier* fich = (Fichier*)calloc(1, sizeof(Fichier));
        if(fich==NULL)erreur_allocation("Fichier_Create");
        #ifdef TESTMEMOIRE
        jt_mem->fichier++;
        #endif
        fich->emplacement = emplacement->Dupliquer(emplacement);
        fich->type_ouverture = type;
        fich->Free = Fichier_free;
        fich->Nb_Lignes = Fichier_nb_ligne;
        fich->Lire_Ligne = Fichier_lire_ligne;
        return fich;
}




