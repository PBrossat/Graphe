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



// int Graphe::getVoisinNord(int indice)
// {
//     return indice-this->C;
// }



// int Graphe::getVoisinSud(int indice)
// {
//     return indice+this->C;
// }



// int Graphe::getVoisinOuest(int indice)
// {
//     return indice+1;
// }



// int Graphe::getVoisinEst(int indice)
// {
//     return indice-1;
// }



int Graphe::getAltitude(int indice)
{
    return altitude[indice];
}



int Graphe::getVoisin(int indice , Direction d)
{
    switch (d) 
    {
        case 'NORD':
            return indice-this->C;
        break;

        case 'EST':
            return indice-1;
        break;

        case 'OUEST':
            return indice+1;
        break;

        case 'SUD':
            return indice+this->C;
        break;
    }
}

bool Graphe::voisinExistant(int indice, Direction d)
{
    switch (d) 
    {
        case 'NORD':
            if (getVoisin(indice,d)>=0) //si l'indice du voisin est positif (si il appartient au graphe)
            {
                return true; 
            }else return false; 
        break;

        case 'EST':
            if (getVoisin(indice,d)>=0) //si l'indice du voisin est positif (si il appartient au graphe)
            {
                return true; 
            }else return false; 
        break;

        case 'OUEST':
            if (getVoisin(indice,d)>=0) //si l'indice du voisin est positif (si il appartient au graphe)
            {
                return true; 
            }else return false; 
        break;

        case 'SUD':
            if (getVoisin(indice,d)>=0) //si l'indice du voisin est positif (si il appartient au graphe)
            {
                return true; 
            }else return false; 
        break;
    }
}


void Graphe::modifAltitude(int indice, int nouvelleAltitude)
{
    altitude[indice]=nouvelleAltitude;
}
