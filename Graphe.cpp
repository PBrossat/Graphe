#include "Graphe.h"
#include <iostream>
using namespace std;



// Graphe::Graphe(unsigned int nbLignes,unsigned int nbColonnes)
// {
//     tailleGraphe=nbLignes*nbColonnes;
// }

int Graphe::getIndice(int i, int j)
{
    return i*C+j;
}

int Graphe::getVoisinNord(int indice)
{
    return indice-this->C;
}

int Graphe::getVoisinSud(int indice)
{
    return indice+this->C;
}

int Graphe::getVoisinOuest(int indice)
{
    return indice+1;
}

int Graphe::getVoisinEst(int indice)
{
    return indice-1;
}

