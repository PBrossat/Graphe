#include <fstream>
#include <string>
#include "Graphe.h"
#include <limits.h>
#include <queue>
#include <utility>
#include <cmath>
#include <ctgmath>

// Constructeur
// Paramètre: data Fichier contenant les informations du graphes à créer
// Créer un objet graphe
Graphe::Graphe(const std::string data)
{
    std::ifstream file(data); // ouvre le fichier
    if (file.is_open())
    {
        std::string line;
        file >> this->L >> this->C; // L prend la valeur du premier caractères de la première lignes du fichier et C prend la valeur du second caractères de premère ligne du fichiers
        int tmp;
        while (file >> tmp) // tant que tmp peut prendre une valeur présente dans le fichier (cad tant que la fin du fichier n'est pas atteinte)
        {
            this->altitude.push_back(tmp); // ajout dans le vector contenant les altitudes la valeur lues dans le fichier
        }
    }
    if (this->altitude.size() != (static_cast<unsigned long long>(this->L * this->C))) // verifie que les données entrée dans le fichier sont correctes
    {
        std::cout << "Donnée Invalide" << std::endl;
    }
}

// Constucteur par copie
// Paramètres: références vers un Graphes existant
Graphe::Graphe(const Graphe &g)
{
    this->C = g.C;
    this->L = g.L;
    this->altitude = g.altitude;
}

// Surchage de l'opérateur "="
// Paramètres: references vers un Graphes déjà existant
Graphe &Graphe::operator=(const Graphe &g)
{
    if (this == &g)
    {
        return *this;
    }
    Graphe grph(g);
    return grph;
}

// Destructeur
Graphe::~Graphe()
{
}

// Accesseur de l'indice d'un sommets d'un Graphes
// Paramètres: int i < nombre de lignes du Graphes
//             int j < nombre de colonnes du Graphes
// Retourne: int indice du sommets de coordonnées (i,j)
int Graphe::getIndice(int i, int j)
{
    if (i > this->L - 1 || j > this->C - 1)
    {
        return -1;
    }
    return i * C + j;
}

// Accesseur de l'altitude d'un sommets
// Paramètre: int indice - indice d'un sommets du Graphes
// Retourne: int - ALtitude du sommets d'indice donnée en paramètres
int Graphe::getAltitude(int indice)
{
    if (!this->verifIndice(indice))
    {
        return -1;
    }
    return this->altitude[indice];
}

// Accesseurs d'un voisin d'un sommets
// Paramètres: int indice - indice du sommets
//             Direction d (NORD, EST, SUD, OUEST° - direction du Voisin
// Retourne: int - indice du voisin
int Graphe::getVoisin(int indice, Direction d)
{
    if (!this->verifIndice(indice))
    {
        return -1;
    }
    switch (d)
    {
    case NORD:
        if (indice / this->C == 0) // Verification de l'existence du voisin au NORD
        {
            return -1;
        }
        return indice - this->C;
        break;

    case EST:
        if (indice % this->C == 0) // Verification de l'existence du voisin au EST
        {
            return -1;
        }
        return indice - 1;
        break;

    case OUEST:
        if (indice % this->C == this->C - 1) // Verification de l'existence du voisin au OUEST
        {
            return -1;
        }
        return indice + 1;
        break;

    case SUD:
        if (indice / this->C == this->L - 1) // Verification de l'existence du voisin au SUD
        {
            return -1;
        }
        return indice + this->C;
        break;
    }
}

// Setter d'une nouvelle altitude
// Paramètre: int indice - indice d'un sommet
//            int nouvelleAltitude - nouvelle Altitude du sommet
void Graphe::modifAltitude(int indice, int nouvelleAltitude)
{
    if (!this->verifIndice(indice))
    {
        return;
    }
    this->altitude[indice] = nouvelleAltitude;
}

// Accède aux nombre de voisin d'un sommet
// Paramètre: int indice - indice d'un sommet
// Retourne: int cpt - compteur indiquant le nombre de voisin
int Graphe::nombreVoisin(int indice)
{
    int cpt = 0;
    for (int i = 0; i < 4; i++) // boucle autour des direction possible(voisin possible)
    {
        if (this->getVoisin(indice, static_cast<Direction>(i)) != -1) // test si le voisin existe
        {
            cpt++; // count le voisin si il existe
        }
    }
    return cpt;
}

// Verifie si l'indice d'un sommet est correct (cad verifie que le sommets existe)
// Paramètre: int indice - indice d'un sommet
// Retourne: boolean - True si le sommet existe dans le Graph
//                     False si le sommet n'existe pas dans le Graphe
bool Graphe::verifIndice(int indice)
{
    if (indice >= this->L * this->C)
    {
        return false;
    }
    return true;
}

// Accesseurs de la distance entre un sommet et un de ses voisins
// Paramètre: int indice - indice d'un sommet
//            Direction d - (NORD, EST, SUD, OUEST° - direction du Voisin
// Retourne: double - Distance entre un sommet et son voisin
double Graphe::getDistance(int indice, Direction d)
{
    if (this->getVoisin(indice, d) != -1) // si mle voisin d existe
    {
        return sqrt(1 + pow(this->getAltitude(indice) - this->getAltitude(this->getVoisin(indice, d)), 2)); // retourne la distance
    }
    return -1; // sinon retourne une valeur par défaut
}

// Affiche le Graphe dans la console
void Graphe::affichage()
{
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->C; j++)
        {
            int tmp = this->getIndice(i, j);
            std::cout << "(" << tmp << "," << this->altitude[tmp] << ") ";
        }
        std::cout << std::endl;
    }
}

// Fonction de recherche du plus court chemin
// Paramètre: int depart -indice du sommet indiquan le départ de la recherche
//            vector<int> précédent - vector stokant le précédant de chaque sommets durant la recherche
//            vector<double> distance - vector stokant les distance entre les sommets
// Retourne: vector<double> distance- vector contenant les distances entre les sommets
std::vector<double> Graphe::rechercheChemin(int depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i = 0; i < (this->L * this->C); i++) // parcours de tous les noeuds
    {
        precedent.push_back(i);                                      // convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); // valeur infini pour la distance
    }
    precedent[depart] = depart;
    distance[depart] = 0; // met la priorité du sommets de départ à 0

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> F; // création file à priorité nommé F trier par  ordre croissant
    F.push(std::make_pair(distance[depart], depart));                                                                         // insertion du tuple (paire) distance[depart]/depart dans la file à prio F (la priorité se fait sur distance et pas départ)

    while (!F.empty()) // tant que F n'est pas vide
    {
        int n;
        n = F.top().second; // n prend la valeur du PREMIER sommet (deuxieme valeur du couple) de la file de priorité => distance min
        F.pop();            // supression du Premier élément de la file de priorité
        for (int i = 0; i < 4; i++)
        {
            int tmp = this->getVoisin(n, static_cast<Direction>(i));
            if (tmp != -1) // si i est voisin de n (different de -1 => existe)
            {
                double distanceVoisin = distance[tmp];
                // this->getDistance(depart,static_cast<Direction>(i)); //distance entre n et son voisin i
                double distanceN = distance[n];
                double dnv = distanceN + this->getDistance(n, static_cast<Direction>(i)); // dnv est le coût (distance noeud de depart + distance avec le voisin i)
                if (dnv < distanceVoisin)
                {
                    distance[tmp] = dnv;
                    precedent[tmp] = n;
                    F.push(std::make_pair(dnv, tmp));
                }
            }
        }
    }
    return distance;
}

// Fonction de recherche du plus court chemin
// Paramètre: vector<int> depart - vector d'indice de multiples sommet indiquant le départ de la recherche
//            vector<int> précédent - vector stokant le précédant de chaque sommets durant la recherche
//            vector<double> distance - vector stokant les distance entre les sommets
// Retourne: vector<double> distance- vector contenant les distances entre les sommets
std::vector<double> Graphe::rechercheChemin2(std::vector<int> depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i = 0; i < (this->L * this->C); i++) // parcours de tous les noeuds
    {
        precedent.push_back(i);                                      // convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); // valeur infini pour la distance
        // depart.push_back(i); //ajout de tous les noeuds dans départ
    }

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> F; // création file à priorité nommé F => ordre décroissant

    for (int i = 0; i < depart.size(); i++)
    {
        distance[depart[i]] = 0;
        precedent[depart[i]] = depart[i];
        F.push(std::make_pair(distance[depart[i]], depart[i])); // insertion du tuple (paire) distance[depart]/depart dans la file à prio F (la priorité se fait sur distance et pas départ)
    }

    while (!F.empty()) // tant que F n'est pas vide
    {
        int n;
        n = F.top().second; // n prend la valeur du PREMIER sommet (deuxieme valeur du couple) de la file de priorité => distance min
        F.pop();            // supression du Premier élément de la file de priorité
        for (int i = 0; i < 4; i++)
        {
            int tmp = this->getVoisin(n, static_cast<Direction>(i));
            if (tmp != -1) // si i est voisin de n (different de -1 => existe)
            {
                double distanceVoisin = distance[tmp];
                // this->getDistance(depart,static_cast<Direction>(i)); //distance entre n et son voisin i
                double distanceN = distance[n];
                double dnv = distanceN + this->getDistance(n, static_cast<Direction>(i)); // dnv est le coût (distance noeud de depart + distance avec le voisin i)
                if (dnv < distanceVoisin)
                {
                    distance[tmp] = dnv;
                    precedent[tmp] = n;
                    F.push(std::make_pair(dnv, tmp));
                }
            }
        }
    }
    return distance;
}

void Graphe::voronoi()
{
}

void livraisonVoironoi()
{
}