/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Détermination d'une orientation forte des graphes non orientés
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "importGraph.h"
#include "connexeGraph.h"


void echangeAretes(Arete* listeAretes, int i, int j) {
    /* Echange 2 arêtes d'une liste d'arêtes aux indices i et j */
    int sommet1_tmp, sommet2_tmp;
    sommet1_tmp = listeAretes[i].sommet1;
    sommet2_tmp = listeAretes[i].sommet2;
    listeAretes[i].sommet1 = listeAretes[j].sommet1;
    listeAretes[i].sommet2 = listeAretes[j].sommet2;
    listeAretes[j].sommet1 = sommet1_tmp;
    listeAretes[j].sommet2 = sommet2_tmp;
}

int estSansPont(Graphe* graph, int affichage) {
    /* Retourne 1 si le graphe est sans pont, 0 sinon */
    int i;
    Graphe* graphPartiel = malloc(sizeof(Graphe));
    if (graphPartiel != NULL) {
        graphPartiel->nbSommets = graph->nbSommets;
        graphPartiel->oriente = graph->oriente;
        graphPartiel->nbAretes = graph->nbAretes - 1; // Une arête de moins que le graphe
        Arete* listeAretes = malloc(graph->nbAretes*sizeof(Arete));
        if (listeAretes != NULL) {
            for (i = 0 ; i < graph->nbAretes ; i++) {
                listeAretes[i].sommet1 = graph->listeAretes[i].sommet1;
                listeAretes[i].sommet2 = graph->listeAretes[i].sommet2;
            }
            graphPartiel->listeAretes = listeAretes; // Même liste d'arêtes que le graphe
            for (i = 0 ; i < graph->nbAretes ; i++) {
                echangeAretes(graphPartiel->listeAretes, i, graph->nbAretes - 1); // On met en fin de liste l'arête à supprimer
                if (!estConnexe(graphPartiel)) { // Etudie la connexité sans prendre en compte la dernière arête de la liste
                    if (affichage) {
                        printf(
                            "L'arête %d -- %d est un pont !\n",
                            graphPartiel->listeAretes[graph->nbAretes - 1].sommet1,
                            graphPartiel->listeAretes[graph->nbAretes - 1].sommet2);
                    }
                    liberationMemoire(graphPartiel);
                    return 0;
                }
                echangeAretes(graphPartiel->listeAretes, i, graph->nbAretes - 1); // On rééchange pour remettre la liste à l'état initial
            }
            liberationMemoire(graphPartiel);
            return 1;
        }
        else {
            free(graphPartiel);
            printf("Erreur d'allocation de mémoire !\n");
        }
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
    return 0;
}

void afficheEstSansPont(Graphe* graph) {
    /* Affiche si un graphe est sans pont ou non */
    if (estSansPont(graph, 1)) {
        printf("Le graphe est sans pont.\n");
    }
    else {
        printf("Le graphe possède au moins un pont.\n");
    }
}

void dfsOrientationForte(Graphe* graph, int s, int* nonMarque, int* numArete, Arete* listeAretesFortes, int* aretesUtilise) {
    /* Fonction récursive pour le parcours dfs pour déterminer l'orientation forte */
    nonMarque[s] = 0;
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                listeAretesFortes[*numArete].sommet1 = listeAretes[i].sommet1;
                listeAretesFortes[*numArete].sommet2 = listeAretes[i].sommet2;
                aretesUtilise[i] = 1;
                *numArete += 1;
                dfsOrientationForte(graph, t, nonMarque, numArete, listeAretesFortes, aretesUtilise);
            }
            if (!aretesUtilise[i]) { // Si l'arête n'a pas été ajoutée (cas où le dfs recule)
                listeAretesFortes[*numArete].sommet1 = listeAretes[i].sommet1;
                listeAretesFortes[*numArete].sommet2 = listeAretes[i].sommet2;
                aretesUtilise[i] = 1;
                *numArete += 1;
            }
        }
        else if (listeAretes[i].sommet2 == s + 1) {
            t = listeAretes[i].sommet1 - 1;
            if (nonMarque[t]) {
                listeAretesFortes[*numArete].sommet1 = listeAretes[i].sommet2;
                listeAretesFortes[*numArete].sommet2 = listeAretes[i].sommet1;
                aretesUtilise[i] = 1;
                *numArete += 1;
                dfsOrientationForte(graph, t, nonMarque, numArete, listeAretesFortes, aretesUtilise);
            }
            if (!aretesUtilise[i]) { // Si l'arête n'a pas été ajoutée (cas où le dfs recule)
                listeAretesFortes[*numArete].sommet1 = listeAretes[i].sommet2;
                listeAretesFortes[*numArete].sommet2 = listeAretes[i].sommet1;
                aretesUtilise[i] = 1;
                *numArete += 1;
            }
        }
    }
}

Graphe* orientationForte(Graphe* graph) {
    /* Détermine une orientation forte d'un graphe non orienté et retourne ce graphe */
    if (estSansPont(graph, 0)) { // Orientation forte seulement si le graphe est sans pont
        Graphe* graphOrientForte = malloc(sizeof(Graphe)); // Création du graphe fortement orienté
        if (graphOrientForte != NULL) {
            graphOrientForte->nbSommets = graph->nbSommets;
            graphOrientForte->oriente = 1;
            graphOrientForte->nbAretes = graph->nbAretes;
            Arete* listeAretesFortes = malloc(graphOrientForte->nbAretes*sizeof(Arete));
            int* nonMarque = malloc(graph->nbSommets*sizeof(int));
            int* aretesUtilise = malloc(graph->nbAretes*sizeof(int)); // Liste qui indique si les arêtes ont été orientés
            if (listeAretesFortes != NULL && nonMarque != NULL && aretesUtilise != NULL) {
                int i;
                for (i = 0 ; i < graph->nbSommets ; i++) {
                    nonMarque[i] = 1;
                }
                for (i = 0 ; i < graph->nbAretes ; i++) {
                    aretesUtilise[i] = 0;
                }
                int numArete = 0;
                for (i = 0 ; i < graph->nbSommets ; i++) {
                    dfsOrientationForte(graph, i, nonMarque, &numArete, listeAretesFortes, aretesUtilise);
                }
                free(nonMarque);
                free(aretesUtilise);
                graphOrientForte->listeAretes = listeAretesFortes;
                return graphOrientForte; // Retourne le graphe fortement orienté
            }
            else {
                free(graphOrientForte);
                printf("Erreur d'allocation de mémoire !\n");
            }
        }
        else {
            printf("Erreur d'allocation de mémoire !\n");
        }
    }
    else {
        printf("Le graphe n'est pas sans pont : pas d'orientation forte !\n");
    }
    return NULL;
}
