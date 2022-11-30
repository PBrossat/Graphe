#ifndef _GRPAHE
#define _GRAPHE
#include "vector"


class Graphe 
{
    public:

    Graphe(int, int, vector<int>);
    
    Graphe(unsigned int nbLignes,unsigned int nbColonnes);

    ~Graphe();

    void modificationAltitudeSommet();

    void affichageGrilleHauteur();

    unsigned int getIndice();

    unsigned int getAltitude();

    Noeud * getVoisinNord(Noeud* noeud);

    Noeud * getVoisinSud(Noeud* noeud);

    Noeud * getVoisinEst(Noeud* noeud);

    Noeud * getVoisinOuest(Noeud* noeud);

    bool voisinExistant(Noeud* noeud, unsigned int voisin);

    private :

    Noeud* noeud; 

    unsigned int tailleGraphe;

    unsigned int nbLignes;

    unsigned int nbColonnes;
    
};
#endif