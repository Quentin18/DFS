/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Inversion des graphes
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "structGraph.h"


Graphe* inverseGraphe(Graphe* graph) {
    /* Retourne l'inverse d'un graphe orienté */
    Graphe* graphInverse = malloc(sizeof(Graphe));
    if (graph != NULL) {
        graphInverse->nbSommets = graph->nbSommets;
        graphInverse->nbAretes = graph->nbAretes;
        graphInverse->oriente = 1;
        Arete* listeAretes = malloc(graphInverse->nbAretes*sizeof(Arete));
        if (listeAretes != NULL) {
            for (int i = 0 ; i < graphInverse->nbAretes ; i++) { // Inverse toutes les arêtes
                listeAretes[i].sommet1 = graph->listeAretes[i].sommet2;
                listeAretes[i].sommet2 = graph->listeAretes[i].sommet1;
            }
            graphInverse->listeAretes = listeAretes;
            return graphInverse;
        }
        else {
            printf("Erreur d'allocation de mémoire !\n");
        }
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
    return NULL;
}
