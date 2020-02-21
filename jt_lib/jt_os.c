#include "jt_os.h"

Tab_String* executer(String* commande){
          char car;
          Tab_String* tab = Tab_String_Create(0);
          String* ligne;
          int nb_caractere, cmt,  nb_max_caractere,cmt_max_caractere; 
          FILE* lire = popen(commande->chaine, "r");
          nb_caractere = 0;
          nb_max_caractere = 1000;
          cmt_max_caractere =nb_max_caractere;
          ligne =  String_Create_int(nb_max_caractere);
          cmt=0;
          while((car =fgetc(lire))!=EOF){
                     /*on realloue 1000 caractere a la ligne*/
                      if(nb_caractere>=cmt_max_caractere){
                                                         ligne->Reallouer(ligne, nb_max_caractere);
                                                         cmt_max_caractere+=nb_max_caractere;
                      }
                      if(car=='\n'){
                           /*on finalise la ligne*/ 
                          ligne->Set(ligne, '\0',nb_caractere);  
                          ligne->Ajuster_Taille(ligne);
                          tab->Ajouter(tab, ligne, cmt);
                          ligne =  String_Create_int(nb_max_caractere);
                          nb_caractere = 0;   
                          cmt_max_caractere=nb_max_caractere;
                          cmt++;      
                      }else{
                            ligne->Set(ligne, car,nb_caractere);
                            nb_caractere++;
                      }
 /*  [Linker error] undefined reference to `GenererCoalecensceNnoeud2' */                   
                     
          }
          ligne->Set(ligne, '\0',nb_caractere);  
          ligne->Ajuster_Taille(ligne);
          tab->Ajouter(tab, ligne, cmt);
          pclose(lire);
          return tab;
}


