/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Parcours dfs en affichage console et exportation en .dot
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "structGraph.h"


void dfsAffiche(Graphe* graph, int s, int* nonMarque) {
    /* Fonction récursive pour le parcours dfs qui affiche les sommets */
    nonMarque[s] = 0;
    if (s != 0) {
        printf(" -> %d", s + 1);
    }
    else {
        printf("%d", s + 1);
    }
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                dfsAffiche(graph, t, nonMarque);
            }
        }
    }
}

void afficheParcoursDfs(Graphe* graph) {
    /* Affiche le parcours dfs d'un graphe en console */
    int* nonMarque = malloc(graph->nbSommets*sizeof(int));
    int i;
    if (nonMarque != NULL) {
        printf("Parcours en profondeur : ");
        for (i = 0 ; i < graph->nbSommets ; i++) { // initialisation de la liste nonMarque
            nonMarque[i] = 1;
        }
        for (i = 0 ; i < graph->nbSommets ; i++) {
            if (nonMarque[i]) {
                dfsAffiche(graph, i, nonMarque);
            }
        }
        printf("\n");
        free(nonMarque);
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
}

void exportationDotDfs(Graphe* graph, char* nomFichier, int* color, int* step) {
    /* Exporte un graphe sous le format .dot en montrant un parcours dfs
    L'argument color correspond à un pointeur sur la liste des arêtes à colorer (liste de 1 et 0 : 1 si à colorer 0 sinon)
    L'argument step contient la liste avec le numéro de l'étape du dfs pour chaque arête (0 si l'arête n'est pas traversée par le dfs) */
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w");
    char symbole;
    int i;
    if (fichier != NULL && color != NULL) {
        if (graph->oriente) {
            fprintf(fichier, "digraph mon_graphe {"); // Première ligne pour un graphe orienté
            symbole = '>'; // Symbole pour créer les arcs
        }
        else {
            fprintf(fichier, "graph mon_graphe {"); // Première ligne pour un graphe non orienté
            symbole = '-'; // Symbole pour créer les arêtes
        }
        fprintf(fichier, "\n\tlabel=\"Parcours dfs\";");
        for (i = 0 ; i < graph->nbSommets ; i++) { // Ecriture des sommets
            fprintf(fichier, "\n\t%d;", i + 1);
        }
        for (i = 0 ; i < graph->nbAretes ; i++) { // Ecriture des arêtes
            if (color[i]) { // Cas où l'arête est traversée par le dfs -> à colorer
                fprintf(fichier, "\n\t%d -%c %d [color=blue, penwidth=3.0, label=\"Step %d\"];", graph->listeAretes[i].sommet1, symbole, graph->listeAretes[i].sommet2, step[i]);
            }
            else { // Cas où l'arête n'est pas traversée par le dfs -> en noir
                fprintf(fichier, "\n\t%d -%c %d [color=gray];", graph->listeAretes[i].sommet1, symbole, graph->listeAretes[i].sommet2);
            }
        }
        fprintf(fichier, "\n}");
        fclose(fichier);
    }
    else {
        printf("Impossible de créer le fichier %s !\n", nomFichier);
    }
}

void dfsCouleur(Graphe* graph, int s, int* nonMarque, int* color, int* step, int* numStep) {
    /* Fonction récursive pour le parcours dfs en remplissant les couleurs des arêtes */
    nonMarque[s] = 0;
    Arete* listeAretes = graph->listeAretes;
    int t;
    for (int i = 0 ; i < graph->nbAretes ; i++) {
        if (listeAretes[i].sommet1 == s + 1) {
            t = listeAretes[i].sommet2 - 1;
            if (nonMarque[t]) {
                color[i] = 1; // L'arête à l'indice i doit être colorée
                step[i] = *numStep;
                *numStep += 1;
                dfsCouleur(graph, t, nonMarque, color, step, numStep);
            }
        }
    }
}

void creeParcoursDfsCouleur(Graphe* graph, char* nomFichier) {
    /* Crée le parcours dfs d'un graphe en l'exportant en .dot*/
    int* nonMarque = malloc(graph->nbSommets*sizeof(int));
    int* color = malloc(graph->nbAretes*sizeof(int));
    int* step = malloc(graph->nbAretes*sizeof(int));
    int i;
    int numStep = 1;
    if (nonMarque != NULL && color != NULL && step != NULL) {
        for (i = 0 ; i < graph->nbSommets ; i++) { // Initialisation de la liste nonMarque
            nonMarque[i] = 1;
        }
        for (i = 0 ; i < graph->nbAretes ; i++) { // Initialisation des listes color et step
            color[i] = 0;
            step[i] = 0;
        }
        for (i = 0 ; i < graph->nbSommets ; i++) {
            if (nonMarque[i]) {
                dfsCouleur(graph, i, nonMarque, color, step, &numStep);
            }
        }
        free(nonMarque);
        exportationDotDfs(graph, nomFichier, color, step); // Création l'arbre dfs en .dot
        free(color);
        free(step);
        printf("Le fichier %s montrant le parcours dfs a été créé.\n", nomFichier);
    }
    else {
        printf("Erreur d'allocation de mémoire !\n");
    }
}
