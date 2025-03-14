#include "entreeSortieH.h"

BiblioH* charger_n_entreesH(char* nomfic, int n, int m) {
    FILE *f = fopen(nomfic, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomfic);
        return NULL;
    }

    BiblioH* b = creer_biblioH(m);
    char ligne[512]; // Buffer pour lire chaque ligne
    int num;
    char titre[256], auteur[256];
    int count = 0;

    while (count < n && fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d %255s %255s", &num, titre, auteur) == 3) {
            inserer(b, num, titre, auteur);
            count++;
        }
    }

    fclose(f);
    return b;
}

void enregistrer_biblioH(BiblioH *b, char* nomfic) {
    FILE *f = fopen(nomfic, "w");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomfic);
        return;
    }

    for (int i = 0; i < b->m; i++) {
        LivreH *courant = b->T[i];
        while (courant) {
            fprintf(f, "%d %s %s\n", courant->num, courant->titre, courant->auteur);
            courant = courant->suivant;
        }
    }

    fclose(f);
}