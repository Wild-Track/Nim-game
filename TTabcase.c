#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "TTabcase.h"


int Hasard(int bi, int bs){
    int x;
    x = rand()%(bs+1) + bi ;
    return x;
}

void Hasard_Ban(T_Tab_case ban, int nban, int nl, int nc) {
    //nbl , nbc nombre lignes colonnes servant pour les cases bannies
    int i, j, nbl, nbc;
    int trouve = 0;


    for(i= 0; i <= nban; i++){
        do{
            nbl = Hasard(1, nl-1);
            nbc = Hasard(1, nc-1);
            for(j= 0; j < VMAX; j++){
                //Vérification des conditions pour les cases bannies
                if((ban.tab[j].il != nbl) && (ban.tab[j].ic != nbc)){
                    if(((ban.tab[j].il != nbl -1)&&(ban.tab[j].ic != nbc + 1))||((ban.tab[j].il != nbl + 1)&&(ban.tab[j].ic != nbc - 1))){
                        trouve = 1;
                    }
                    else
                        trouve = 0;
                }
                else
                    trouve = 0;
            }
        } while(trouve == 0);
        //Remplissage des coordonnées des différentes cases bannies
        ban.tab[i].ic = nbc;
        ban.tab[i].il = nbl;
        // TTab_case -> tab -> Tcase -> int (il)
    }
}

//l et c coordonnées de la case c, nl/nc coordonnées de nombres de lignes colonnes présent dans la grille
void Voisines(int l, int c, int nl, int nc, int nban, T_Tab_case ban, T_Tab_case tv) {
    //trouve servant à savoir si une case bannies à été trouvé comme voisine
    int i = 0, trouve = 0;

    printf("test_voisinnes");
//Vérification de la 1ere voisines de droites
    if(c+1 < nc){
    //Check parmis toutes les cases bannies
        do{
            if((ban.tab[i].ic == c+1) && (ban.tab[i].il == l))
                trouve = 1;
            i++;
        }while((trouve == 0) || (i != nban));
//Si pas trouver parmis toutes les cases bannies alors 1eres voisines de droite trouver
        if(trouve == 0){
            tv.tab[i].il = l;
            tv.tab[i].ic = c+1;
            tv.nb_vois ++;
            i=0;
    //Vérification de la 2eme voisines de droite de même que pour la premiere
            do{
                if((ban.tab[i].ic == c+2) && (ban.tab[i].il == l))
                    trouve = 1;
                i++;
            }while((trouve == 0) || (i != nban));
            if(trouve == 0){
                tv.tab[i].il = l;
                tv.tab[i].ic = c+2;
                tv.nb_vois ++;
            }
        }
    }

//vérification de la 1ere voisines du bas
    if(l+1 < nl){
        i = 0;
        trouve = 0;
     //Check parmis toutes les cases bannies
        do{
            if((ban.tab[i].il == l+1) && (ban.tab[i].ic == c))
                trouve = 1;
            i++;
        }while((trouve = 0) || (i != nban));

//Si pas trouver parmis toutes les cases bannies alors 1eres voisines du bas trouver
        if(trouve == 0){
            tv.tab[i].il = l+1;
            tv.tab[i].ic = c;
            tv.nb_vois ++;
            i = 0;
    //Vérification de la 2eme voisines du bas de même que pour la premiere
            do{
                if((ban.tab[i].il == l+1) && (ban.tab[i].ic == c))
                    trouve = 1;
                i++;
            }while((trouve == 0) || (i != nban));
            if(trouve == 0){
                tv.tab[i].il = l+2;
                tv.tab[i].ic = c;
                tv.nb_vois ++;
            }
        }
    }
}

void Coup_joueur(int nl, int nc, T_case pion, int nban, T_Tab_case tban, T_Tab_case tv){
    int i, select;

    Voisines(pion.il, pion.ic, nl, nc, nban, tban, tv);
    printf("A toi de jouer !!!!!!!!! \n Choisi la destinnation");
    for(i= 0; i < tv.nb_vois; i++){
        printf("%d : (%d,%d) ", i+1, tv.tab[i].il, tv.tab[i].ic);
    }
    printf("\n");
    scanf("%d", &select);
    printf("--------> %d", select);
    pion.il = tv.tab[select-1].il;
    pion.ic = tv.tab[select-1].ic;
}

void Coup_ordi_hasard(int nl, int nc, T_case pion, int nban, T_Tab_case tban, T_Tab_case tv){
    int select;

    Voisines(pion.il, pion.ic, nl, nc, nban, tban, tv);
    printf("L'ordinateur déplace le pion en :");
    select = Hasard(0, tv.nb_vois - 1);
    pion.il = tv.tab[select].il;
    pion.ic = tv.tab[select].ic;
    printf("(%d,%d) \n", tv.tab[select].il, tv.tab[select].ic);
}
