/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Etudie la connexité des graphes
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "structGraph.h"


void dfsConnexe(Graphe* graph, int s, int* nonMarque, int* numSommet) {
    /* Fonction récursive pour le parcours dfs pour déterminer la connexité */
    nonMarque[s] = 0;
    *numSommet += 1; // Incrémentation du compteur de sommets parcourus
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                dfsConnexe(graph, t, nonMarque, numSommet);
            }
        }
        if (listeAretes[i].sommet2 == s + 1) {
            t = listeAretes[i].sommet1 - 1;
            if (nonMarque[t]) {
                dfsConnexe(graph, t, nonMarque, numSommet);
            }
        }
    }
}

int estConnexe(Graphe* graph) {
    /* Retourne 1 si le graphe pris en entrée est connexe, 0 sinon */
    int* nonMarque = malloc(graph->nbSommets*sizeof(int));
    int numSommet = 0; // Compteur de sommets parcourus
    if (nonMarque != NULL) {
        for (int i = 0 ; i < graph->nbSommets ; i++) {
            nonMarque[i] = 1;
        }
        dfsConnexe(graph, 0, nonMarque, &numSommet);
        free(nonMarque);
        return (numSommet == graph->nbSommets); // Teste si tous les sommets ont été parcourus par un appel du dfs
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
    return 0;
}

void afficheEstConnexe(Graphe* graph) {
    /* Affiche si un graphe est connexe ou non */
    if (estConnexe(graph)) {
        printf("Le graphe est connexe.\n");
    }
    else {
        printf("Le graphe n'est pas connexe.\n");
    }
}
