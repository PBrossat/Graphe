#include <fstream>
#include <string>
#include "Graphe.h"
#include <limits.h>
#include <queue>
#include <utility>
#include <cmath>
#include <ctgmath>


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

double Graphe::getDistance(int indice,Direction d)
{   
    if(this->getVoisin(indice,d)!=-1) //si mle voisin d existe 
    {
        return sqrt(1+pow(this->getAltitude(indice)-this->getAltitude(this->getVoisin(indice,d)),2)); //retourne la distance 
    }
    return -1; //sinon retourne une valeur par défaut 
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



void Graphe::rechercheChemin(int depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i=0; i<(this->L*this->C); i++) //parcours de tous les noeuds 
    {
        precedent.push_back(i); //convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); //valeur infini pour la distance 
    }
    precedent[depart]=depart;
    distance[depart]=0;

    std::priority_queue< std::pair<double,int>, std::vector<std::pair<double,int> >, std::greater<std::pair <double,int> > > F; //création file à priorité nommé F => ordre décroissant 
    F.push(std::make_pair(distance[depart],depart)); // insertion du tuple (paire) distance[depart]/depart dans la file à prio F (la priorité se fait sur distance et pas départ)
    
    while (!F.empty()) //tant que F n'est pas vide 
    {
        int n;
        n=F.top().second; // n prend la valeur du PREMIER sommet (deuxieme valeur du couple) de la file de priorité => distance min
        F.pop(); //supression du Premier élément de la file de priorité
        for (int i=0; i<4; i++)
        {
            if (this->getVoisin(n, static_cast<Direction>(i)) != -1) // si i est voisin de n (different de -1 => existe)
            {
                double distanceVoisin= distance[this->getVoisin(n, static_cast<Direction>(i))]; 
                //this->getDistance(depart,static_cast<Direction>(i)); //distance entre n et son voisin i 
                double distanceN = distance[n];
                double dnv = distanceN + this->getDistance(n,static_cast<Direction>(i)); //dnv est le coût (distance noeud de depart + distance avec le voisin i)
                if (dnv < distanceVoisin)
                {
                    distance[this->getVoisin(n, static_cast<Direction>(i))]=dnv;
                    precedent[this->getVoisin(n, static_cast<Direction>(i))]=n;
                    F.push(std::make_pair(dnv, this->getVoisin(n, static_cast<Direction>(i))));
                }
            }
            std::cout<<"Pas de voisin :" <<static_cast<Direction>(i)<<std::endl;
        }
    }
    for (int i=0; i<(this->L*this->C); i++)
    {
        std::cout<<i<<" "<<distance[i]<<std::endl;
    }
}