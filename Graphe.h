#ifndef _GRAPHE
#define _GRAPHE
#include <vector>

class Graphe
{

enum Direction 
{
    NORD=0,
    EST=1,
    SUD=2,
    OUEST=3
};

    
public:

    Graphe(int, int, vector<int>);
    Graphe(const string);
    ~Graphe();
    void affichageGrilleHauteur();
    int getIndice(int i, int j);
    int getAltitude(int indice);
    int getVoisinNord(int indice);
    int getVoisinSud(int indice);
    int getVoisinEst(int indice);
    int getVoisinOuest(int indice);
    bool voisinExistant(int indice,Direction);
    void modifAltitude(int indice, int nouvelleAltitude);
    void affichage() const;
    void rechercheChemin();
    void livraison();
    void nombreVoisin(int indice);

private:
    vector<int> altitude;
    int L;
    int C;

};
#endif