#ifndef BIBLIO_H_H
#define BIBLIO_H_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livreh {
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table {
    int nE;
    int m;
    LivreH **T;
} BiblioH;

int fonctionClef(char* auteur);
int fonctionHachage(int cle, int m);
LivreH* creer_livreH(int num, char* titre, char* auteur);
void liberer_livreH(LivreH* l);
BiblioH* creer_biblioH(int m);
void liberer_biblioH(BiblioH* b);
void inserer(BiblioH* b, int num, char* titre, char* auteur);
void afficher_livreH(LivreH* l);
void afficher_biblioH(BiblioH* b);
LivreH* rechercher_par_numH(BiblioH* b, int num);
LivreH* rechercher_par_titreH(BiblioH* b, char* titre);
void fusionner_bibliosH(BiblioH* b1, BiblioH* b2);
BiblioH* rechercher_par_auteurH(BiblioH* b, char* auteur);
void supprimer_livreH(BiblioH* b, int num);
BiblioH* rechercher_exemplairesH(BiblioH* b);

#endif