#ifndef INTERSECT_HPP_INCLUDED
#define INTERSECT_HPP_INCLUDED
#include"Point.hpp"


//fonction qui détermine si 2 segments se coupent ou pas 
template <class T>
bool intersect(const Point<T> & A, const Point<T> & B, const Point<T> & C, const Point<T> & D) 
{
if (vect(A,B,C,D)!=0)
    {
        if ((vect(A,B,A,D)*vect(A,B,A,C)<=0 && vect(C,D,C,B)*vect(C,D,C,A)<0) or (vect(A,B,A,D)*vect(A,B,A,C)<0 && vect(C,D,C,B)*vect(C,D,C,A)<=0))
            return 1;
        else
            return 0;
    }
else
    {
    return 0;
    }
}


#endif
