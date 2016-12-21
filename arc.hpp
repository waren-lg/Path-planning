#ifndef ARC_HPP_INCLUDED
#define ARC_HPP_INCLUDED
#include "Point.hpp"
#include "arcplanification.hpp"

template <class T>
class arc
{   public :
        Point<T> s1;
        Point<T> s2;
        T poids;

        arc();
        arc(const Point<T> & u, const Point<T> & v);
        arc(const arc<T> & u);
        arc & operator=(const arc<T> & u);
        int operator==(const arc<T> & u) ;
        void print()
        {
            s1.print() ;
            s2.print() ;
        }
};

template <class T>
arc<T>::arc()
{
    s1.x = 0;
    s1.y = 0;
    s2.x = 0;
    s2.y = 0;
    poids=0;
}

template <class T>
arc<T>::arc(const Point<T> & u, const Point<T> & v)
{
    s1=u;
    s2=v;
    poids = s1.distance(s2) ;
}

//constructeur par copie
template <class T>
arc<T>::arc(const arc & u)
{
    s1=u.s1;
    s2=u.s2;
    poids=u.poids;
}

//opérateur d'égalité
template <class T>
arc<T> & arc<T>::operator=(const arc<T> & u )
{
    s1=u.s1;
    s2=u.s2;
    poids=u.poids;
    return *this;
}

template <class T>
int arc<T>::operator==(const arc<T> & u)
{
    if ((s1==u.s1 && s2==u.s2 && poids==u.poids) || ((s2==u.s1 && s1==u.s2 && poids==u.poids)))
        {
            return 1 ;
        }
    else
        return 0 ;
}




#endif // ARC_HPP_INCLUDED
