#include <fstream>
#include <string>
#include <limits.h>
#include <queue>
#include <utility>
#include <cmath>
#include "Graphe.h"

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

// Accesseurs vers le nombre de ligne du Graphe
int Graphe::getLigne()
{
    return this->L;
}

// Accesseurs vers le nombre de colonnes du Graphe
int Graphe::getColonne()
{
    return this->C;
}

// Accesseurs vers le tableau contenant l'altitude de chaque sommets du Graphe
std::vector<int> Graphe::getToutesLesAltitudes()
{
    return this->altitude;
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

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > F; // création file à priorité nommé F trier par  ordre croissant
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
// Retourne: vector<pair<vector<int>, vector<double>>> res - vector contenant les précédent des sommetes et les distances entre les sommets
std::vector<std::pair<std::vector<int>, std::vector<double> > > Graphe::rechercheChemin2(std::vector<int> depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i = 0; i < (this->L * this->C); i++) // parcours de tous les noeuds
    {
        precedent.push_back(i);                                      // convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); // valeur infini pour la distance
        // depart.push_back(i); //ajout de tous les noeuds dans départ
    }

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > F; // création file à priorité nommé F => ordre décroissant

    for (int i = 0; i < depart.size(); i++)
    {
        distance[depart[i]] = 0;
        precedent[depart[i]] = depart[i];
        F.push(std::make_pair(distance[depart[i]], depart[i])); // insertion du tuple (paire) distance[depart]/depart dans la file à prio F (la priorité se fait sur distance et pas départ)

        while (!F.empty()) // tant que F n'est pas vide
        {
            int n;
            n = F.top().second; // n prend la valeur du PREMIER sommet (deuxieme valeur du couple) de la file de priorité => distance min
            F.pop();            // supression du Premier élément de la file de priorité
            for (int j = 0; j < 4; j++)
            {
                int tmp = this->getVoisin(n, static_cast<Direction>(j));
                if (tmp != -1) // si i est voisin de n (different de -1 => existe)
                {
                    double distanceVoisin = distance[tmp];
                    // this->getDistance(depart,static_cast<Direction>(i)); //distance entre n et son voisin i
                    double distanceN = distance[n];
                    double dnv = distanceN + this->getDistance(n, static_cast<Direction>(j)); // dnv est le coût (distance noeud de depart + distance avec le voisin i)
                    if (dnv < distanceVoisin)
                    {
                        distance[tmp] = dnv;
                        precedent[tmp] = n;
                        F.push(std::make_pair(dnv, tmp));
                    }
                }
            }
        }
    }
    std::vector<std::pair<std::vector<int>, std::vector<double> > > res;
    res.push_back(std::make_pair(precedent, distance));
    return res;
}

// Fonction d'affichage de Voronoi
// Paramètre: vector<int> depart - vector d'indices indiquant l'indices des sommets de départ
void Graphe::voronoi(std::vector<int> depart)
{
    std::vector<std::pair<std::string, int> > res; // vector stokant le resultat à afficher
    for (int i = 0; i < (this->L * this->C); i++)
    {
        res.push_back(std::make_pair(" ", i)); // remplissage du tableau
    }
    std::string color = " ";
    std::string c2 = std::to_string(std::rand() % 3);
    for (int i = 0; i < depart.size(); i++)
    {
        std::string c1;
        for (const auto &e : res)
        {
            while (e.first == color)
            {
                c1 = std::to_string(std::rand() % 8);
                // c2 = std::to_string(std::rand() % 3);
                color = "\033[" + c2 + ";3" + c1 + "m";
            }
        }
        res[depart[i]] = std::make_pair(color, depart[i]); // stockage de l'indice colorée dans le vector res
    }
    std::vector<int> precedent;
    std::vector<double> distance;
    std::vector<std::pair<std::vector<int>, std::vector<double> > > tmp = this->rechercheChemin2(depart, precedent, distance); // réalisation de la recherche de chemin
    for (int i = 0; i < tmp.size(); i++)
    {
        for (int j = 0; j < tmp[i].first.size(); j++)
        {
            int tmp1 = j;
            while (tmp1 != tmp[i].first[tmp1]) // Tant que le precedent n'est pas lui-même
            {
                tmp1 = tmp[i].first[tmp1]; // rechercher le précendent du sommets étudiée
            }
            res[j] = std::make_pair(res[tmp1].first, j); // stockage de l'indice coloré dans le vector résultat
        }
    }
    for (int i = 0; i < res.size(); i++)
    {
        if (i % this->C == 0)
        {
            std::cout << std::endl;
        }
        std::cout << res[i].first << res[i].second << " "; // affichage du vector resultat
    }
}

// Fonction affichant Voronoi pour une fonction de cout différentes
// Paramètre: vector<pair<int,int>> - vector indiquant les sommets de départ de la recherche et leur cout kilométriques
void Graphe::livraisonVoronoi(std::vector<std::pair<int, int> > depart)
{
    std::vector<std::pair<std::string, int> > res;
    for (int i = 0; i < (this->L * this->C); i++)
    {
        res.push_back(std::make_pair(" ", i));
    }
    std::string color = " ";
    std::string c2 = std::to_string(std::rand() % 3);
    for (int i = 0; i < depart.size(); i++)
    {
        std::string c1;
        for (const auto &e : res)
        {
            while (e.first == color)
            {
                c1 = std::to_string(std::rand() % 8);
                // c2 = std::to_string(std::rand() % 3);
                color = "\033[" + c2 + ";3" + c1 + "m";
            }
        }
        res[depart[i].first] = std::make_pair(color, depart[i].first);
    }
    std::vector<int> precedent;
    std::vector<double> distance;
    for (int i = 0; i < (this->L * this->C); i++)
    {
        precedent.push_back(i);
        distance.push_back(std::numeric_limits<double>::infinity());
    }
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > F;
    for (int i = 0; i < depart.size(); i++)
    {
        distance[depart[i].first] = 0;
        precedent[depart[i].first] = depart[i].first;
        F.push(std::make_pair(distance[depart[i].first], depart[i].first));

        while (!F.empty()) // while the queue is not empty
        {
            int n;
            n = F.top().second;
            F.pop();
            for (int j = 0; j < 4; j++)
            {
                int tmp = this->getVoisin(n, static_cast<Direction>(j));
                if (tmp != -1)
                {
                    double distanceNeighbour = distance[tmp];
                    double distance_n = distance[n];
                    double dnv = distance_n + (depart[i].second * this->getDistance(n, static_cast<Direction>(j))); // changement de la fonction de cout
                    if (dnv < distanceNeighbour)
                    {
                        distance[tmp] = dnv;
                        precedent[tmp] = n;
                        F.push(std::make_pair(dnv, tmp));
                    }
                }
            }
        }
    }
    for (int i = 0; i < precedent.size(); i++)
    {
        int tmp = i;
        while (tmp != precedent[tmp])
        {
            tmp = precedent[tmp];
        }
        res[i] = std::make_pair(res[tmp].first, i);
    }
    for (int i = 0; i < res.size(); i++)
    {
        if (i % this->C == 0)
        {
            std::cout << std::endl;
        }
        std::cout << res[i].first << res[i].second << " ";
    }
}
