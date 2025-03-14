#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define A 0.6180339887 // (√5 - 1) / 2 - Nombre d'or diminué de 1

int fonctionClef(char* auteur) {
    int somme = 0;
    for (int i = 0; auteur[i] != '\0'; i++) {
        somme += auteur[i];
    }
    return somme;
}

LivreH* creer_livreH(int num, char* titre, char* auteur) {
    LivreH* l = (LivreH*)malloc(sizeof(LivreH));
    if (!l) return NULL;
    l->clef = fonctionClef(auteur);
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suivant = NULL;
    return l;
}

void liberer_livreH(LivreH* l) {
    if (l) {
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

BiblioH* creer_biblioH(int m) {
    BiblioH* b = (BiblioH*)malloc(sizeof(BiblioH));
    if (!b) return NULL;
    b->nE = 0;
    b->m = m;
    b->T = (LivreH**)malloc(m * sizeof(LivreH*));
    if (!b->T) {
        free(b);
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        b->T[i] = NULL;
    }
    return b;
}

void liberer_biblioH(BiblioH* b) {
    if (b) {
        for (int i = 0; i < b->m; i++) {
            LivreH* courant = b->T[i];
            while (courant) {
                LivreH* temp = courant;
                courant = courant->suivant;
                liberer_livreH(temp);
            }
        }
        free(b->T);
        free(b);
    }
}

int fonctionHachage(int cle, int m) {
    double val = cle * A;
    val = val - (int)val; // On garde la partie décimale
    return (int)(m * val);
}

void inserer(BiblioH* b, int num, char* titre, char* auteur) {
    if (!b) return;
    int index = fonctionHachage(num, b->m);
    LivreH* nouveau = creer_livreH(num, titre, auteur);
    if (!nouveau) return;
    nouveau->suivant = b->T[index];
    b->T[index] = nouveau;
    b->nE++;
}

void afficher_livreH(LivreH* l) {
    if (l) {
        printf("Numero: %d, Titre: %s, Auteur: %s\n", l->num, l->titre, l->auteur);
    } else {
        printf("Livre non trouve\n");
    }
}

void afficher_biblioH(BiblioH* b) {
    if (!b || b->nE == 0) {
        printf("Bibliotheque vide\n");
        return;
    }
    for (int i = 0; i < b->m; i++) {
        LivreH* courant = b->T[i];
        while (courant) {
            afficher_livreH(courant);
            courant = courant->suivant;
        }
    }
}

LivreH* rechercher_par_numH(BiblioH* b, int num) {
    int index = fonctionHachage(num, b->m);
    LivreH* courant = b->T[index];
    while (courant) {
        if (courant->num == num) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

BiblioH* rechercher_par_auteurH(BiblioH* b, char* auteur) {
    BiblioH* res = creer_biblioH(b->m);
    for (int i = 0; i < b->m; i++) {
        LivreH* courant = b->T[i];
        while (courant) {
            if (strcmp(courant->auteur, auteur) == 0) {
                inserer(res, courant->num, courant->titre, courant->auteur);
            }
            courant = courant->suivant;
        }
    }
    return res;
}

void supprimer_livreH(BiblioH* b, int num) {
    int index = fonctionHachage(num, b->m);
    LivreH* courant = b->T[index];
    LivreH* prec = NULL;
    while (courant) {
        if (courant->num == num) {
            if (prec) {
                prec->suivant = courant->suivant;
            } else {
                b->T[index] = courant->suivant;
            }
            liberer_livreH(courant);
            b->nE--;
            return;
        }
        prec = courant;
        courant = courant->suivant;
    }
}

LivreH* rechercher_par_titreH(BiblioH* b, char* titre) {
    for (int i = 0; i < b->m; i++) {
        LivreH* courant = b->T[i];
        while (courant) {
            if (strcmp(courant->titre, titre) == 0) {
                return courant;
            }
            courant = courant->suivant;
        }
    }
    return NULL;
}

void fusionner_bibliosH(BiblioH* b1, BiblioH* b2) {
    for (int i = 0; i < b2->m; i++) {
        LivreH* courant = b2->T[i];
        while (courant) {
            inserer(b1, courant->num, courant->titre, courant->auteur);
            courant = courant->suivant;
        }
    }
    liberer_biblioH(b2);
}

BiblioH* rechercher_exemplairesH(BiblioH* b) {
    BiblioH* res = creer_biblioH(b->m);
    for (int i = 0; i < b->m; i++) {
        for (LivreH* l1 = b->T[i]; l1; l1 = l1->suivant) {
            for (int j = i; j < b->m; j++) {
                for (LivreH* l2 = (i == j) ? l1->suivant : b->T[j]; l2; l2 = l2->suivant) {
                    if (strcmp(l1->titre, l2->titre) == 0 && strcmp(l1->auteur, l2->auteur) == 0) {
                        inserer(res, l1->num, l1->titre, l1->auteur);
                        inserer(res, l2->num, l2->titre, l2->auteur);
                    }
                }
            }
        }
    }
    return res;
}
