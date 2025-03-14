/* entreeSortieH.h - Gestion des entrées/sorties pour la table de hachage */
#ifndef ENTREE_SORTIE_H_H
#define ENTREE_SORTIE_H_H

#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BiblioH* charger_n_entreesH(char* nomfic, int n, int m);
void enregistrer_biblioH(BiblioH *b, char* nomfic);

#endif
