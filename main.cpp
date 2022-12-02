#include <fstream>
#include <string>
#include "Graphe.h"

int main()
{
    Graphe a = Graphe("data.txt");
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

    std::cout << "END" << std::endl;
    return 0;
}