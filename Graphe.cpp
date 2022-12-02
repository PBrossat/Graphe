#include <fstream>
#include <string>
#include "Graphe.h"
// using namespace std;

Graphe::Graphe(const std::string data)
{
    std::ifstream file(data);
    if (file.is_open())
    {
        std::string line;
        file >> this->L >> this->C;
        int tmp;
        while (file >> tmp)
        {
            this->altitude.push_back(tmp);
        }
    }
    if (this->altitude.size() != (static_cast<unsigned long long>(this->L * this->C)))
    {
        std::cout << "Donnée Invalide" << std::endl;
    }
}

Graphe::Graphe(const Graphe &g)
{
    this->C = g.C;
    this->L = g.L;
    this->altitude = g.altitude;
}

Graphe &Graphe::operator=(const Graphe &g)
{
    if (this == &g)
    {
        return *this;
    }
    Graphe grph(g);
    return grph;
}

Graphe::~Graphe()
{
}

int Graphe::getIndice(int i, int j)
{
    if (i > this->L - 1 || j > this->C - 1)
    {
        return -1;
    }
    return i * C + j;
}

int Graphe::getAltitude(int indice)
{
    if (!this->verifIndice(indice))
    {
        return -1;
    }
    return this->altitude[indice];
}

int Graphe::getVoisin(int indice, Direction d)
{
    if (!this->verifIndice(indice))
    {
        return -1;
    }
    switch (d)
    {
    case NORD:
        if (indice / this->C == 0)
        {
            return -1;
        }
        return indice - this->C;
        break;

    case EST:
        if (indice % this->C == 0)
        {
            return -1;
        }
        return indice - 1;
        break;

    case OUEST:
        if (indice % this->C == this->C - 1)
        {
            return -1;
        }
        return indice + 1;
        break;

    case SUD:
        if (indice / this->C == this->L - 1)
        {
            return -1;
        }
        return indice + this->C;
        break;
    }
}

void Graphe::modifAltitude(int indice, int nouvelleAltitude)
{
    if (!this->verifIndice(indice))
    {
        return;
    }
    this->altitude[indice] = nouvelleAltitude;
}

int Graphe::nombreVoisin(int indice)
{
    int cpt = 0;
    for (int i = 0; i < 4; i++)
    {
        if (this->getVoisin(indice, static_cast<Direction>(i)) != -1)
        {
            cpt++;
        }
    }
    return cpt;
}

bool Graphe::verifIndice(int indice)
{
    if (indice >= this->L * this->C)
    {
        return false;
    }
    return true;
}

void Graphe::affichage()
{
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->C; j++)
        {
            int tmp = this->getIndice(i, j);
            std::cout << "(Indice: " << tmp << ", Altitude: " << this->altitude[tmp] << ") ";
        }
        std::cout << std::endl;
    }
}