/**
 * \author Quentin Deschamps
 * \date 2020
 *
 * Analyse d'un graphe
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgraph.h"


void analyseGraphe(char const *nomFichier, int const oriente) {
    /* Effectue l'analyse complète du graphe stocké dans un fichier .txt */
    char txt[5], dot[5], inv[10], dfs[10], cfc[10], ort[10];
    char fichiertxt[50], fichierdot[50], fichierinv[50], fichierdfs[50], fichiercfc[50], fichierort[50];
    strcpy(txt, ".txt");
    strcpy(fichiertxt, nomFichier);
    strcat(fichiertxt, txt);
    strcpy(dot, ".dot");
    strcpy(fichierdot, nomFichier);
    strcat(fichierdot, dot);
    strcpy(inv, "-inv.dot");
    strcpy(fichierinv, nomFichier);
    strcat(fichierinv, inv);
    strcpy(dfs, "-dfs.dot");
    strcpy(fichierdfs, nomFichier);
    strcat(fichierdfs, dfs);
    strcpy(cfc, "-cfc.dot");
    strcpy(fichiercfc, nomFichier);
    strcat(fichiercfc, cfc);
    strcpy(ort, "-ort.dot");
    strcpy(fichierort, nomFichier);
    strcat(fichierort, ort);
    printf("\n========== Analyse du fichier : %s ==========\n", fichiertxt);
    // Importation graphe
    Graphe* graph = importationGraphe(fichiertxt, oriente);
    if (graph != NULL) {
        // Exportation du graphe en .dot
        exportationDot(graph, fichierdot);
        // Cas où le graphe est orienté
        if (oriente) {
            // Création du graphe inverse
            Graphe* graphInverse = inverseGraphe(graph);
            // Exportation du graphe inverse en .dot
            exportationDot(graphInverse, fichierinv);
            // Affichage du dfs dans le terminal
            afficheParcoursDfs(graph);
            // Exportation du dfs en .dot
            creeParcoursDfsCouleur(graph, fichierdfs);
            // Affiche si le graphe est connexe ou non dans le terminal
            afficheEstConnexe(graph);
            // Exporte les composantes fortement connexes en .dot et affichage dans le terminal
            CFC(graph, fichiercfc, "paired12");
            liberationMemoire(graphInverse);
        }
        // Cas où le graphe est non orienté : détermination d'une orientation forte
        else {
            // Affiche dans le terminal si le graphe est sans pont
            afficheEstSansPont(graph);
            printf("Détermination d'une orientation forte...\n");
            // Création du graphe fortement orienté
            Graphe* graphOrienteFort = orientationForte(graph); 
            // Si une orientation forte existe (sans pont)
            if (graphOrienteFort != NULL) {
                printf("Orientation forte déterminée !\n");
                // Exportation du graphe fortement orienté en .dot
                exportationDot(graphOrienteFort, fichierort);
                // Affichage du parcours dfs du graphe fortement orienté dans le terminal
                afficheParcoursDfs(graphOrienteFort);
                // Exportation du dfs du graphe fortement orienté en .dot
                creeParcoursDfsCouleur(graphOrienteFort, fichierdfs);
                // Affiche si le graphe fortement orienté est connexe ou non dans le terminal
                // (normalement toujours oui)
                afficheEstConnexe(graphOrienteFort);
                // Exporte les composantes fortement connexes du graphe fortement orienté en .dot
                // (normalement toujours une seule classe)
                CFC(graphOrienteFort, fichiercfc, "paired12");
                liberationMemoire(graphOrienteFort);
            }
        }
        liberationMemoire(graph);
    }
    else {
        printf("L'importation du graphe a échoué !\n");
    }
    printf("========== Fin analyse fichier : %s ==========\n\n", fichiertxt);
}

int main(int argc, char const *argv[]) {
    if (argc == 3) {
        analyseGraphe(argv[1], (int)strtol(argv[2], NULL, 10));
    }
    else {
        printf("Pas assez d'arguments :\n");
        printf("./graphAnalyzer <nomFichier> <orientation>\n");
    }
    return 0;
}
