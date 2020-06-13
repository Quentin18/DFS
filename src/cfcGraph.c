/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Détermine les composantes fortement connexes des graphes et exportation en .dot pour visualisation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "importGraph.h"
#include "inverseGraph.h"


void dfsPostOrdre(Graphe* graph, int s, int* nonMarque, int* postOrdre, int* numSommet) {
    /* Fonction récursive pour le parcours dfs
    Génère le post-ordre du parcours dfs */
    nonMarque[s] = 0;
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                dfsPostOrdre(graph, t, nonMarque, postOrdre, numSommet);
                postOrdre[*numSommet] = t + 1;
                *numSommet += 1;
            }
        }
    }
}

void dfsClasse(Graphe* graph, int s, int* nonMarque, int* classe, int numClasse) {
    /* Fonction récursive pour le parcours dfs
    Indique la classe CFC de chaque sommet */
    nonMarque[s] = 0;
    classe[s] = numClasse;
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                dfsClasse(graph, t, nonMarque, classe, numClasse);
            }
        }
    }
}

void exportationDotCFC(Graphe* graph, char* nomFichier, int* classe, char* paletteCouleurs) {
    /* Exporte un graphe sous le format .dot en montrant les CFC */
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w");
    char symbole;
    int i;
    if (fichier != NULL) {
        if (graph->oriente) {
            fprintf(fichier, "digraph mon_graphe {");
            symbole = '>';
        }
        else {
            fprintf(fichier, "graph mon_graphe {");
            symbole = '-';
        }
        fprintf(fichier, "\n\tlabel=\"Composantes fortement connexes\";");
        int numSommet = 0;
        int numClasse = 1;
        while (numSommet < graph->nbSommets) {
            fprintf(fichier, "\n\tsubgraph cluster_%d {", numClasse);
            fprintf(fichier, "\n\t\tlabel=\"Classe %d\";", numClasse);
            for (i = 0 ; i < graph->nbSommets ; i++) {
                if (classe[i] == numClasse) {
                    fprintf(fichier, "\n\t\t%d [colorscheme=%s, color=%d];", i + 1, paletteCouleurs, classe[i]);
                    numSommet++;
                }
            }
            fprintf(fichier, "\n\t}");
            numClasse++;
        }
        for (i = 0 ; i < graph->nbAretes ; i++) {
            fprintf(fichier, "\n\t%d -%c %d [color=gray];", graph->listeAretes[i].sommet1, symbole, graph->listeAretes[i].sommet2);
        }
        fprintf(fichier, "\n}");
        fclose(fichier);
    }
    else {
        printf("Impossible de créer le fichier %s !\n", nomFichier);
    }
}

void CFC(Graphe* graph, char* nomFichier, char* paletteCouleurs) {
    /* Affiche les composantes fortement connexes d'un graphe dans un fichier .dot */
    int* nonMarque = malloc(graph->nbSommets*sizeof(int));
    int* postOrdre = malloc(graph->nbSommets*sizeof(int));
    int* classe = malloc(graph->nbSommets*sizeof(int)); // Numéro de classe d'équivalence de chaque sommet
    int numSommet = 0;
    int numClasse = 1;
    int i;
    if (nonMarque != NULL && postOrdre != NULL && classe != NULL) {
        for (i = 0 ; i < graph->nbSommets ; i++) { // Initialisation des listes nonMarque et classe
            nonMarque[i] = 1;
            classe[i] = 0;
        }
        for (i = 0 ; i < graph->nbSommets ; i++) { // Parcours dfs pour générer le post-ordre
            if (nonMarque[i]) {
                dfsPostOrdre(graph, i, nonMarque, postOrdre, &numSommet);
                postOrdre[numSommet] = i + 1;
                numSommet += 1;
            }
        }
        printf("Détermination des classes fortement connexes :\n");
        printf("\tPost-ordre : ");
        for (i = 0 ; i < graph->nbSommets ; i++) {
            printf("%d", postOrdre[i]);
            if (i < graph->nbSommets - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        for (i = 0 ; i < graph->nbSommets ; i++) { // Réinitialisation de la liste nonMarque
            nonMarque[i] = 1;
        }
        Graphe* graphInverse = inverseGraphe(graph); // Création du graphe inverse
        if (graphInverse != NULL) {
            for (i = graphInverse->nbSommets - 1 ; i >= 0 ; i--) { // Parcours suivant le post-ordre inverse
                if (nonMarque[postOrdre[i] - 1]) {
                    dfsClasse(graphInverse, postOrdre[i] - 1, nonMarque, classe, numClasse);
                    numClasse += 1;
                }
            }
            printf("\tNuméro de classe des sommets : ");
            for (i = 0 ; i < graph->nbSommets ; i++) {
                printf("\n\tSommet %d : %d", i + 1, classe[i]);
            }
            printf("\n");
            exportationDotCFC(graph, nomFichier, classe, paletteCouleurs); // Exportation des CFC en .dot pour meilleure visualisation
            liberationMemoire(graphInverse);
        }
        free(nonMarque);
        free(postOrdre);
        free(classe);
        printf("Le fichier %s montrant les composantes fortement connexes a été créé.\n", nomFichier);
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
}
