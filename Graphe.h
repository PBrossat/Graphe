#ifndef _GRAPHE
#define _GRAPHE
#include <vector>

class Graphe
{
public:
    Graphe(int, int, vector<int>);
    Graphe(string);
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
    vector<int> altitude;
    int L;
    int C;
};
#endif