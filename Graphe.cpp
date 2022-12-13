#include <fstream>
#include <string>
#include <limits.h>
#include <queue>
#include <utility>
#include <cmath>
#include "Graphe.h"

// Constructeur
// Paramètre: data:string - Fichier contenant les informations du graphes à créer
// Créer un objet graphe
Graphe::Graphe(const std::string data)
{
    std::ifstream file(data); // ouvre le fichier
    if (file.is_open()) 
    {
        std::string line; 
        file >> this->L >> this->C; // L prend la valeur du premier caractère de la première ligne du fichier et C prend la valeur du second caractère de la première ligne du fichier
        int tmp;
        while (file >> tmp) // tant que tmp peut prendre une valeur présente dans le fichier (càd tant que la fin du fichier n'est pas atteinte)
        {
            this->altitude.push_back(tmp); // ajout dans le vector contenant les altitudes la valeur lues dans le fichier
        }
    }
}

// Constucteur par copie
// Paramètres: références vers un Graphe existant
Graphe::Graphe(const Graphe &g)
{
    this->C = g.C;
    this->L = g.L;
    this->altitude = g.altitude;
}

// Surchage de l'opérateur "="
// Paramètres: references vers un Graphes déjà existant
//retourne un graphe
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

// Accesseurs vers le nombre de lignes du Graphe
int Graphe::getLigne()
{
    return this->L;
}

// Accesseurs vers le nombre de colonnes du Graphe
int Graphe::getColonne()
{
    return this->C;
}

// Accesseurs vers le tableau contenant l'altitude de chaque sommet du Graphe
std::vector<int> Graphe::getToutesLesAltitudes()
{
    return this->altitude;
}

// Accesseur de l'indice d'un sommet d'un Graphe
// Paramètres: int i < nombre de lignes du Graphe
//             int j < nombre de colonnes du Graphe
// Retourne: int indice du sommets de coordonnées (i,j)
int Graphe::getIndice(int i, int j)
{
    if (i > this->L - 1 || j > this->C - 1)
    {
        return -1; //retourne une valeur par défaut (-1) en cas d'erreur 
    }
    return i * C + j;
}

// Accesseur de l'altitude d'un sommet
// Paramètre: int indice - indice d'un sommet du Graphe
// Retourne: int - ALtitude du sommet d'indice donné en paramètre
int Graphe::getAltitude(int indice)
{
    if (!this->verifIndice(indice))
    {
        return -1; //retourne une valeur par défaut (-1) en cas d'erreur 
    }
    return this->altitude[indice];
}

// Accesseurs d'un voisin d'un sommet
// Paramètres: int indice - indice du sommet
//             Direction d (NORD, EST, SUD, OUEST)- direction du Voisin
// Retourne: int - indice du voisin
int Graphe::getVoisin(int indice, Direction d)
{
    if (!this->verifIndice(indice))
    {
        return -1; //retourne une valeur par défaut (-1) en cas d'erreur 
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

// Modification de l'altitude d'un sommet
// Paramètre: int indice - indice d'un sommet
//            int nouvelleAltitude - nouvelle Altitude du sommet
void Graphe::modifAltitude(int indice, int nouvelleAltitude)
{
    if (!this->verifIndice(indice))
    {
        return; //l'indice n'existe pas dans le graphe 
    }
    this->altitude[indice] = nouvelleAltitude; //modifie l'altitude de l'indice en question
}

// Accède au nombre de voisins d'un sommet
// Paramètre: int indice - indice d'un sommet
// Retourne: int cpt - compteur indiquant le nombre de voisin
int Graphe::nombreVoisin(int indice)
{
    int cpt = 0;
    for (int i = 0; i < 4; i++) // boucle autour des direction possible(voisin possible)
    {
        if (this->getVoisin(indice, static_cast<Direction>(i)) != -1) // test si le voisin existe
        {
            cpt++; // incrémente le compteur si le voisin i existe 
        }
    }
    return cpt; 
}

// Verifie si l'indice d'un sommet est correct (càd verifie que le sommet existe)
// Paramètre: int indice - indice d'un sommet
// Retourne: booléen - True si le sommet existe dans le Graphe
//                     False si le sommet n'existe pas dans le Graphe
bool Graphe::verifIndice(int indice)
{
    if (indice >= this->L * this->C)
    {
        return false;
    }
    return true;
}

// Accesseur de la distance entre un sommet et un de ses voisins
// Paramètre: int indice - indice d'un sommet
//            Direction d - (NORD, EST, SUD, OUEST) - direction du Voisin
// Retourne: double - Distance entre un sommet et son voisin
double Graphe::getDistance(int indice, Direction d)
{
    if (this->getVoisin(indice, d) != -1) // si le voisin éxiste
    {
        return sqrt(1 + pow(this->getAltitude(indice) - this->getAltitude(this->getVoisin(indice, d)), 2)); // retourne la distance donnée à partir d'une fonction de coût 
    }
    return -1; // sinon retourne une valeur par défaut
}

// Affiche le Graphe dans la console/terminal 
void Graphe::affichage()
{
    for (int i = 0; i < this->L; i++) //boucle ligne 
    {
        for (int j = 0; j < this->C; j++) //boucle colonne
        {
            int tmp = this->getIndice(i, j);
            std::cout << "(" << tmp << "," << this->altitude[tmp] << ") "; //affiche le couple (indice,altitude )
        }
        std::cout << std::endl;
    }
}

// Fonction de recherche du plus court chemin à partir d'UN unique sommet 
// Paramètre: int depart -indice du sommet indiquant le départ de la recherche
//            vector<int> précédent - vector stockant le précédent de chaque sommet durant la recherche
//            vector<double> distance - vector stockant les distances entre les sommets
// Retourne: vector<double> distance- vector contenant les distances entre les sommets
std::vector<double> Graphe::rechercheChemin(int depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i = 0; i < (this->L * this->C); i++) // parcours de tous les noeuds
    {
        precedent.push_back(i);                                      // convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); // valeur par défaut infini pour la distance
    }
    precedent[depart] = depart; // le précedent du sommet de départ est lui-même 
    distance[depart] = 0; // met la priorité du sommet de départ à 0

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > F; // création file à priorité nommé F trier par  ordre croissant
    F.push(std::make_pair(distance[depart], depart));  // insertion du tuple (paire) distance[depart]/depart dans la file à prio F (la priorité se fait sur distance et pas départ)

    while (!F.empty()) // tant que F n'est pas vide
    {
        int n;
        n = F.top().second; // n prend l'indice du PREMIER (via top()) sommet (deuxieme valeur du couple) de la file de priorité => distance min
        F.pop();            // supression du Premier élément de la file de priorité
        for (int i = 0; i < 4; i++) //parcour pour chaque voisin (4 voisins possibles)
        {
            int tmp = this->getVoisin(n, static_cast<Direction>(i)); 
            if (tmp != -1) // si i est voisin de n (different de -1 => existe)
            {
                double distanceVoisin = distance[tmp];
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

// Fonction de recherche du plus court chemin à partir d'un tableau de sommet (correspondant aux librairies)
// Paramètre: vector<int> depart - vector d'indice de multiples sommets indiquant le départ de la recherche
//            vector<int> précédent - vector stockant le précédent de chaque sommet durant la recherche
//            vector<double> distance - vector stockant les distance entre les sommets
// Retourne: vector<pair<vector<int>, vector<double>>> res - vector contenant les précédent des sommets et les distances entre les sommets
std::vector<std::pair<std::vector<int>, std::vector<double> > > Graphe::rechercheChemin2(std::vector<int> depart, std::vector<int> precedent, std::vector<double> distance)
{
    for (int i = 0; i < (this->L * this->C); i++) // parcours de tous les noeuds
    {
        precedent.push_back(i);                                      // convention : le precedent d'un noeud est lui même
        distance.push_back(std::numeric_limits<double>::infinity()); // valeur infini pour la distance
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
    std::vector<std::pair<std::vector<int>, std::vector<double> > > res; //création du tableau resultat 
    res.push_back(std::make_pair(precedent, distance)); //res est un tableau de couple (précedent[],distance[])
    return res;
}

// Procédure d'affichage de Voronoi
// Paramètre: vector<int> depart - vector d'indices indiquant l'indices des sommets de départ
void Graphe::voronoi(std::vector<int> depart)
{
    std::vector<std::pair<std::string, int> > res; // vector stockant le résultat à afficher
    for (int i = 0; i < (this->L * this->C); i++) //parcours de tous les sommets 
    {
        res.push_back(std::make_pair(" ", i)); // remplissage du tableau avec des valeurs par défaut 
    }
    std::string color = " "; // valeur par défaut de color 
    std::string c2 = std::to_string(std::rand() % 3); // c2 => valeur indiquant la physique de la police (%3 => 3 valeurs possibles)
    for (int i = 0; i < depart.size(); i++) //boucle dans tableau de librairies 
    {
        std::string c1; 
        for (const auto &e : res) //itération autour des éléments de res 
        {
            while (e.first == color) // tant que color est présent dans res 
            {
                c1 = std::to_string(std::rand() % 8); // c1=> valeur indiquant la couleur de la librairie  (%8 => 8 valeurs possibles)
                color = "\033[" + c2 + ";3" + c1 + "m"; // affectation d'une valeur à color (chaque zone aura une couleur différentes) 
            }
        }
        res[depart[i]] = std::make_pair(color, depart[i]); // stockage de l'indice colorée dans le vector res
    }

    std::vector<int> precedent;
    std::vector<double> distance;
    std::vector<std::pair<std::vector<int>, std::vector<double> > > tmp = this->rechercheChemin2(depart, precedent, distance); // réalisation de la recherche de chemin
    for (int i = 0; i < tmp.size(); i++) //parcours du tableau tmp (resultat de rechercheChemin2)
    {
        for (int j = 0; j < tmp[i].first.size(); j++) // parcours le tableau de precedent
        {
            int tmp1 = j;
            while (tmp1 != tmp[i].first[tmp1]) // Tant que le précédent n'est pas lui-même
            {
                tmp1 = tmp[i].first[tmp1]; // rechercher le précédent du sommets étudiée
            }
            res[j] = std::make_pair(res[tmp1].first, j); // stockage de l'indice coloré dans le vector résultat
        }
    }
    std::cout << "Library:"
              << " ";
    for (int i = 0; i < depart.size(); i++)
    {
        std::cout << depart[i] << " ";
    } //affichage des indices où les librairies se trouvent 
    std::cout << std::endl;
    for (int i = 0; i < res.size(); i++)
    {
        if (i % this->C == 0)
        {
            std::cout << std::endl;
        }
        std::cout << res[i].first << res[i].second << " "; // affichage du vector resultat (res[i].first => couleur , res[i].second => indice)
    }
}

// Fonction affichant Voronoi pour une fonction de coût différente
// Paramètre: vector<pair<int,int>> - vector indiquant les sommets de départs de la recherche et leur coût kilométrique
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
                color = "\033[" + c2 + ";3" + c1 + "m";
            }
        }
        res[depart[i].first] = std::make_pair(color, depart[i].first);
    }

    //idem processus que rechercheChemin2
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

        while (!F.empty()) 
        {
            int n;
            n = F.top().second;
            F.pop();
            for (int j = 0; j < 4; j++)
            {
                int tmp = this->getVoisin(n, static_cast<Direction>(j));
                if (tmp != -1)
                {
                    double distanceVoisin = distance[tmp];
                    double distance_n = distance[n];
                    double dnv = distance_n + (depart[i].second * this->getDistance(n, static_cast<Direction>(j))); // changement de la fonction de coût
                    //depart[i].second => coût kilométrique associé à la librairie 
                    //depart[i].first => indice de la librairie 
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
    
    //idem que Voronoi 
    for (int i = 0; i < precedent.size(); i++)
    {
        int tmp = i;
        while (tmp != precedent[tmp])
        {
            tmp = precedent[tmp];
        }
        res[i] = std::make_pair(res[tmp].first, i);
    }
    std::cout << "Library:"
              << " ";
    for (int i = 0; i < depart.size(); i++)
    {
        std::cout << depart[i].first << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < res.size(); i++)
    {
        if (i % this->C == 0)
        {
            std::cout << std::endl;
        }
        std::cout << res[i].first << res[i].second << " ";
    }
}
