#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "vecteur.hpp"
#include "matrice.hpp"
#include <vector>
#include <limits>

template <class T>
void dijkstra(int N, const matrice<T> & C, vector<int> S, vector<int> U, vector<T>  & l, vector<T> & p)
{
    double a = std::numeric_limits<double>::infinity();    //On assigne à a la valeur infinie
    for (int i = 0; i < N; i++)
    {

        l[i] = C.val[0][i] ;              //On initialise l avec le coût de base : si le sommet i est directement lié au 1 ou pas
        p[i] = 0 ;                    //Pour le moment, pas de parent pour chaque sommet (valeur -1)
        if (i > 0 && C.val[0][i] < a)
        {
            p[i] = 0 ;                //Pour tous les sommets sauf le premier, s'il est lié au premier alors son parent est 1
        }
    }
    while (U.size() != 0)                 //On boucle sur U tant qu'il n'est pas vide
    {
        T b = l[U[0]] ;                  //On garde en mémoire l[U[0]]
        int c = 0 ;
        int d = U[0] ;
        for (unsigned int i = 1; i < U.size(); i++)     //On cherche le minimum de l sur U
        {
            if (l[U[i]] < b)
            {
                b = l[U[i]] ;
                c = i ;                            //On stocke la position du min pour la supprimer ensuite
                d = U[i] ;                           //On stocke la valeur du min pour le remettre dans S
            }
        }
        S.push_back(d) ;                  //On met d dans S
        U.erase(U.begin() + c) ;          //On supprime la valeur de U gardée


        for (unsigned int j = 0; j < U.size(); j++)      //On boucle sur les sommets encore dans U
        {
            if (C.val[d][U[j]] < a && l[U[j]] > l[d] + C.val[d][U[j]])     //2 conditions : il doit y avoir un lien entre les deux sommets et le nouveau chemin doit valoir le coup
            {
                    l[U[j]] = l[d] + C.val[d][U[j]] ; //Nouvelle valeur dans l
                    p[U[j]] = d ;                         //Nouveau parent
            }
        }

    }

}








#endif // DIJKSTRA_HPP
