#ifndef _GRPAHE
#define _GRAPHE
#include "Noeud.h"
#include "Element.h"


class Graphe 
{
    public:

    Graphe(unsigned int nbLignes,unsigned int nbColonnes);

    ~Graphe();
    
    void modificationAltitudeSommet();

    void affichageGrilleHauteur();

    unsigned int getIndice();

    unsigned int getAltitude();

    Noeud * getVoisinNord();

    Noeud * getVoisinSud();

    Noeud * getVoisinEst();

    Noeud * getVoisinOuest();

};
#endif