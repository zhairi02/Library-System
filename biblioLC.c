#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Livre* creer_livre(int num, char* titre, char* auteur) {
    Livre *l = (Livre*)malloc(sizeof(Livre));
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suiv = NULL;
    return l;
}

void liberer_livre(Livre* l) {
    if (l) {
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

Biblio* creer_biblio() {
    Biblio *b = (Biblio*)malloc(sizeof(Biblio));
    b->L = NULL;
    return b;
}

void liberer_biblio(Biblio* b) {
    Livre *courant = b->L;
    while (courant) {
        Livre *suivant = courant->suiv;
        liberer_livre(courant);
        courant = suivant;
    }
    free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur) {
    Livre *nouveau = creer_livre(num, titre, auteur);
    nouveau->suiv = b->L;
    b->L = nouveau;
}

void afficher_livre(Livre* l) {
    if (l) {
        printf("Numero: %d, Titre: %s, Auteur: %s\n", l->num, l->titre, l->auteur);
    } else {
        printf("Livre non trouve\n");
    }
}

void afficher_biblio(Biblio* b) {
    if (!b || !b->L) {
        printf("bibliotheque vide\n");
        return;
    }
    Livre *courant = b->L;
    while (courant) {
        afficher_livre(courant);
        courant = courant->suiv;
    }
}

Livre *rechercher_par_num(Biblio *b, int num){
    
    Livre *courant=b->L;

    while(courant){
        if(courant->num==num){
            return courant;
        }
        courant=courant->suiv;
    }

    return NULL;

}

Livre* rechercher_par_titre(Biblio* b, char* titre) {

    Livre *courant = b->L;
    while (courant) {
        if (strcmp(courant->titre, titre) == 0)
            return courant;
        courant = courant->suiv;
    }
    return NULL;
}

Biblio* rechercher_par_auteur(Biblio* b, char* auteur) {
    Biblio* res = creer_biblio();
    Livre *courant = b->L;
    while (courant) {
        if (strcmp(courant->auteur, auteur) == 0)
            inserer_en_tete(res, courant->num, courant->titre, courant->auteur);
        courant = courant->suiv;
    }
    return res;
}

 void supprimer_livre(Biblio* b, int num) {
    Livre *courant = b->L;
    Livre *prec = NULL;
    while (courant) {
        if (courant->num == num) {
            if (prec)
                prec->suiv = courant->suiv;
            else
                b->L = courant->suiv;
            liberer_livre(courant);
            return;
        }
        prec = courant;
        courant = courant->suiv;
    }
}

void fusionner_biblios(Biblio *b1, Biblio *b2){
    Livre *courant= b2->L;
    while(courant->suiv){
        inserer_en_tete(b1, courant->num, courant->titre, courant->auteur);
        courant= courant->suiv;
    }
    liberer_biblio(b2);
}

Biblio* rechercher_exemplaires(Biblio* b) {
    Biblio* res = creer_biblio();
    for (Livre* l1 = b->L; l1; l1 = l1->suiv) {
        for (Livre* l2 = l1->suiv; l2; l2 = l2->suiv) {
            if (strcmp(l1->titre, l2->titre) == 0 && strcmp(l1->auteur, l2->auteur) == 0) {
                inserer_en_tete(res, l1->num, l1->titre, l1->auteur);
                inserer_en_tete(res, l2->num, l2->titre, l2->auteur);
            }
        }
    }
    return res;
}
