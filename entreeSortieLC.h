#ifndef ENTREE_SORTIE_LC_H
#define ENTREE_SORTIE_LC_H

#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Biblio* charger_n_entrees(char* nomfic, int n);
void enregistrer_biblio(Biblio *b, char* nomfic);

#endif 
