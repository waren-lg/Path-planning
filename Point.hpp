#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED
#include <iostream>
#include <cmath>
#include "vecteur.hpp"



using namespace std;

template <class T>
class Point
{public:
    T x ;
    T y ;
    Point ();
    Point (const T & u, const T & v);
    Point (const Point<T> & u);
    Point<T> & operator=(const Point<T> & u );
    Point<T> & operator+=(const Point<T> & u);
    Point<T> & operator-=(const Point<T> & u);
    Point<T> & operator*=(const T & u);
    Point<T> operator/=(T u);
    bool  operator==(const Point<T> & u);
    void print()
    {
        cout << "(" << x << "," << y << ")" << endl;
    };
    T distance(const Point<T> & s2) const
    {
        return sqrt((x-s2.x)*(x-s2.x) + (y-s2.y)*(y-s2.y)) ;
    };
    Point<T> rotation(const Point<T> & P1, const Point<T> & P2, double angle);

};

template <class T>
Point<T>::Point()                  //Constructeur par défaut
{
    x=0;
    y=0;
}
template <class T>
Point<T>::Point(const T & u, const T & v)       //Constructeur avec valeurs
{
    x=u;
    y=v;
}

template <class T>
Point<T>::Point(const Point<T> & u )          //Constructeur par copie
{
    x=u.x;
    y=u.y;
}


template <class T>
bool  Point<T>::operator==(const Point<T> & u)       //Opérateur de test d'égalité
{
    if (x==u.x and y==u.y)
        return true ;
    else
        return false;
}


template <class T>
Point<T> & Point<T>::operator=(const Point<T> & u)         //Opérateur d'assignation
{
    x=u.x;
    y=u.y;
    return *this;
}

template <class T>
Point<T> & Point<T>::operator+=(const Point<T> & u)           //Opérateur de somme de points
{
    x=x+u.x;
    y=y+u.y;
    return *this;
}

template <class T>
Point<T> & Point<T>::operator-=(const Point<T> &  u)            //Opérateur de soustraction de points
{
    x=x-u.x;
    y=y-u.y;
    return *this;
}

template <class T>
Point<T> & Point<T>::operator*=(const T & u)          //Opérateur de produit d'un point par un nombre
{
    x=x*u;
    y=y*u;
    return *this;

}
template <class T>
Point<T> Point<T>::operator/=(T u)              //Opérateur de division d'un point par un nombre
{   if (u==0)
    {
        Point<T> P;
        return P;
    }
    else
    {
        x=x/u;
        y=y/u;
        return *this;

    }
}

template <class T>
Point<T> operator +(const Point<T> & u , const Point<T> & v)          //Opérateur de somme de points
{
    Point<T> s(u) ;
    return s+=v;

}

template <class T>
Point<T> operator -(const Point<T> & u , const Point<T> & v)    //Opérateur de soustraction de points
{
    Point<T> s(u) ;
    return s-=v;

}

template <class T>
Point<T> operator *(const Point<T> & u , const T & v)           //Opérateur de produit de point par un nombre
{
    Point<T> s(u) ;
    return s*=v;

}

template <class T>
Point<T> operator /(const Point<T> & u , const T & v)           //Opérateur de division d'un point par un nombre
{
    Point<T> s(u) ;
    return s/=v;

}

template <class T>
Point<T> rotation(const Point<T> & P1, const Point<T> & P2, double alpha) //Une fonction qui effectue la rotation du point P1 autour du point P2 d'un angle alpha
{
    vecteur<T> V ;
    V.val.push_back(P1.x-P2.x) ;
    V.val.push_back(P1.y-P2.y) ;
    Point<T> P ;
    P.x = cos(alpha)*V.val[0]-sin(alpha)*V.val[1] +P2.x;
    P.y = sin(alpha)*V.val[0]+cos(alpha)*V.val[1] +P2.y;
    return P;
}

template <class T>
T vect(const Point<T> & A,const Point<T> & B,const Point<T> & C,const Point<T> & D)        //Une fonction qui calcule le produit vectoriel entre AB et CD
{
    return ((B.x-A.x)*(D.y-C.y)-(B.y-A.y)*(D.x-C.x)) ;
}




#endif // POINT_HPP_INCLUDED
