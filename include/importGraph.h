#ifndef IMPORT
#define IMPORT

#include "structGraph.h"


Graphe* importationGraphe(char* nomFichier, int oriente);
void affichageInformations(Graphe* graph);
void exportationDot(Graphe* graph, char* nomFichier);
void liberationMemoire(Graphe* graph);

#endif
