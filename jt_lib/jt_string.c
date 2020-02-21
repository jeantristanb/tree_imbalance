#include "jt_string.h"

void Tab_String_Free(Tab_String* tab){
     int cmt;
     for(cmt=0; cmt< tab->nb_string; cmt++){
                if(tab->Get(tab, cmt)!=NULL)(tab->Get(tab, cmt))->Free((tab->Get(tab, cmt)));
     }
     free(tab->tab);
     free(tab);    
     #ifdef TESTMEMOIRE
     jt_mem->tab_string--;
     #endif
     
}

String* Tab_String_get_string(Tab_String* tab, int nb){
         #ifdef ERREUR
         if(nb >= tab->nb_string || nb <0 )erreur("Tab_String_get_string");
         #endif
         return tab->tab[nb];        
}


void Tab_String_set_string(Tab_String* tab, String* str , int nb){
         if(nb >= tab->nb_string || nb <0 )erreur("Tab_String_set_string");
         if(tab->tab[nb]==NULL)tab->tab[nb]=str;
         else{
              tab->tab[nb]->Free(tab->tab[nb]);
              tab->tab[nb] =str;
         }
}


void Tab_String_afficher(FILE* sortie, Tab_String* tab_s){
     int cmt;
     for(cmt=0; cmt<tab_s->nb_string; cmt++)(tab_s->Get(tab_s,cmt))->Afficher(sortie, (tab_s->Get(tab_s, cmt)));    
}

void Tab_String_ajouter(Tab_String* tab_str, String* str, int position ){
        int cmt;
        if(position<0 || position > tab_str->nb_string)erreur("Tab_String_ajouter : ajout de la ligne a une mauvaise position\n");
        /*on realloue la memoire*/
        tab_str->tab = realloc(tab_str->tab, (tab_str->nb_string+1)*sizeof(String*));
        if(tab_str->tab==NULL)erreur_allocation("Tab_String_ajouter");
        /*on decale*/
        for(cmt=tab_str->nb_string; cmt>position; cmt--){
                   tab_str->tab[cmt] = tab_str->tab[cmt-1];                                     
        }
        tab_str->tab[position]=str;
        tab_str->nb_string++;
}
Tab_String* Tab_String_dupliquer(Tab_String* tab){
            int cmt;
            Tab_String* tab_new = Tab_String_Create(tab->nb_string);
            for(cmt=0; cmt<tab->nb_string; cmt++){
                    tab_new->Set(tab_new,(tab->Get(tab, cmt))->Dupliquer(tab->Get(tab, cmt)), cmt);        
            } 
            return tab_new;
            
}

Tab_String* Tab_String_Create(int nb_string){
     int cmt;
     Tab_String* tab_str = (Tab_String*)calloc(1, sizeof(Tab_String));
     if(tab_str==NULL)erreur("Tab_String_Create");
     tab_str->tab = (String**)calloc(nb_string, sizeof(String*));
     if(tab_str->tab==NULL)erreur("Tab_String_Create");
     for(cmt=0; cmt<nb_string; cmt++){
                tab_str->tab[cmt]=NULL;
     }
     #ifdef TESTMEMOIRE
     jt_mem->tab_string++;
     #endif
     tab_str->nb_string = nb_string;
     tab_str->Get =Tab_String_get_string;
     tab_str->Set =Tab_String_set_string;
     tab_str->Afficher=Tab_String_afficher;
     tab_str->Ajouter =Tab_String_ajouter;
     tab_str->Free = Tab_String_Free;
     tab_str->Dupliquer = Tab_String_dupliquer;
     return tab_str;      
}

boolean String_compare(String* chaine1,String* chaine2 ){
       if(strcmp(chaine1->chaine,chaine2->chaine)==0)return TRUE;
       else return FALSE;
}

boolean String_compare_sans_case(String* chaine1,String* chaine2){
       if(strcmp(chaine1->chaine,chaine2->chaine)==0)return TRUE;
       else return FALSE;
}

boolean String_est_present(String* chaine_longue,String* chaine_courte){
        char* test;
        if((test=strstr(chaine_longue->chaine, chaine_courte->chaine))==NULL)return FALSE;
        else{
              return TRUE;       
             } 
}
/*concatene chaine 2 et chaine 1 en modifiant chaine1*/
void String_concatener(String* chaine1,String* chaine2){
      int longeur = chaine1->longeur + chaine2->longeur;
      char* chain;
      chain = c_allocate(longeur+1);
      if(chain==NULL)erreur_allocation("Create_string");
      sprintf(chain, "%s%s", chaine1->chaine, chaine2->chaine);
      free_tab_char(chaine1->chaine);
      chaine1->chaine = chain;
      chaine1->longeur = longeur;
}

void String_remplacer(String* chaine, char caractere, char caractere2){
     int cmt = 0;
     while(chaine->chaine[cmt]!='\0'){
               if(chaine->chaine[cmt]==caractere)chaine->chaine[cmt] = caractere2;
     cmt++;
                           
     }
}
void String_supprimer(String* chaine, char caractere){
     char* chain =c_allocate(chaine->longeur+1);
     int cmt = 0, cmt2=0;
     if(chain==NULL)erreur_allocation("Create_string");      
     while(chaine->chaine[cmt]!='\0'){
               if(chaine->chaine[cmt]!=caractere){
                                  chain[cmt2] =chaine->chaine[cmt]; 
                                  cmt2++;
               }
     cmt++;
                           
     }
     chain[cmt2]='\0';
     free_tab_char(chaine->chaine);
     chaine->chaine = chain;
}

int String_compter(String* chaine, char caractere){
        int cmt=0, cmt2=0;
        while(chaine->chaine[cmt]!='\0'){
                      if(chaine->chaine[cmt]==caractere)cmt2++;
                      cmt++;                                                    
        }
        return cmt2;
}
void String_Set(String* chaine, char caractere, int position){
     if(chaine->longeur<=position)erreur("String_Set :chaine->longeur<=position");  
     chaine->chaine[position] = caractere;
}

/**/
Tab_String* String_split(String* chaine, char caractere){
     int nb_caractere = 0, cmt, cmt2, cmt3;
     char* chaine2 = c_allocate(chaine->longeur+1);
     /*on copie la chaine que l(on veut decouper*/
     char* c_chaine = c_allocate(chaine->longeur+1);
     Tab_String* tab_str=NULL;
     c_chaine = strcpy(c_chaine, chaine->chaine);
     /*on enleve les doublons*/
     cmt=0;
     /*si le premier caractere est le caractere recherche on ne le prend pas en compte*/
     while(chaine->chaine[cmt]==caractere)cmt++;
     cmt2=0;
     while(chaine->chaine[cmt]!='\0'){
             c_chaine[cmt2]=chaine->chaine[cmt];
             cmt2++;
             if(chaine->chaine[cmt]==caractere){
                nb_caractere++;
                 while(chaine->chaine[cmt]==caractere && chaine->chaine[cmt]!='\0' )cmt++;                                        
             }else cmt++;
             if(chaine->chaine[cmt]=='\0'){
                         c_chaine[cmt2]='\0';
                         nb_caractere--;                  
             }
     }
     nb_caractere+=2;
     tab_str = Tab_String_Create(nb_caractere);
     cmt=0, cmt2=0, cmt3=0;
     while(c_chaine[cmt]!='\0'){
                if(c_chaine[cmt]==caractere){
                              chaine2[cmt2]='\0';
                              tab_str->Set(tab_str, String_Create(chaine2), cmt3);
                              cmt2=0;
                              cmt3++;                               
                }
                else{
                      chaine2[cmt2]=c_chaine[cmt];
                      cmt2++;
                      }
                cmt++;
     }
     chaine2[cmt2]='\0';
     tab_str->Set(tab_str, String_Create(chaine2), cmt3);
     /*pour chacun */
     free_tab_char(chaine2);
     return tab_str;
}
void String_free(String* str){
     if(str->chaine==NULL)erreur("String_free");
     free_tab_char(str->chaine);
     #ifdef TESTMEMOIRE
     jt_mem->string--;
     #endif
     free(str);     
}
String* String_Dupliquer(String* str){
     return String_Create(str->chaine);
}
void String_afficher(FILE* sortie, String* str){
     fprintf(sortie, "%s\n", str->chaine);     
}
void String_Reallouer_chaine(String* str, int taille_suplementaire){
     str->longeur = str->longeur+taille_suplementaire;
     str->chaine = (char*)realloc(str->chaine, (str->longeur+1)*sizeof(char));     
     if(str->chaine==NULL)erreur_allocation("String_Reallouer");
}
void String_ajuster_taille(String* str){
     int cmt=0;
     while(cmt<str->longeur && str->chaine[cmt]!='\0')cmt++;
     if(str->chaine[cmt]!='\0')erreur("String_ajuster_taille : pas de \\0 fin de chaine");
     if(cmt<str->longeur)str->chaine=(char*)realloc(str->chaine, (cmt+1)*sizeof(char));
     str->longeur = cmt;

}
/*retourne le nombre de difference entre deux chaine*/
int String_nombre_diff(String* str, String* str2){
    int max = MIN(str->longeur,str2->longeur), cmt, nb_diff=0;
    for(cmt=0; cmt<max; cmt++){
                 if(str->chaine[cmt]!=str2->chaine[cmt]) nb_diff++;
    }
    return nb_diff;
}



void String_init_pointeur_fction(String* str){
              str->Comparer = String_compare;
              str->Comparer_Sans_Case = String_compare_sans_case;
              str->Concatener = String_concatener;
              str->Remplacer = String_remplacer;
              str->Compter = String_compter;
              str->Split = String_split;
              str->Afficher = String_afficher;
              str->Supprimer = String_supprimer;
              str->Dupliquer = String_Dupliquer;
              str->Free = String_free;
              str->Est_Present = String_est_present;
              str->Set = String_Set;
              str->Reallouer = String_Reallouer_chaine;
              str->Ajuster_Taille = String_ajuster_taille;
              str->Nombre_Diff = String_nombre_diff;
}


String* String_Create(char* chaine){
              /*allocation*/
              String* str = (String*)calloc(1,sizeof(String));
              if(str==NULL)erreur_allocation("Create_string");
              str->longeur = strlen(chaine);
              str->chaine = c_allocate(str->longeur+1);
              if(str->chaine==NULL)erreur_allocation("Create_string");
              str->chaine = strcpy(str->chaine, chaine);
              String_init_pointeur_fction(str);
              #ifdef TESTMEMOIRE
              jt_mem->string++;
              #endif
              return str;
}
String* String_Create_int(int nb_caractere){
              /*allocation*/
              String* str = (String*)calloc(1,sizeof(String));
              if(str==NULL)erreur_allocation("Create_string");
              str->longeur = nb_caractere;
              str->chaine = c_allocate(nb_caractere+1);
              if(str->chaine==NULL)erreur_allocation("Create_string");
              String_init_pointeur_fction(str);
              #ifdef TESTMEMOIRE
              jt_mem->string++;
              #endif
              return str;
}
