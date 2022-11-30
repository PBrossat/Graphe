#ifndef _NOEUD
#define _NOEUD
#include "Element.h"


class Noeud
{
    public:
    Noeud();

    Noeud(const Elem &e);

    ~Noeud();
    //const Noeud* rechercheElement(const Elem &e)const;   
    //Noeud*  insertionElement( const Elem &e);
    //void affichageInfixe()const;
    private:
    
    Elem info;

    Noeud * Nord; 

    Noeud * Sud; 

    Noeud * Est;

    Noeud * Ouest; 

};



#endif