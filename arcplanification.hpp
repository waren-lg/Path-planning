#ifndef ARCPLANIFICATION_HPP_INCLUDED
#define ARCPLANIFICATION_HPP_INCLUDED
#include "arc.hpp"
#include "Point.hpp"

template <class T>
class arcPlanification : public arc<T>
{public :
    arcPlanification();
    arcPlanification(const Point<T> & u, const Point<T> & v);
    arcPlanification(const arcPlanification<T> & M );

};

template <class T>
arcPlanification<T>::arcPlanification()
{
    this->s1.x = 0 ;
    this->s2.x = 0 ;
    this->s1.y = 0 ;
    this->s2.y = 0 ;
    this->poids = 0 ;
}

template <class T>
arcPlanification<T>::arcPlanification(const Point<T> & u, const Point<T> & v)
{
    this->s1 = u ;
    this->s2 = v ;
    this->poids = this->s1.distance(this->s2) ;
}

template <class T>
arcPlanification<T>::arcPlanification(const arcPlanification<T> & M)
{
    this->s1 = M.s1;
    this->s2 = M.s2;
    this->poids=M.poids;
}




#endif // ARCPLANIFICATION_HPP_INCLUDED
