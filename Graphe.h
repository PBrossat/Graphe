#ifndef _GRAPHE
#define _GRAPHE
#include <vector>

class Graphe
{
public:
    Graphe(int, int, vector<int>);
    Graphe(const string);
    ~Graphe();
    void modificationAltitudeSommet();
    void affichageGrilleHauteur();
    int getIndice(int i, int j);
    int getAltitude(int indice);
    int getVoisinNord(int indice);
    int getVoisinSud(int indice);
    int getVoisinEst(int indice);
    int getVoisinOuest(int indice);
    bool voisinExistant(int, int);
    void modifAltitude(int indice, int nouvelleAltitude);
    void affichage() const;
    void rechercheChemin();

private:
    vector<int> altitude;
    int L;
    int C;
};
#endif