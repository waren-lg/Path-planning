#ifndef COUTS_HPP_INCLUDED
#define COUTS_HPP_INCLUDED
#include <limits>
#include <vector>
#include"Point.hpp"
#include"arcplanification.hpp"
#include"matrice.hpp"
#include"intersect.hpp"
#include "graphe.hpp"

template<typename T>
int intersection(Point<T> D, Point<T> A, vector<Obstacle<T> > O, int nb_obs)   //Une Fonction qui determine si l'arc (AD) coupe l'un des obstacles ou pas.
{
    for(int i=0; i<nb_obs; i++)
    {
        graphe<T> G = arcs_diag(O[i]) ;   //On ajoute les arcs pour les obstacles non convexes
        for (int j=0; j<G.A.size(); j++)
        {
            if (intersect(D,A,G.A[j].s1,G.A[j].s2)==1)
                return 1;
        }
    }
    return 0;
}


template<typename T>
bool sommet(Point<T> D, vector<Obstacle<T> > O, int nb_obs)   //Une fonction qui determine si un point est un sommet ou pas: utile pour la matrice des couts, afin d'eviter les repetitions.
{
    for(int i=0; i<nb_obs; i++)
    {
        vector<Point<T> > sommets(O[i].S);
        for(int j =0; j<O[i].nb; j++)
        {
            if (sommets[j]==D)
                return 1 ;
        }
    }
    return 0;
}


template<typename T>
bool arc_arete(Point<T> D,Point<T> A, graphe<T> G)          //Une fonction qui determine si un arc entre deux sommets est une arête possible ou pas
{
    if (D==A)
        return 1;

    for (int i=0; i<G.A.size(); i++)
    {
        arc<T> temp = arc<T> (D,A);
        if (temp==G.A[i])
            return 1;
    }
    return 0;
}

template<class T>
matrice<T> couts(Point<T> D, Point<T> A, vector<Obstacle<T> > O, int nb_obs)           //Une fonction qui va calculer la matrice des coûts
{
    int m=0; //Compteur de positionement sur le vecteur sommets
    vector<Point<T> > sommets = vector<Point <T> >() ;     //Le vecteur qui va contenir les points
    int n=0;
    if (sommet(D,O,nb_obs)==0)              //Si le départ ne s'effectue pas sur le sommet d'un obstacle..
        {
            sommets.push_back(D);     //On rentre le point de départ dans le vecteur
            n=1;
            m++;
        }
    for (int i=0; i<nb_obs; i++)
    {
        for(int j=0; j<O[i].nb; j++)
            {
                sommets.push_back(O[i].S[j]);    //On rentre chaque sommet dans le vecteur
            }

            n+=O[i].nb;
    }
    if (sommet(A,O,nb_obs)==0)        //Idem pour le point d'arrivée
    {
        sommets.push_back(A);
        n++;
    }

    matrice<T> c(n,0);           //On crée la matrice
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n;j++)
        {
            if (intersection(sommets[i],sommets[j],O,nb_obs)==1) //Dès qu'il y a intersection avec l'un des autres obstacles
                c.val[i][j]=std::numeric_limits<T>::infinity();    //Le coût du déplacement est infini
            else
                c.val[i][j]=sommets[j].distance(sommets[i]);    //Sinon on affecte la distance
        }
    }
    //On elimine les differents arcs non admissibles des obstacles (comme les arcs diagonaux d'un carre)
   for (int k=0; k<nb_obs; k++)
   {
       int nb= O[k].nb;
       for (int i=0; i<nb; i++)
       {
           for (int j=0; j<nb;j++)
           {
               if (arc_arete(sommets[i+m],sommets[j+m],arcs_diag(O[k]))==0)          //Si l'arc est impossible..
                    c.val[i+m][j+m]=std::numeric_limits<T>::infinity();            //Le coût de déplacement est infini
                else
                    c.val[i+m][j+m]=sommets[j+m].distance(sommets[m+i]);         //Sinon on affecte la distance
           }
       }
       m=m+nb;     //On passe de matrice par bloc à une autre.
   }
    return c;
}

#endif // COUTS_HPP_INCLUDED
