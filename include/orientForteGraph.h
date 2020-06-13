#ifndef ORIENT
#define ORIENT

#include "importGraph.h"
#include "connexeGraph.h"


void echangeAretes(Arete* listeAretes, int i, int j);
int estSansPont(Graphe* graph, int affichage);
void afficheEstSansPont(Graphe* graph);
Graphe* orientationForte(Graphe* graph);

#endif
