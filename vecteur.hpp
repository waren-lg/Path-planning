#ifndef VECTEUR_HPP
#define VECTEUR_HPP
#include <vector>
#include <iostream>

using namespace std ;

template <class T>
class vecteur
{public:
    vector<T> val;

    vecteur() ;                     //constructeur par défault

    vecteur(int n, const T & v) ;       //constructeur avec valeurs

    vecteur(const vector<T> & v)  ;   //constructeur par copie

    void print() ;                         //affichage des coordonnées d'un vecteur

    vecteur<T> & operator=(const vecteur<T> & v) ;   //assignation d'un vecteur

};

//---------------------- Constructeurs de vecteur ----------------------------
template <class T>
vecteur<T>::vecteur()            //Constructeur par défaut
{
    val = vector<T>(0) ;
}

template <class T>
vecteur<T>::vecteur(int n,const T & v)    //Constructeur avec valeurs
{
    val = vector<T>(n,v) ;
}

template <class T>
vecteur<T>::vecteur(const vector<T> & v)   //constructeur par copie
{
    val = vector<T>(v) ;
}


//---------------------Fonctionnalités sur les vecteurs-----------------------
template <class T>
void vecteur<T>::print()        //Fonction d'affichage
{
    cout << "(" << val[0];
    for (int i = 1; i < val.size(); i++)
    {
        cout <<"," << val[i];
    }
    cout << ")" << endl ;
}


template <class T>
vecteur<T> & vecteur<T>::operator=(const vecteur<T> & v)       //Opérateur d'assignation
{
    val = v.val ;
    return * this ;
}








#endif // VECTEUR_HPP
