#include "biblioH.h"
#include "biblioLC.h"
#include "entreeSortieH.h"
#include "entreeSortieLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_TABLE 1000

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <fichier bibliothèque>\n", argv[0]);
        return 1;
    }

    FILE *output = fopen("temps_recherche_exemplaires.dat", "w");
    if (!output) {
        printf("Erreur : impossible de créer le fichier de sortie.\n");
        return 1;
    }
    fprintf(output, "Taille_Bibliotheque Temps_Hachage Temps_Liste\n");

    for (int n = 1000; n <= 50000; n *= 2) {
        Biblio* bl = charger_n_entrees(argv[1], n);
        BiblioH* bh = charger_n_entreesH(argv[1], n, TAILLE_TABLE);

        

        if (!bl || !bh) {
            printf("Erreur : impossible de charger %d entrées.\n", n);
            break;
        }

        clock_t start, end;
        double tempsLC, tempsH;

        // Recherche des ouvrages en plusieurs exemplaires - Liste
        start = clock();
        Biblio* resultLC = rechercher_exemplaires(bl);
        end = clock();
        tempsLC = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Recherche des ouvrages en plusieurs exemplaires - Hachage
        start = clock();
        BiblioH* resultH = rechercher_exemplairesH(bh);
        end = clock();
        tempsH = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Taille: %d - Temps (Hachage): %.6f s, Temps (Liste): %.6f s\n", n, tempsLC, tempsH);
        fprintf(output, "%d %.6f %.6f\n", n, tempsLC, tempsH);

        

        // Libération des bibliothèques 
        liberer_biblio(resultLC);
        liberer_biblioH(resultH);
        liberer_biblio(bl);
        liberer_biblioH(bh);
    }

    

    fclose(output);
    printf("Les résultats ont été enregistrés dans temps_recherche_exemplaires.dat\n");
    return 0;
}
