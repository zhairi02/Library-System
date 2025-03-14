#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Biblio* charger_n_entrees(char* nomfic, int n) {
    FILE *f = fopen(nomfic, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomfic);
        return NULL;
    }

    Biblio* b = creer_biblio();
    char ligne[512]; // Buffer pour lire chaque ligne
    int num;
    char titre[256], auteur[256];
    int count = 0;

    while (count < n && fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d %255s %255s", &num, titre, auteur) == 3) {
            inserer_en_tete(b, num, titre, auteur);
            count++;
        }
    }

    fclose(f);
    return b;
}

void enregistrer_biblio(Biblio *b, char* nomfic){

    FILE *f=fopen(nomfic,"w");
    Livre *courant=b->L;
    
    while(courant){
        fprintf(f, "%d %s %s\n", courant->num, courant->titre, courant->auteur);
        courant = courant->suiv;
    }

    fclose(f);

}

