#ifndef CONNEXE
#define CONNEXE

#include "structGraph.h"


void dfsConnexe(Graphe* graph, int s, int* nonMarque, int* numSommet);
int estConnexe(Graphe* graph);
void afficheEstConnexe(Graphe* graph);

#endif
