#ifndef _DIRECTION
#define _DIRECTION

#include "./jt_string.h"
#include <sys/types.h>
#include <dirent.h>

typedef struct Direction{
        String* Str_direction; 
        Tab_String *repertoire;
        void (*Afficher)(FILE*, struct Direction*);
        Tab_String* (*Get_Dossier_Tab_String)(struct Direction* );
        Tab_String* (*Get_Fichier_Tab_String)(struct Direction* );
        void (*Free)(struct Direction*);
        int (*Est_Presente)(struct Direction*, struct String*);
        
}Direction;
Direction* Direction_Create(String* s_direc);

#endif
