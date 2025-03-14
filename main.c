#include "biblioH.h"

#include <time.h>
#include "entreeSortieH.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menu() {
    printf("\nMenu:\n");
    printf("1 - Afficher la bibliothèque\n");
    printf("2 - Ajouter un livre\n");
    printf("3 - Rechercher par numéro\n");
    printf("4 - Rechercher par titre\n");
    printf("5 - Rechercher par auteur\n");
    printf("6 - Supprimer un livre\n");
    printf("7 - Fusionner une autre bibliothèque\n");
    printf("8 - Trouver les ouvrages en double\n");
    printf("0 - Quitter\n");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <fichier bibliothèque> <Nb_lignes_a_lire>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]); 
    int m = 2 * n; // Taille de la table = 2 fois le nombre de lignes lues

   

    BiblioH* B = charger_n_entreesH(argv[1], n, m);
    if (!B) {
        printf("Erreur lors du chargement de la bibliothèque.\n");
        return 1;
    }

    int rep, num;
    char titre[256], auteur[256], buffer[512], autre_fichier[256];

    do {
        menu();
        printf("Votre choix: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &rep) != 1) {
            printf("Erreur : veuillez entrer un nombre valide.\n");
            continue;
        }

        switch (rep) {
            case 1:
                afficher_biblioH(B);
                break;
            case 2:
                printf("Veuillez entrer le numéro, le titre et l'auteur :\n");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%d %255s %255s", &num, titre, auteur) == 3) {
                    inserer(B, num, titre, auteur);
                    printf("Ajout réussi.\n");
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 3:
                printf("Numéro: ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%d", &num) == 1) {
                    afficher_livreH(rechercher_par_numH(B, num));
                } else {
                    printf("Erreur : numéro invalide.\n");
                }
                break;
            case 4:
                printf("Titre: ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%255s", titre) == 1) {
                    afficher_livreH(rechercher_par_titreH(B, titre));
                } else {
                    printf("Erreur : titre invalide.\n");
                }
                break;
            case 5:
                printf("Auteur: ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%255s", auteur) == 1) {
                    afficher_biblioH(rechercher_par_auteurH(B, auteur));
                } else {
                    printf("Erreur : auteur invalide.\n");
                }
                break;
            case 6:
                printf("Numéro: ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%d", &num) == 1) {
                    supprimer_livreH(B, num);
                    printf("Livre supprimé.\n");
                } else {
                    printf("Erreur : numéro invalide.\n");
                }
                break;
            case 7:
                printf("Entrez le fichier de la deuxième bibliothèque: ");
                fgets(autre_fichier, sizeof(autre_fichier), stdin);
                autre_fichier[strcspn(autre_fichier, "\n")] = 0; // Supprimer le \n
                BiblioH* B2 = charger_n_entreesH(autre_fichier, n, m);
                if (!B2) {
                    printf("Erreur : impossible de charger la deuxième bibliothèque.\n");
                } else {
                    fusionner_bibliosH(B, B2);
                    printf("Fusion réalisée avec succès.\n");
                }
                break;
            case 8:
                printf("Ouvrages en double:\n");
                afficher_biblioH(rechercher_exemplairesH(B));
                break;
            case 0:
                printf("Enregistrement et fermeture...\n");
            
                break;
            default:
                printf("Option invalide. Veuillez choisir un nombre entre 0 et 8.\n");
                break;
        }
    } while (rep != 0);

   
    liberer_biblioH(B);
    printf("Merci et au revoir !\n");

   
    return 0;
}