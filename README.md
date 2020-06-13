# DFS
Algorithme de parcours en profondeur et ses applications en C

## Installation
Clonez le projet :
```bash
git clone https://github.com/Quentin18/DFS.git
```

Générez la librairie statique *libgraph* :
```bash
cd src
make
```

Générez l'exécutable *graphAnalyzer* :
```bash
cd ..
make
```

## Utilisation
L'exécutable *graphAnalyzer* établit différentes analyses sur des graphes au format *.txt* et génère des fichiers *.dot*. Pour l'utiliser :
```bash
./graphAnalyzer <nomFichier> <orientation>
```
Où :

- *nomFichier* correspond au nom du fichier *.txt* à analyser sans l'extension *.txt*
- *orientation* vaut 1 si le graphe est orienté et 0 sinon

**Exemple :**
```bash
./graphAnalyzer graphs/graph-1 0
```

## Graphes
Vous trouverez différents graphes au format *.txt* dans le répertoire *graphs*. Par convention, les fichiers nommés *digraph* sont des graphes orientés et *graph* sont non orientés. Ces fichiers sont organisés comme suit :

- Ligne 1 : nombre de sommets
- Ligne 2 : nombre d'arêtes
- Lignes suivantes : arêtes entre deux sommets

Dans le cas où le graphe est orienté, l'ordre des deux sommets est important.

## Fonctionnalités
Voici la liste des fonctionnalités de la librairie *libgraph* :

* Exportation d'un graphe au format *.dot*
* Inversion d'un graphe orienté
* Parcours DFS avec visualisation en *.dot*
* Connexité et composantes fortement connexes
* Détermination d'une orientation forte

## Exemples
**Graphe orienté : digraph-1**

* Graphe au format *.dot* :

![](https://github.com/Quentin18/DFS/blob/master/img/digraph-1.png)

* Graphe inverse :

![](https://github.com/Quentin18/DFS/blob/master/img/digraph-1-inv.png)

* Parcours DFS :

![](https://github.com/Quentin18/DFS/blob/master/img/digraph-1-dfs.png)

* Composantes fortement connexes :

![](https://github.com/Quentin18/DFS/blob/master/img/digraph-1-cfc.png)

**Graphe non orienté : graph-k**

* Graphe au format *.dot* :

![](https://github.com/Quentin18/DFS/blob/master/img/graph-k.png)

* Détermination d'une orientation forte :

![](https://github.com/Quentin18/DFS/blob/master/img/graph-k-ort.png)

* Vérification de la forte connexité avec les composantes fortement connexes :

![](https://github.com/Quentin18/DFS/blob/master/img/graph-k-cfc.png)

## Exportation des .dot
Les fichiers *.dot* peuvent être exportés grâce à *graphviz* aux formats *.png*, *.svg* et *.eps*. Pour cela, voici les commandes :

```bash
dot -Tpng filename.dot -o filename.png
dot -Tsvg filename.dot -o filename.svg
dot -Tps filename.dot -o filename.eps
```

## Contact
Quentin Deschamps: quentindeschamps18@gmail.com

## Licence
[MIT](https://choosealicense.com/licenses/mit/)
