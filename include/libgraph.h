#ifndef LIBGRAPH
#define LIBGRAPH

typedef struct arete {
    int sommet1;
    int sommet2;
} Arete;

typedef struct graphe {
    int nbSommets;
    int nbAretes;
    int oriente; // 1 si orienté, 0 si non-orienté
    Arete* listeAretes;
} Graphe;

// cfcGraph
void dfsPostOrdre(Graphe* graph, int s, int* nonMarque, int* postOrdre, int* numSommet);
void dfsClasse(Graphe* graph, int s, int* nonMarque, int* classe, int numClasse);
void exportationDotCFC(Graphe* graph, char* nomFichier, int* classe, char* paletteCouleurs);
void CFC(Graphe* graph, char* nomFichier, char* paletteCouleurs);

// connexeGraph
void dfsConnexe(Graphe* graph, int s, int* nonMarque, int* numSommet);
int estConnexe(Graphe* graph);
void afficheEstConnexe(Graphe* graph);

// dfsGraph
void dfsAffiche(Graphe* graph, int s, int* nonMarque);
void afficheParcoursDfs(Graphe* graph);
void exportationDotDfs(Graphe* graph, char* nomFichier, int* color);
void dfsCouleur(Graphe* graph, int s, int* nonMarque, int* color);
void creeParcoursDfsCouleur(Graphe* graph, char* nomFichier);

// importGraph
Graphe* importationGraphe(char* nomFichier, int oriente);
void affichageInformations(Graphe* graph);
void exportationDot(Graphe* graph, char* nomFichier);
void liberationMemoire(Graphe* graph);

// inverseGraph
Graphe* inverseGraphe(Graphe* graph);

// orientForteGraph
void echangeAretes(Arete* listeAretes, int i, int j);
int estSansPont(Graphe* graph, int affichage);
void afficheEstSansPont(Graphe* graph);
Graphe* orientationForte(Graphe* graph);

#endif
