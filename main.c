#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TTabcase.h"

int maximum(int a, int b) {
    if(a<b){
        return b;
    }
    else{
        return a;
    }
}

void parametre(int *nl, int *nc, int *lvl, int *first, int *nban){

    printf("paramètres du jeu : \n");
    do{
            printf("Nombres de lignes: ");
            scanf("%d", nl);
    }while((*nl < VMIN) || (*nl > VMAX ));
    do{
        printf("Nombres de colonnes:");
        scanf("%d", nc);
    } while((*nc < VMIN) || (*nc > VMAX));
    printf("Nombres de cases bannies générées: ");
    *nban = Hasard(0, maximum(*nl, *nc));
    printf("%d \n", *nban);
    do{
    printf("niveau de 1 à 4 : ");
    scanf("%d", lvl);
    }while((*lvl < 1) || (*lvl > 4));
    do{
        printf("Qui commence ? \n l'ordinateur (1) ou le joueur (2) : ");
        scanf("%d", first);
        printf("%d %d %d", *nban, *nc, *nl);
    } while((*first != 1) && (*first != 2));
}

//t table de nimbers, tab_vois contenant les voisines
void calcul_nimber(int nim[][VMAX], int nl, int nc, T_Tab_case tab_vois, int nban, T_Tab_case ban){
    int i, j, k = 0, tr0 = 0, trouve_ban = 0;
    //i, j, k variables d'incrémentation, tr0 variables servant à savoir si une voisine de la case à un nimber égal à 0


    nim[nl -1][nc -1] = 0;
    //décrementation des colonnes (-1 car le tableau commence à 0)
    for(i = nc -1; i >= 0; i--){
      //décrementation des lignes
        for(j = nl - 1; j >= 0; j--){
            Voisines(j, i , nl, nc, nban, ban, tab_vois);
            //vérification des cases bannies car le nimber de compte pas les cases bannies

            do{
                if((ban.tab[k].il == j) && (ban.tab[k].ic == i)){
                  trouve_ban = 1;
                }
                k ++;
            }while((trouve_ban == 1) || (k < nban));
            if(trouve_ban == 0){
                k = 0;
                //Vérification sur toutes les voisines si l'une d'entre elle est un 1 ou un 0
                do{
                    if(nim[tab_vois.tab[k].il][tab_vois.tab[k].ic] == 0)
                    tr0 = 1;
                    k++;
                }while((k != tab_vois.nb_vois) || (tr0 = 1));
                nim[j][i] = tr0;
            }
            else{
            //valeur de nimbers par défaut à -1 pour les cases bannies
                nim[j][i] = -1;
            }
        }
    }
}

void Coup_ordi_gagnant(int nl, int nc, T_case pion, int nban, T_Tab_case tban, T_Tab_case tv, int nim[][VMAX]){
    int i = 0, trouve = 0;

    Voisines(pion.il, pion.ic, nl, nc, nban, tban, tv);
    do{
        //trouve indique si un 0 comme voisin à été trouvé
        if(nim[tv.tab[i].il][tv.tab[i].ic] == 0)
            trouve = 1;
        else
            i++;
    }while((i != tv.nb_vois) || (trouve == 0));
    if(trouve == 1){
        pion.il = tv.tab[i].il;
        pion.ic = tv.tab[i].ic;
        printf("L'ordinateur place le pion en : (%d,%d)", tv.tab[i].il, tv.tab[i].ic);
    }
    else
        Coup_ordi_hasard(nl, nc, pion, nban, tban, tv);
}

void Interfaces(int nlig, int ncol, int nban , T_Tab_case ban, T_case pion){
    int i, j, k;

    for(i = 0; i <= nlig; i++){
        for(j = 0; j <= ncol; j++){
            if(j == 0)
                printf("|");
            for(k = 0; k <= nban; k++){
                if((ban.tab[k].il == i) && (ban.tab[k].ic == j))
                    printf("X|");
            }
            if((pion.il == i) && (pion.ic == j))
                printf("O|");
            else
                printf("-|");
        }
    }
}

int main(){
    int nlig, ncol, niveau, first, nban, i;
    int nim[VMAX][VMAX];
    T_Tab_case tv;
    T_Tab_case ban;
    T_case pion = {0,0};

    for(i = 0; i < VMAX; i++){
        tv.tab[i].il = 0;
        tv.tab[i].ic = 0;
        ban.tab[i].il = 0;
        ban.tab[i].ic = 0;
    }

    srand((unsigned int)time(NULL));

    parametre(&nlig, &ncol, &niveau, &first, &nban);
    Hasard_Ban(ban, nban, nlig, ncol);
    calcul_nimber(nim, nlig, ncol, tv, nban, ban);
    printf("C'est parti !");
    Interfaces(nlig, ncol, nban, ban, pion);
    if(first == 2){
        do{
            Coup_joueur(nlig, ncol, pion, nban, ban, tv);
            Interfaces(nlig, ncol, nban, ban, pion);
            if((pion.il == nlig) && (pion.ic == ncol)){
                printf("Le joueur à gagner");
                break;
            }
            Coup_ordi_gagnant(nlig, ncol, pion, nban, ban, tv, nim);
            Interfaces(nlig, ncol, nban, ban, pion);
            if((pion.il == nlig) && (pion.ic == ncol)){
                printf("L'ordinateur à gagner");
                break;
            }
        }while(1);
    }
    else{
        do{
            Coup_ordi_gagnant(nlig, ncol, pion, nban, ban, tv, nim);
            Interfaces(nlig, ncol, nban, ban, pion);
            if((pion.il == nlig) && (pion.ic == ncol)){
                printf("L'ordinateur à gagner");
                break;
            }
            Coup_joueur(nlig, ncol, pion, nban, ban, tv);
            Interfaces(nlig, ncol, nban, ban, pion);
            if((pion.il == nlig) && (pion.ic == ncol)){
                printf("Le joueur à gagner");
                break;
            }
        }while(1);
    }
}
