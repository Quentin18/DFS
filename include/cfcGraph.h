#ifndef CFC
#define CFC

#include "structGraph.h"
#include "importGraph.h"
#include "inverseGraph.h"


void dfsPostOrdre(Graphe* graph, int s, int* nonMarque, int* postOrdre, int* numSommet);
void dfsClasse(Graphe* graph, int s, int* nonMarque, int* classe, int numClasse);
void exportationDotCFC(Graphe* graph, char* nomFichier, int* classe, char* paletteCouleurs);
void CFC(Graphe* graph, char* nomFichier, char* paletteCouleurs);

#endif
