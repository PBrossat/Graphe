# Graphe

    Lien vers le projet : https://forge.univ-lyon1.fr/p2002218/brossat_savigny

# Contributeurs : 

    p2002218 Brossat Pierrick 
    p1935618 Savigny Henri


# Présentation Graphe :

    Ce projet consiste à manipuler des graphes de tailles variables constitués d'entiers représentants des sommets où des librairies peuvent y siéger. 
    Ce projet est constitué de trois grosses fonctions étant: rechercheChemin, Voronoi et livraisonVoronoi.

    La première consiste à trouver le chemin le plus court d'un sommet de départ jusqu'aux autres sommets du graphe. Chaque paire de sommets est associée à un unique chemin (étant le plus court possible entre ceux-ci).

    La seconde permet de visualiser les différentes zones selon l'altitudes des librairies, elle permet de savoir rapidement dans quelle zone géographique se trouve chaque sommet. Si un sommet est de la même couleur qu'une librairie alors celui-ci est plus proche de cette librairie que des autres.

    Enfin, la troisieme est basée sur le même principe que la fonction Voronoi mais indique les zones selon une fonction de coût differente de la premiere.



# Compilation 

Pour compiler, utiliser la commande make suivante: 

    ~/Projet$ make

Qui permet de crée l'éxecutable utile à notre projet. 



# Arborescence

	Brossat_Savigny/
	├─ Graphe.h // Définition des fonctions du graphe
    ├─ Graphe.cpp // Implémentation des fonctions du graphe 
    ├─ main.cpp // Programme principal
    ├─ graphe.txt // Correspond aux informations concernant le graphe
    ├─ library.txt // Correspond aux informations les librairies présentes dans le graphe
    ├─ Makefile // Permet la compilation du projet
    ├─ Readme.md // Vous y êtes 



# Utilisation

Le projet permet de créer l'éxecutable suivant :

## /main:
    Cet exécutable permet de lancer le programme.

    Pour le lancer :
		~/Projet$ ./main


# Format des fichiers 
    ## Le fichier graphe.txt doit ressembler à cela:
    4 6           // Dimensions du graphe L (largeur) et H (hauteur)
    1 2 3 ..     //Altitudes des L*H sommets listés ligne par ligne
                // (du haut vers le bas et de gauche vers la droite)


    ## Le fichier librairy.txt doit ressembler à cela:
    0 0 10           // Coordonnées de la ligne, de la colonne et du coût de livraison/kilomètre dans l'ordre 
    ...             // (du haut vers le bas et de gauche vers la droite)
    ...            // (chaque ligne correspond aux informations d'une et une seule librairie)