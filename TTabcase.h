#ifndef TYPE_T_Tab_case
#define TYPE_T_Tab_case

#include "Tcase.h"

#define VMAX 15
#define VMIN 5

typedef struct  TTab_case{
    T_case tab[VMAX];
    int nb_vois;
}T_Tab_case;

int Hasard(int bi, int bs);
void Hasard_Ban(T_Tab_case ban, int nban, int nl, int nc);
//nb_vois present dand le type T_Tab_Case pour éviter les erreurs en passant en pointeur nb_vois dans toutes les fonction
void Voisines(int l, int c, int nl, int nc, int nban, T_Tab_case tban, T_Tab_case tv);
void Coup_joueur(int nl, int nc, T_case pion, int nban, T_Tab_case tban, T_Tab_case tv);
void Coup_ordi_hasard(int nl, int nc, T_case pion, int nban, T_Tab_case tban, T_Tab_case tv);


#endif
