#ifndef BIBLIO_LC_H
#define BIBLIO_LC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct {
    Livre *L;  // Premier élément de la liste
} Biblio;

Livre* creer_livre(int num, char* titre, char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);
void afficher_livre(Livre* l);
void afficher_biblio(Biblio *b);
Livre* rechercher_par_num(Biblio* b, int num);
Livre* rechercher_par_titre(Biblio* b, char* titre);
Biblio* rechercher_par_auteur(Biblio* b, char* auteur);
void supprimer_livre(Biblio* b, int num);
void fusionner_biblios(Biblio* b1, Biblio* b2);
Biblio* rechercher_exemplaires(Biblio* b);

#endif 
