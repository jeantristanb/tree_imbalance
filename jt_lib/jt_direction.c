#include "jt_direction.h"
Direction* allocate_Direction(){
        Direction* dir = (Direction*)calloc(1,sizeof(Direction));
        if(dir==NULL)erreur_allocation("allocate_Direction");
        dir->repertoire = NULL;
        dir->Str_direction = NULL;
        return dir;
} 

void Direction_Afficher(FILE* sortie, Direction* dir){
     printf("Direction : ");
     dir->Str_direction->Afficher(sortie, dir->Str_direction);
     dir->repertoire->Afficher(sortie, dir->repertoire);
}

void Direction_free(Direction* dir){
     if(dir->repertoire!=NULL)dir->repertoire->Free(dir->repertoire);
     if(dir->Str_direction!=NULL)dir->Str_direction->Free(dir->Str_direction);
     free(dir);     
     
}
/*retourne un tableau de string contenant les fichiers du'une direction*/
Tab_String* Direction_Get_Fichier_Tab_String(Direction* dir){
   struct dirent *lecture;
   int cmt=0;
   String* direction;
   Tab_String* str_Fichier = Tab_String_Create(0);
   DIR* rep = opendir(dir->Str_direction->chaine);
   String* bakslach = String_Create("/");
   String* point = String_Create(".");
   String* pointpoint = String_Create("..");
   String* fichier;
   while ((lecture = readdir(rep))){
         direction = dir->Str_direction->Dupliquer(dir->Str_direction);  
         fichier = String_Create(lecture->d_name);
         if(!fichier->Comparer(fichier, pointpoint) && !fichier->Comparer(fichier, point)){
                                    direction->Concatener(direction,bakslach);
                                    direction->Concatener(direction, fichier);
                                    str_Fichier->Ajouter(str_Fichier, direction, cmt);
                                    cmt++;
      }
      fichier->Free(fichier);
   }
   closedir(rep);
   point->Free(point);
   pointpoint->Free(pointpoint);
   bakslach->Free(bakslach);
   return str_Fichier;
}
/*retourne un tableau de string avec chaque direction a partir*/
Tab_String* Direction_Get_Dossier_Tab_String(Direction* dir){
          int cmt, cmt2=0;
          char message[1000];
          DIR* D_dir;
          Tab_String* str_Dossier = Tab_String_Create(0);
          String* direction;
          String* dossier; 
          String* bakslach = String_Create("/");
          String* point = String_Create(".");
          String* pointpoint = String_Create("..");
          for(cmt=0; cmt<dir->repertoire->nb_string; cmt++){
                     direction = dir->Str_direction->Dupliquer(dir->Str_direction);
                     dossier = dir->repertoire->Get(dir->repertoire, cmt);
                     if(!dossier->Comparer(dossier, pointpoint) && !dossier->Comparer(dossier, point)){
                              direction->Concatener(direction,bakslach);
                              direction->Concatener(direction,dossier);
                              if((D_dir=opendir(direction->chaine))!=NULL){
                                                           str_Dossier->Ajouter(str_Dossier, direction, cmt2);
                                                           cmt2++; 
                                                           if(closedir(D_dir)==-1){
                                                                      sprintf(message, "get_Direction_Tab_String : impossibilite de fermer la direction : %s", direction->chaine );
                                                                      erreur(message);                         
                                                           } 
                              }
                     }
          }
          point->Free(point);
          pointpoint->Free(pointpoint);
          bakslach->Free(bakslach);
          return str_Dossier;
}

int Direction_est_presente( Direction* dir,  String* str){
       int cmt;
       String* str2;

       for(cmt=0; cmt<dir->repertoire->nb_string; cmt++){
                  str2 = dir->repertoire->Get(dir->repertoire, cmt);
                  if(str->Est_Present(str,str2) || str2->Est_Present(str2,str))return cmt;           
                  
       }
       return -1;
       
}


Direction* Direction_Create(String* s_direc){
      Direction*dir = allocate_Direction();
      int cmt = 0;
      DIR* D_dir;
      String* Temp;
      struct dirent *lecture;
      String* point = String_Create(".");
      String* pointpoint = String_Create("..");
      String* str = s_direc->Dupliquer(s_direc);
      dir->repertoire = Tab_String_Create(0);
      dir->Str_direction = str;
      D_dir =  opendir(str->chaine);
      if(D_dir==NULL){
                      erreur( "Direction_Create : impossibilite d'ouvrir la direction : %s",str->chaine);                
      }
       while ((lecture = readdir(D_dir))){
                       Temp = String_Create(lecture->d_name);     
                       if(!Temp->Comparer(Temp, point) && !Temp->Comparer(Temp, pointpoint) ){dir->repertoire->Ajouter(dir->repertoire,Temp, cmt);
                                 cmt++;
                       }           
       }
      if(closedir(D_dir)==-1){
                      erreur("Direction_Create : impossibilite de fermer la direction : %s",str->chaine);                         
      } 
      dir->Afficher = Direction_Afficher;
      dir->Get_Dossier_Tab_String = Direction_Get_Dossier_Tab_String; 
      dir->Get_Fichier_Tab_String = Direction_Get_Fichier_Tab_String;
      dir->Free = Direction_free;
      dir->Est_Presente = Direction_est_presente;
      point->Free(point);
      point->Free(pointpoint);
      return dir;     
}
