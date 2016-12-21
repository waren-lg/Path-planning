#ifndef GRAPHE_HPP
#define GRAPHE_HPP
#include <limits>
#include <vector>
#include "obstacle.hpp"
#include "arc.hpp"

template <class T>
class graphe
{public:
    vector<arc<T> > A ;

    graphe() ;
    graphe(const arc<T> & a) ;
    graphe(const graphe<T> & G) ;
    void print()
    {
        for (int i = 0; i < A.size(); i++)
        {
            A[i].print() ;
        }
    }

};

template <class T>
graphe<T>::graphe()           //Constructeur par défaut
{
    A = vector<arc<T> >(0) ;
}

template <class T>
graphe<T>::graphe(const arc<T> & a)   //Constructeur avec valeurs
{
    A = vector<arc<T> >(a) ;
}

template <class T>
graphe<T>::graphe(const graphe<T> & G)   //Constructeurs par copie
{
    A = vector<arc<T> >(G.A) ;
}




#endif

