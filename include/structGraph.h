#ifndef STRUCT
#define STRUCT

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

#endif
