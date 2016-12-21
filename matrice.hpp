#ifndef MATRICE_HPP
#define MATRICE_HPP
#include <iostream>

using namespace std ;

template <class T>
class matrice
{
public:
    int dim ;
    T** val ;

    matrice() ;                     //constructeur par d�fault

    matrice(int d, T v) ;  //constructeur avec valeurs

    matrice(const matrice<T> & M)  ;   //constructeur par copie

    ~matrice()  ;                 //destructeur

    T & operator()(int i, int j) const ; //acces au terme (i,j)

    int dim_() const; // taille de la matrice

    matrice<T> & operator =(const matrice<T> & M) ;  //assignation d'une matrice

    matrice<T> & operator +=(T a) ;          //addition d'une matrice et d'un r�el

    matrice<T> & operator *=(T a) ;          //multiplication d'une matrice par un r�el

    matrice<T> & operator +=(const matrice<T> & M) ; //addition de deux matrices

    void print() ;                             //affichage des coordonn�es d'une matrice


};

//---------------------- Constructeurs de matrice ----------------------------
template <class T>
matrice<T>::matrice()            //Constructeur par d�faut
{
    dim = 0 ;
    val = NULL ;
}

template <class T>
matrice<T>::matrice(int d, T v)    //Constructeur avec valeurs
    {
        dim = d ;
        val = new T* [dim] ;
        for (int i = 0; i < dim; i++)
        {
            val[i] = new T [dim] ;
            for (int j = 0; j < dim; j++)
            {
                val[i][j] = v ;
            }
        }


    }

template <class T>
matrice<T>::matrice(const matrice<T> & M)   //constructeur par copie
    {
        dim = M.dim ;
        val = new T* [dim] ;
        for (int i = 0; i < dim; i++)
        {
            val[i] = new T [dim] ;
            for (int j = 0; j < dim; j++)
            {
                val[i][j] = M.val[i][j] ;

            }

        }

    }

template <class T>
matrice<T>::~matrice()                 //destructeur
    {
        if (val != 0)
        {
            for (int i = 0; i < dim; i++)
            {
                delete [] val[i] ;
            }
        }
    }

template <class T>
T & matrice<T>::operator()(int i, int j ) const
{
    return val[i-1][j-1];
}

template<class T>
int matrice<T>::dim_() const
{
    return dim;
}

//---------------------Fonctionnalit�s sur les matrices-----------------------

template <class T>
matrice<T>& matrice<T>::operator=(const matrice<T> & M)          //Op�rateur d'assignation
{
    dim = M.dim ;
    val = new T* [dim] ;
    for (int i = 0; i < dim; i++)
    {
        val[i] = new T [dim] ;
        for (int j = 0; j < dim; j++)
        {
            val[i][j] = M.val[i][j] ;
        }
    }
    return *this ;
}

template <class T>
matrice<T>& matrice<T>::operator+=(T a)           //Op�rateur de somme d'une matrice et d'un nombre
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            val[i][j] += a ;
        }
    }
    return *this ;
}

template <class T>
matrice<T>& matrice<T>::operator*=(T a)                 //Op�rateur de produit d'une matrice et d'un nombre
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            val[i][j] *= a ;
        }
    }
    return *this ;
}

template <class T>
matrice<T> & matrice<T>::operator +=(const matrice<T> & M)      //Op�rateur de somme de matrices
{
    if (dim != M.dim)
    {
        delete [] val ;
        dim = M.dim ;
        val = new T* [dim] ;
        for (int i = 0; i < dim; i++)
        {
            val[i] = new T [dim] ;
        }
    }

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            val[i][j] += M.val[i][j] ;
        }
    }
    return *this ;
}

template <class T>
void matrice<T>::print()                 //Affichage de matrices
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            cout << val[i][j] << " ";
        }
        cout << endl ;
    }

}
#endif // MATRICE_HPP
