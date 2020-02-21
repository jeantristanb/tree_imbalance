#include "./utilitaire.h"
/****************************************************************************/
/*
*
* ---------------------------------erreur-------------------------------------
*
*/
/****************************************************************************/
/*
* fonction: void erreur_allocation(char* mesdage)
* argument: message imprimer
* retourne: rien 
* fonction utilise lors d'une erreur d'allocation rapporte le message et ferme le programme 
*
*/
#ifdef TESTMEMOIRE
void init_testmemoire(){
     jt_mem = (S_Memoire*)calloc(1, sizeof(S_Memoire));   
     jt_mem->direction = 0;
     jt_mem->string = 0; 
     jt_mem->fichier = 0;
     jt_mem->tab_string = 0;
     jt_mem->arbre = 0;
     jt_mem->noeud = 0;
     jt_mem->longhaplo = 0;
     jt_mem->tablonghaplo = 0;
     jt_mem->snp=0;
     jt_mem->tabdint = 0;
     jt_mem->tabint = 0;
     jt_mem->tabchar = 0;
     jt_mem->tabdouble = 0;
}

void afficher_testmemoire(){
     printf("\nAffichage de la memoire : \n");
     printf("String %d\n", jt_mem->string);     
     printf("Tab_String %d\n", jt_mem->tab_string); 
     printf("Fichier %d\n", jt_mem->fichier); 
     printf("Direction %d\n", jt_mem->direction); 
     printf("Arbre %d\n", jt_mem->arbre); 
     printf("Noeud %d\n", jt_mem->noeud);
     printf("LongHaplo %d\n", jt_mem->longhaplo);
     printf("tab LongHaplo %d\n", jt_mem->tablonghaplo);
     printf("snp %d\n", jt_mem->snp);
     printf("tabdint %d\n", jt_mem->tabdint);
     printf("tabint %d\n",jt_mem->tabint);
     printf("tabchar %d\n",jt_mem->tabchar);
     printf("tabdouble %d\n", jt_mem->tabdouble);
     PAUSE();
}
#endif
void erreur_allocation(char *format, ...) {
  va_list pa;
  int n;
  char *s, c;
  float f;
  printf("erreur d'allocation : "); 
  va_start(pa, format);
  while (*format != '\0') {
    if ( *format == '%' ) {
      switch (*++format) {
        case '%' : putc('%', stderr); break;
        case 'c' : /* affichage d'un caractère */ 
                   c = va_arg(pa, int);
                   putc(c, stderr);
                   break;
        case 'd' : /* affichage d'un entier */ 
                   n = va_arg(pa, int);
                   fprintf(stderr, "%d", n); 
                   break;
        case 'f' : /* affichage d'un float */ 
                   f = va_arg(pa, double);    /* !!!!! */
                   fprintf(stderr,"%f", f); 
                   break;
        case 's' : /* affichage d'une chaîne */ 
                   s = va_arg(pa, char *);
                   for ( ; *s != '\0'; s++ ) 
                     putc(*s,stderr);
                   break;
      } /* end switch */
    }
    else 
      putc(*format,stderr);
    format++;
  }   
  va_end(pa);
  
  #ifdef TESTMEMOIRE
  afficher_testmemoire();
  #endif
    PAUSE();
     exit(0);
} 

/*
* fonction: void erreur(char* mesdage)
* argument: message ï¿½imprimer
* retourne: rien 
* fonction utilise lors d'une erreur  rapporte le message et stoppe le programme 
*
*/

void erreur(char *format, ...) {
  va_list pa;
  int n;
  char *s, c;
  float f;
  va_start(pa, format);
  fprintf(stderr,"\nerreur :\nmessage :");
  while (*format != '\0') {
    if ( *format == '%' ) {
      switch (*++format) {
        case '%' : putc('%', stderr); break;
        case 'c' : /* affichage d'un caractère */ 
                   c = va_arg(pa, int);
                  fprintf(stderr, "%c",c); 
                   break;
        case 'd' : /* affichage d'un entier */ 
                   n = va_arg(pa, int);
                   fprintf(stderr,"%d", n); 
                   break;
        case 'f' : /* affichage d'un float */ 
                   f = va_arg(pa, double);    /* !!!!! */
                   fprintf(stderr,"%f", f); 
                   break;
        case 's' : /* affichage d'une chaîne */ 
                   s = va_arg(pa, char *);
                     fprintf(stderr," %s", s );
                   break;
      } /* end switch */
    }
    else 
      putc( *format, stderr);
    format++;
  }   
  va_end(pa);
  PAUSE();
  exit(0);
} 
/**/
/*
double isum(double *table, int min, int max)
Argument :
        double *table : tableau de double contenant des nombre a sommer
        int min :  Position ou commence a sommer
        int max :  Possition Finissant a sommer
Retourne :
         Double : somme des valeurs entre min et max compris
*/
int isum(int *table, int min, int max)
{
        int s=0;
        int i;
        for (i=min;i<=max;i++)
                s+=table[i];

        return s;
}
/*
double imean(imean *table, int min, int max)
Argument :
        double *table : tableau de double contenant des nombre a moyenner
        int min :  Position ou commence a moyenner
        int max :  Possition Finissant a moyenner
Retourne :
         int : moyenne des valeurs entre min et max compris
*/
double imean(int *table, int min, int max)
{
       return ((double)isum(table,min,max))/((double)(max-min+1));
}


/*
double dsum(double *table, int min, int max)
Argument :
        double *table : tableau de double contenant des nombre a sommer
        int min :  Position ou commence a sommer
        int max :  Possition Finissant a sommer
Retourne :
         Double : somme des valeurs entre min et max compris
*/
double dsum(double *table, int min, int max)
{
        double s=0;
        int i;
        for (i=min;i<=max;i++)
                s+=table[i];

        return s;
}
/*
double dmean(double *table, int min, int max)
Argument :
        double *table : tableau de double contenant des nombre a moyenner
        int min :  Position ou commence a moyenner
        int max :  Possition Finissant a moyenner
Retourne :
         Double : moyenne des valeurs entre min et max compris
*/
double dmean(double *table, int min, int max)
{
       return dsum(table,min,max)/(max-min+1);
}


/***************************************************************************/
/*
*
* -------------------allocation et libï¿½ation de la memoire-------------------
*
*/
/****************************************************************************/
int** d_i_allocate(int nb){
    #ifdef CALLOC
    int** ptr = (int**)calloc(nb, sizeof(int*));
    #else
    int** ptr = malloc(nb* sizeof(int*));
    #endif
	if(ptr==NULL){
 
                  erreur_allocation("d_i_allocate %d",nb );
 
 }
	#ifdef TESTMEMOIRE
    jt_mem->tabdint++;
    #endif
	return ptr;
    
}
int* i_allocate(int nb){
    #ifdef CALLOC
    int* ptr = (int*)calloc(nb,sizeof(int)); 
    #else
    int* ptr = malloc(nb*sizeof(int)); 
    #endif	
    if(ptr==NULL){
                  erreur_allocation("i_allocate %d",nb );
 }
	#ifdef TESTMEMOIRE
    jt_mem->tabint++;
    #endif
	return ptr;
}
short int* short_i_allocate(int nb){
    #ifdef CALLOC
    short int* ptr = (int*)calloc(nb,sizeof(short int)); 
    #else
    short int* ptr = malloc(nb*sizeof(int)); 
    #endif
    if(ptr==NULL)erreur_allocation("s_i_allocate");
	#ifdef TESTMEMOIRE
    jt_mem->tabint++;
    #endif
	return ptr;
}


double* d_allocate(int nb){
    double* ptr;
    #ifdef ERREUR
    if(nb<=0)erreur("d_allocate : nombre inferieur a zero");
    #endif
	#ifdef CALLOC
    ptr = (double*)calloc(nb,sizeof(double));
	#else
	ptr = malloc(nb*sizeof(double));
	#endif
    if(ptr==NULL)erreur_allocation("d_allocate");
	#ifdef TESTMEMOIRE
    jt_mem->tabdouble++;
    #endif
	return ptr;
}
double** d_d_allocate(int nb){
    #ifdef CALLOC
	double** ptr = (double**)calloc(nb, sizeof(double*));
	#else
	double** ptr = malloc(nb*sizeof(double*));
	#endif
	if(ptr==NULL){
(void)fprintf(stderr, "Taille demandee = %d\n", nb);
       erreur_allocation("d_d_allocate");

       }
	#ifdef MEMOIRE_TEST
    global_test_memoire->tab_d_double++;
    #endif
	return ptr;
}
char* c_allocate(int (nb)){
    char* ptr = (char*)calloc(nb,sizeof(char));
	if(ptr==NULL)erreur_allocation("c_allocate");
	#ifdef TESTMEMOIRE
    jt_mem->tabchar++;
    #endif
	return ptr;
}
/*peremt de realouer un tableau de caractere taille total du nouveau tableau : nb*/
char* c_reallocate(char*ancienne, int (nb)){
    char* ptr = (char*)realloc(ancienne,nb*sizeof(char));
	if(ptr==NULL)erreur_allocation("c_reallocate");
	return ptr;
}

int* i_reallocate(int* ancienne, int (nb)){
    int* ptr = (int*)realloc(ancienne,nb*sizeof(int));
	if(ptr==NULL)erreur_allocation("i_reallocate");
	return ptr;
}

char** d_c_reallocate(char**ancienne, int (nb)){
    char** ptr = realloc(ancienne,nb*sizeof(char*));
	if(ptr==NULL)erreur_allocation("c_reallocate");
	return ptr;
}

int** d_i_reallocate(int** ancienne, int (nb)){
    int** ptr = (int**)realloc(ancienne,nb*sizeof(int*));
	if(ptr==NULL)erreur_allocation("d_i_reallocate");
	return ptr;
}

char** d_c_allocate(int (nb)){
    int cmt;
    char** ptr = (char**)calloc(nb,sizeof(char*));
	if(ptr==NULL)erreur_allocation("d_c_allocate");
	for(cmt=0; cmt<nb; cmt++)ptr[cmt]=NULL;

	return ptr;
}

void free_d_tab_char(char** tab){
     free(tab);
    #ifdef MEMOIRE_TEST
    global_test_memoire->tab_char++;
    #endif
}
double*** t_d_allocate(int nb){
	double*** ptr = (double***)calloc(nb, sizeof(double**));
	if(ptr==NULL)erreur_allocation("t_d_allocate");
	return ptr;
}
double**** q_d_allocate(int nb){
	double**** ptr = (double****)calloc(nb, sizeof(double***));
	if(ptr==NULL)erreur_allocation("q_d_allocate");
	return ptr;
}
double***** c_d_allocate(int nb){
	double***** ptr = (double*****)calloc(nb, sizeof(double****));
	if(ptr==NULL)erreur_allocation("q_d_allocate");
	return ptr;
}

void AfficherMatriceDouble(FILE* sortie, double** Matrice, int nb_ligne, int nb_col){
    int cmt_col, cmt_ligne;
    for(cmt_ligne=0; cmt_ligne<nb_ligne; cmt_ligne++){
           for(cmt_col=0;cmt_col<nb_col; cmt_col++)fprintf(sortie,"%f\t", Matrice[cmt_ligne][cmt_col]);                 
           fprintf(sortie,"\n");
    }       
     
}

double** tableau_rec_allocate(int nb_ligne, int nb_col){
    int cmt_col, cmt_ligne;
    double** rec = d_d_allocate(nb_ligne);
    for(cmt_ligne=0; cmt_ligne<nb_ligne; cmt_ligne++){
        rec[cmt_ligne]=d_allocate(nb_col);
        for(cmt_col=0;cmt_col<nb_col; cmt_col++)rec[cmt_ligne][cmt_col]=0.0;
    }    
    return rec;

}
void free_d_tab_double(double** tab){
    free(tab);
    #ifdef MEMOIRE_TEST
    global_test_memoire->tab_d_double--;
    #endif
}
void free_t_tab_double(double*** tab){
    free(tab);
   /* #ifdef MEMOIRE_TEST
    global_test_memoire->tab_t_double--;
    #endif
*/}
void free_tab_double(double* tab){
        free(tab);
	    #ifdef TESTMEMOIRE
        jt_mem->tabdouble--;
        #endif
}
void free_tab_int(int* tab){
    free(tab);
	#ifdef TESTMEMOIRE
    jt_mem->tabint--;
    #endif
}
void free_tab_short_int(short int* tab){
    free(tab);
	#ifdef TESTMEMOIRE
    jt_mem->tabint--;
    #endif
}
void free_d_tab_int(int** tab){
    free(tab);
	#ifdef TESTMEMOIRE
    jt_mem->tabdint--;
    #endif
}
void free_tab_char(char* tab){
    free(tab);
	#ifdef TESTMEMOIRE
    jt_mem->tabchar--;
    #endif
}


void tableau_rec_free(double** rec, int nb_ligne, int nb_col){
    int cmt_col;
    for(cmt_col=0; cmt_col<nb_ligne; cmt_col++){
        free_tab_double(rec[cmt_col]);
    }    
    free_d_tab_double(rec);

}
int** tableau_rect_int_allocate(int nb_ligne, int nb_col){
    int cmt_col, cmt_ligne;
    int** rec = d_i_allocate(nb_ligne);
    for(cmt_ligne=0; cmt_ligne<nb_ligne; cmt_ligne++){
        rec[cmt_ligne]=i_allocate(nb_col);
        for(cmt_col=0;cmt_col<nb_col; cmt_col++)rec[cmt_ligne][cmt_col]=0;
    }    
    return rec;

}

short int** tableau_rect_short_int_allocate(int nb_ligne, int nb_col){
    int cmt_col, cmt_ligne;
    short int** rec = (short int**)calloc(nb_ligne,sizeof(short int*));
    for(cmt_ligne=0; cmt_ligne<nb_ligne; cmt_ligne++){
        rec[cmt_ligne]=short_i_allocate(nb_col);
        for(cmt_col=0;cmt_col<nb_col; cmt_col++)rec[cmt_ligne][cmt_col]=0;
    }    
    return rec;

}

void tableau_rect_int_free(int** rec, int nb_ligne, int nb_col){
    int cmt_col;
    for(cmt_col=0; cmt_col<nb_ligne; cmt_col++){
        free_tab_int(rec[cmt_col]);
    }    
    free_d_tab_int(rec);

}

void tableau_rect_short_int_free(short int** rec, int nb_ligne, int nb_col){
    int cmt_col;
    for(cmt_col=0; cmt_col<nb_ligne; cmt_col++){
        free_tab_short_int(rec[cmt_col]);
    }    
    free(rec);

}

FILE* ouvrirfichier(char* nomfichier,char* mode){
       FILE* fichier =  fopen(nomfichier, mode);
       if(fichier==NULL)erreur("impossibilite d'ouvrir le fichier %s", nomfichier);
        return fichier;
}
char* concatener(char* mot1,char* mot2){
    int i, itt_nm;
    int taille_mot1=0;
    int taille_mot2=0;
    char* nouveau_mot;
    if(mot1==NULL || mot2==NULL)erreur("mot1 ou mot2 null dans concatener");
    /*on recupere la taille du mot1*/
    i=0;
    while(mot1[i]!='\0'){
        taille_mot1++;
        i++;
    }
    i=0;
    while(mot2[i]!='\0'){
        taille_mot2++;
        i++;
    }
    /*on alloue l'espace necessaire pour le nouveau mot*/
    nouveau_mot = c_allocate((taille_mot1+taille_mot2+10));
    
    i=0;
    itt_nm=0;
    /*on ajoute le mot1 au debut*/
    while(i<taille_mot1){
        nouveau_mot[itt_nm]=mot1[i];
        i++;
        itt_nm++;
    }
    /*on ajoute le mot2 ï¿½la suite*/
    i=0;
     while(i<taille_mot2){
        nouveau_mot[itt_nm]=mot2[i];
        i++;
        itt_nm++;
    
    }
    /*on rajoute le signe de fin*/
    nouveau_mot[itt_nm]='\0';
    /*on retourn le nouveau mot*/
    return nouveau_mot;
}
int nb_chiffre_int(int num){
    /*si le chiffre est superieur ï¿½zero on rapelle la fonction en ajoutant 1 pour le negatif*/
    if(num<0)return (nb_chiffre_int(-num)+1);
    if(num<10)return 1;
    else return nb_chiffre_int(((int)(num/10))+1);
}
/*fonction transformant un int en char*/
char* convert_int_char(int arg){
    int taille_arg;
    char* c_arg;
    /*on recupere la taille de l'argument*/
    taille_arg = nb_chiffre_int(arg);
    
    /*on alloue l'espace necessaire */
    c_arg = c_allocate((taille_arg+1));

    /*on le transforme en chaine de caractere*/
    sprintf(c_arg, "%d", arg);
    
    return c_arg;
}
char* ajouter_int(char* message,int num){
    char* temp;
    char* message_fin;
    /*on recupere le numero sous forme de char*/
    temp=convert_int_char(num);
    /*on concatene*/
    message_fin = concatener(message, temp);
    /*on libere l'espace de l'espace temporaire*/
    free_tab_char(temp);
    /*on retourne la chaine*/
    return message_fin;
}
double* proba_cumule(double* proba,int nb){
    int i;
    double * proba_cum = d_allocate(nb);
    proba_cum[0]=proba[0];
    for(i =1; i<nb; i++){
            proba_cum[i]=0;
            proba_cum[i]+=(proba[i]+proba_cum[i-1]);
    }
    return proba_cum;
}



 
 /*

int recherche_dicho(double* tab, double num_recherche, int borne_inf, int borne_sup){
    int borne_moitie;
    borne_moitie = (borne_sup+borne_inf)/2;
    
    if(num_recherche<=tab[borne_moitie]){
            if(borne_moitie==0 || borne_sup==borne_inf || num_recherche>tab[borne_moitie-1])return borne_moitie;
            else return recherche_dicho(tab,num_recherche,borne_inf ,borne_moitie-1);
    }
    else{
        if(borne_moitie==borne_sup || num_recherche<tab[borne_moitie-1] || borne_sup==borne_inf)return borne_moitie;
        else{
             return recherche_dicho(tab, num_recherche,borne_moitie+1,borne_sup);
        }
    }
}

*/
int recherche_dicho(double* tab, double num_recherche, int borne_inf, int borne_sup){
    int borne_moitie = (borne_sup-1+borne_inf)/2;
    while(borne_sup>borne_inf){
            if(num_recherche>tab[borne_moitie]){
                                                  borne_inf = borne_moitie+1;
            }            
            else{

                  borne_sup = borne_moitie;
            
            }
            borne_moitie = (borne_sup+borne_inf)/2;
    }
    return borne_moitie;
}
/**/
void classeIntMethodeMax(int* tab, int nbElement, int maxElement){
         int temp[maxElement+1], cmt, cmt2, cmt3;
         for(cmt=0; cmt<=maxElement; cmt++)temp[cmt]=0;
         for(cmt=0; cmt<nbElement; cmt++)temp[tab[cmt]]++;
         cmt3 = 0;
         for(cmt=0; cmt<=maxElement; cmt++){
                    for(cmt2=0; cmt2<temp[cmt]; cmt2++){
                        tab[cmt3] =   cmt;
                        cmt3++;                  
                    }           
         }
     
}

/*
int DirExist(const char* DirName)
Argument :
         Nom du repertoire pour lequel il faut verifier l'exizstence
Retourne :
         1 si il existe 
         0 si il existe pas
Description :
            Verifie si un repertoire existe ou pas

*/
int DirExist(const char* DirName){
     DIR * rep;
     char Direction[100];
     sprintf(Direction,"./%s", DirName);
     rep = opendir(Direction);
     if(rep==NULL)return 0; 
     closedir(rep);
     return 1;
}

/*
int CreerRepertoire(const char* namerep)
Argument : 
         Nom du repertoire a creer
Retourn :
        1 si le repertoire a bien ete cree
        0 sinon
Description :
            Teste mkdir si elle ne marche pas cree la fonction MD (Dos)
*/
int CreerRepertoire(const char* namerep){
    char instruction[200];
    if(DirExist(namerep)==0){
                (void) sprintf(instruction,"mkdir %s",namerep);
                system(instruction);
                /*Si mkdir n'a pas marche on teste sous Windows ==> commande dos*/
                if(DirExist(namerep)==0){                 
                    (void) sprintf(instruction,"MD %s",namerep);
                     system(instruction);  
                     if(DirExist(namerep)==0)return 0;                                          
                }
        }   
    return 1 ;
}

void CopierMatriceDouble(double** a , double ** b , int col, int ligne){
     int cmtcol, cmtligne;
     for(cmtcol=0;cmtcol<col;cmtcol++)for(cmtligne=0;cmtligne<ligne;cmtligne++)b[cmtcol][cmtligne]=a[cmtcol][cmtligne];
     
}

void CopierTabInt(int* tab1, int* tab2, int nbElement){
     int cmt;
     for(cmt=0; cmt<nbElement; cmt++)tab2[cmt] = tab1[cmt];
}


/*
Retourne l'indice du bonne ordre d'un tableau double
Tab : tableau dont on souhaite le bonne ordre
longeur : longeur du tableau
TabResult : Tableau qui contiendra l'ordre

*/
void GetOrdreTabDouble(double* Tab, int longeur, int* TabResult){
     int cmtTab, cmt2Tab, PosMin,  tempMin;
     double TabMin;     
      for(cmtTab=0; cmtTab<longeur; cmtTab++)TabResult[cmtTab]=cmtTab;
     for(cmtTab=0; cmtTab<longeur; cmtTab++){    
            TabMin = Tab[TabResult[cmtTab]];       
            PosMin = cmtTab;
            for(cmt2Tab=cmtTab+1; cmt2Tab<longeur; cmt2Tab++){    
                if(TabMin>Tab[TabResult[cmt2Tab]]){
                           TabMin = Tab[TabResult[cmt2Tab]];
                           PosMin = cmt2Tab;                        
                    
                } 
                tempMin = TabResult[cmtTab];
                TabResult[cmtTab] = TabResult[PosMin];
                TabResult[PosMin] = tempMin;

            }                 
     }    
     
} 

/*permet de comparer un binaire avec une direction et binaire*/

boolean BonBinaire(char* BinaireArgV,char*  BinaireVoulue){
    int nbCaracArgV, nbCaracVoul, cmt1, cmt2;
    nbCaracArgV = strlen(BinaireArgV);
    nbCaracVoul = strlen(BinaireVoulue);
    if(nbCaracVoul>nbCaracArgV)return FALSE;
    cmt2 = nbCaracArgV;
    cmt1 = nbCaracVoul;
    while(cmt1>=0){
           if(BinaireVoulue[cmt1]!=BinaireArgV[cmt2])return FALSE;
           cmt2--;
           cmt1--;       
                  
    }
    return TRUE;
}

