#pragma once
#ifndef _GRAPHE
#define _GRAPHE
#include <iostream>
#include <vector>

enum Direction
{
    NORD = 0,
    EST = 1,
    SUD = 2,
    OUEST = 3
};

class Graphe
{

public:
    Graphe(int, int, std::vector<int>);
    Graphe(const std::string);
    Graphe(const Graphe &);
    Graphe &operator=(const Graphe &);
    ~Graphe();

    int getIndice(int, int);
    int getAltitude(int);
    int getVoisin(int, Direction);
    void modifAltitude(int, int);
    int nombreVoisin(int);
    bool verifIndice(int);
    double getDistance(int indice1,Direction d);//distance entre 2 indices (indice1 et son voisin via la direction)
    void affichage();

    void rechercheChemin(int depart, std::vector<int> precedent, std::vector<double> distance);
    std::vector<double> rechercheChemin2(std::vector<int> depart, std::vector<int> precedent, std::vector<double> distance);
    void livraison();

private:
    int L;
    int C;
    std::vector<int> altitude;
};
#endif