#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Graphe.h"

void checkData(Graphe a, std::string f, std::vector<int> d, std::vector<std::pair<int, int> > d1)
{
    int cpt = 0;
    if (a.getToutesLesAltitudes().size() != static_cast<unsigned long long>(a.getLigne() * a.getColonne()))
    {
        throw(false);
        return;
    }
    std::ifstream file(f);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            cpt++;
        }
    }
    if (cpt != d.size() || cpt != d1.size())
    {
        throw(false);
        return;
    }
    if (std::find(d.begin(), d.end(), -1) != d.end())
    {
        throw(false);
    }
    for (const auto &e : d1)
    {
        if (e.first == -1)
        {
            throw(false);
            return;
        }
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    Graphe a = Graphe("data.txt");

    std::vector<int> precedent;
    std::vector<double> distance;
    std::vector<int> depart;
    std::vector<std::pair<int, int> > depart2;

    std::string t = "\033[0m";
    std::ifstream file("library.txt");
    if (file.is_open())
    {
        std::string line;
        int cpt = 0;
        int v1, v2, v3;
        while (file >> v1 >> v2 >> v3)
        {
            depart.push_back(a.getIndice(v1, v2));
            depart2.push_back(std::make_pair(a.getIndice(v1, v2), v3));
        }
    }

    try
    {
        checkData(a, "library.txt", depart, depart2);
        std::cout << "****TEST*getIndice()****" << std::endl;
        std::cout << a.getIndice(1, 1) << " "; // Attendu 7
        std::cout << a.getIndice(2, 2) << " "; // Attendu 14
        std::cout << a.getIndice(3, 5) << " "; // Attendu 23
        std::cout << a.getIndice(4, 2) << " "; // Attendu -1
        std::cout << a.getIndice(5, 1) << " "; // Attendu -1
        std::cout << a.getIndice(6, 4) << " "; // Attendu -1
        std::cout << a.getIndice(2, 1) << " "; // Attendu 13
        std::cout << a.getIndice(0, 5) << " "; // Attendu 5
        std::cout << std::endl;

        std::cout << "****TEST*getDistance()****" << std::endl;
        std::cout << a.getDistance(0, SUD) << std::endl;    // Attendu 6,08
        std::cout << a.getDistance(3, NORD) << std::endl;   // Attendu -1
        std::cout << a.getDistance(14, OUEST) << std::endl; // Attendu 1,41

        std::cout << "****TEST*getAltitude()****" << std::endl;
        std::cout << a.getAltitude(22) << " "; // Attendu 23
        std::cout << a.getAltitude(10) << " "; // Attendu 11
        std::cout << a.getAltitude(25) << " "; // Attendu -1
        std::cout << std::endl;

        std::cout << "****TEST*getVoisin()****" << std::endl;
        std::cout << a.getVoisin(10, NORD) << " ";  // Attendu 4
        std::cout << a.getVoisin(10, SUD) << " ";   // Attendu 16
        std::cout << a.getVoisin(10, EST) << " ";   // Attendu 9
        std::cout << a.getVoisin(10, OUEST) << " "; // Attendu 11
        std::cout << a.getVoisin(24, NORD) << " ";  // Attendu -1
        std::cout << a.getVoisin(11, OUEST) << " "; // Attendu -1
        std::cout << a.getVoisin(5, NORD) << " ";   // Attendu -1
        std::cout << a.getVoisin(20, SUD) << " ";   // Attendu -1
        std::cout << a.getVoisin(12, EST) << " ";   // Attendu -1
        std::cout << std::endl;

        std::cout << "****TEST*nombreVoisin()****" << std::endl;
        std::cout << a.nombreVoisin(10) << " "; // Attendu 4
        std::cout << a.nombreVoisin(11) << " "; // Attendu 3
        std::cout << a.nombreVoisin(0) << " ";  // Attendu 2
        std::cout << std::endl;

        std::cout << "****TEST*affichage()****" << std::endl;
        a.affichage();
        std::cout << std::endl;

        std::cout << "****TEST*constructeur***" << std::endl;
        Graphe a1(a);
        a1.affichage();
        std::cout << std::endl;
        Graphe a2 = a1;
        a2.affichage();
        std::cout << std::endl;

        std::cout << "****TEST*Dijkstra*simple****" << std::endl;
        distance.clear();
        precedent.clear();
        std::vector<double> d1 = a.rechercheChemin(0, precedent, distance);
        for (int i = 0; i < d1.size(); i++)
        {
            std::cout << i << ": " << d1[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "****TEST*Dijkstra*MultiSrc****" << std::endl;
        distance.clear();
        precedent.clear();
        std::vector<std::pair<std::vector<int>, std::vector<double> > > d2 = a.rechercheChemin2(depart, precedent, distance);
        for (int i = 0; i < d2.size(); i++)
        {
            for (int j = 0; j < d2[i].first.size() || j < d2[i].second.size(); j++)
            {
                std::cout << "N: " << j << " P: " << d2[i].first[j] << " D: " << d2[i].second[j] << std::endl;
            }
        }
        std::cout << std::endl;

        std::cout << "TEST*Voronoi" << std::endl;
        distance.clear();
        precedent.clear();
        a.voronoi(depart);
        std::cout << std::endl;

        std::cout << t << "**TEST*livraisonVoronoi**" << std::endl;
        distance.clear();
        precedent.clear();
        a.livraisonVoronoi(depart2);
        std::cout << std::endl;
    }
    catch (bool)
    {
        std::cout << "\033[7;31m"
                  << "Données Invalide" << std::endl;
        std::cout << std::endl;
        std::cout << "Le fichier contenant les informations du Graphe doit être sous cette forme: " << std::endl;
        std::cout << "4 5 // nombre de lignes puis nombre de colonnes" << std::endl;
        std::cout << "1 2 3 4 // ALtitudes des L*C sommets listés lignes par lignes du haut vers le bas et de gauche vers la droite" << std::endl;
        std::cout << std::endl;
        std::cout << "Le fichier contenant les informations concernant les différentes library doit être sous cette forme: " << std::endl;
        std::cout << "0 0 10 // coordonnée de la lignes puis de la colonnes du sommet et le cout kilométriques associée à ce sommet" << std::endl;
        std::cout << "Avec Seulement les indications d'une library sur chaque ligne" << std::endl;
        std::cout << std::endl;
    }
    std::cout << t << "END" << std::endl;

    return 0;
}