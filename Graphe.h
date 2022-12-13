#pragma once
#ifndef _GRAPHE
#define _GRAPHE
#include <iostream>
#include <vector>

enum Direction //enumération des directions possibles 
{
    NORD = 0,
    EST = 1,
    SUD = 2,
    OUEST = 3
};

class Graphe
{

public:
    // Graphe(int, int, std::vector<int>); constructeur de graphe
    Graphe(const std::string); //constructeur d'un graphe à partir d'un fichier 
    Graphe(const Graphe &); //constructeur par copie d'un graphe à partir d'un autre 
    Graphe &operator=(const Graphe &); //surcharge de l'opérateur =
    ~Graphe(); //destructeur du graphe

    //Accesseurs :
    int getLigne(); // permet d'accéder au nombre de lignes du graphe (L)
    int getColonne();// permet d'accéder au nombre de colonnes du graphe (C)
    std::vector<int> getToutesLesAltitudes(); //accède au tableau des altitudes des sommets

    //méthode utile
    int getIndice(int, int); // permet d'accéder à l'indice à partir de coordonnées i*j
    int getAltitude(int); // permet d'accéder à l'altitude à partir d'un indice donné 
    int getVoisin(int, Direction); // permet d'accéder à l'indice d'un voisin (si il existe) 
    void modifAltitude(int, int); // permet de modifier l'altitude d'un sommet
    int nombreVoisin(int); // renvoie le nombre de voisins d'un sommet 
    bool verifIndice(int); // verifie qu'un sommet est présent dans le graphe 
    double getDistance(int, Direction); // distance entre 2 indices (indice1 et son voisin via la direction)
    void affichage();

    //fonctions de recherches de chemins (coeur du projet)
    std::vector<double> rechercheChemin(int, std::vector<int>, std::vector<double>); //permet d'éxécuter l'algorithme de Dijkstra sur UN seul sommet 
    std::vector<std::pair<std::vector<int>, std::vector<double> > > rechercheChemin2(std::vector<int>, std::vector<int>, std::vector<double>);// permet d'éxécuter l'algorithme de Dijkstra sur un ou plusieurs sommets (un tableau de sommets) 
    void voronoi(std::vector<int>); // affichage de zones de couleurs en fonctions du résultat de rechercheChemin2
    void livraisonVoronoi(std::vector<std::pair<int, int> >); // idem que voronoi mais avec une fonction de coût/valuation differentes (implémentée directement dans la fonction)

private:
    int L; // ligne
    int C; // colonne
    std::vector<int> altitude; //tableau d'altitudes
};
#endif