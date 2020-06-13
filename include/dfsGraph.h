#ifndef DFS
#define DFS

#include "structGraph.h"


void dfsAffiche(Graphe* graph, int s, int* nonMarque);
void afficheParcoursDfs(Graphe* graph);
void exportationDotDfs(Graphe* graph, char* nomFichier, int* color);
void dfsCouleur(Graphe* graph, int s, int* nonMarque, int* color);
void creeParcoursDfsCouleur(Graphe* graph, char* nomFichier);

#endif
