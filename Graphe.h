#ifndef _GRPAHE
#define _GRAPHE
#include <vector>

class Graphe
{
public:
    Graphe(int , int , vector<int>);
    ~Graphe();
    void modificationAltitudeSommet();
    void affichageGrilleHauteur();
    int getIndice();
    int getAltitude();
    int getVoisinNord();
    int getVoisinSud();
    int getVoisinEst();
    int getVoisinOuest();
    bool voisinExistant(int, int);

private:
    int tailleGraphe;
    int L;
    int C;
};
#endif