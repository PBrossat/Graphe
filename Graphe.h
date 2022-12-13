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

    int getLigne();
    int getColonne();
    std::vector<int> getToutesLesAltitudes();

    int getIndice(int, int);
    int getAltitude(int);
    int getVoisin(int, Direction);
    void modifAltitude(int, int);
    int nombreVoisin(int);
    bool verifIndice(int);
    double getDistance(int, Direction); // distance entre 2 indices (indice1 et son voisin via la direction)
    void affichage();

    std::vector<double> rechercheChemin(int, std::vector<int>, std::vector<double>);
    std::vector<std::pair<std::vector<int>, std::vector<double> > > rechercheChemin2(std::vector<int>, std::vector<int>, std::vector<double>);
    void voronoi(std::vector<int>);
    void livraisonVoronoi(std::vector<std::pair<int, int> >);

private:
    int L;
    int C;
    std::vector<int> altitude;
};
#endif