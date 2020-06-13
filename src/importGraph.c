/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Importation des graphes et exportation en .dot
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "structGraph.h"


Graphe* importationGraphe(char* nomFichier, int oriente) {
    /* Importe un graphe écrit dans un fichier .txt */
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        Graphe* graph = malloc(sizeof(Graphe));
        if (graph != NULL) {
            fscanf(fichier, "%d", &graph->nbSommets);
            fscanf(fichier, "%d", &graph->nbAretes);
            graph->oriente = oriente;
            graph->listeAretes = malloc(graph->nbAretes*sizeof(Arete));
            if (graph->listeAretes != NULL) {
                for (int i = 0 ; i < graph->nbAretes ; i++) {
                    fscanf(fichier, "%d", &graph->listeAretes[i].sommet1);
                    fscanf(fichier, "%d", &graph->listeAretes[i].sommet2);
                }
            }
            else {
                fclose(fichier);
                printf("Erreur d'allocation de mémoire !\n");
                return NULL;
            }
        }
        else {
            fclose(fichier);
            printf("Erreur d'allocation de mémoire !\n");
            return NULL;
        }
        fclose(fichier);
        printf("Importation du graphe du fichier %s réussie !\n", nomFichier);
        return graph;
    }
    else {
        printf("Impossible d'ouvrir le fichier %s !\n", nomFichier);
    }
    return NULL;
}

void affichageInformations(Graphe* graph) {
    /* Affiche les informations d'un graphe */
    printf("Nombre de sommets : %d\n", graph->nbSommets);
    printf("Nombre d'arêtes : %d\n", graph->nbAretes);
    printf("Orienté : %d\n", graph->oriente);
    printf("Liste des arêtes :\n");
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        printf("%d -- %d\n", graph->listeAretes[i].sommet1, graph->listeAretes[i].sommet2);
    }
}

void exportationDot(Graphe* graph, char* nomFichier) {
    /* Exporte un graphe sous le format .dot */
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w");
    char symbole;
    int i;
    if (fichier != NULL) {
        if (graph->oriente) {
            fprintf(fichier, "digraph mon_graphe {"); // Première ligne pour un graphe orienté
            symbole = '>'; // Symbole pour créer les arcs
        }
        else {
            fprintf(fichier, "graph mon_graphe {"); // Première ligne pour un graphe non orienté
            symbole = '-'; // Symbole pour créer les arêtes
        }
        for (i = 0 ; i < graph->nbSommets ; i++) { // Ecriture des sommets
            fprintf(fichier, "\n\t%d;", i + 1);
        }
        for (i = 0 ; i < graph->nbAretes ; i++) { // Ecriture des arêtes
            fprintf(fichier, "\n\t%d -%c %d;", graph->listeAretes[i].sommet1, symbole, graph->listeAretes[i].sommet2);
        }
        fprintf(fichier, "\n}");
        fclose(fichier);
        printf("Le fichier %s a été créé.\n", nomFichier);
    }
    else {
        printf("Impossible de créer le fichier %s !\n", nomFichier);
    }
}

void liberationMemoire(Graphe* graph) {
    /* Libère la mémoire occupée par un graphe */
    free(graph->listeAretes);
    free(graph);
}
