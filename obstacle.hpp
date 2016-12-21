#ifndef OBSTACLE_HPP_INCLUDED
#define OBSTACLE_HPP_INCLUDED
#include <limits>
#include <vector>
#include "Point.hpp"
#include "arcplanification.hpp"
#include "vecteur.hpp"
#include "graphe.hpp"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std ;

template <class T>
class Obstacle
{public:
    int nb;
    vector<Point<T> > S;
    graphe<T> G;
    vector<Point<T> > N;

    Obstacle();
    Obstacle(const vector<Point<T> > & M);
    void print()
    {
        for (unsigned int i =0; i<S.size();i++)
        {
            S[i].print() ;
        }
    }
    void vecteur_sommet(vector<Point<T> > & V, T rayon);

};
template <class T>
Obstacle<T>::Obstacle()           //Constructeur par défaut
{
    nb=0;
}

template <class T>
Obstacle<T>::Obstacle(const vector<Point<T> > & M)             //Constructeur avec valeurs
{
    nb=M.size();
    //On remplit le vecteur de points
    for(int i = 0; i<nb; i++)
    {
        S.push_back(M[i]) ;
    }
    //on dresse les arretes de l'obstacle dans le sens trigonometrique
    for (int i=0; i<nb-1 ; i++)
    {
        arc<T> arrete(M[i], M[i+1]);
        G.A.push_back(arrete);
    }
    //On ferme la boucle des arretes de l'obstacle
    arc<T> arrete(M[nb-1], M[0]);
    G.A.push_back(arrete);

    //calcul des normales :
    for (int i =0; i<nb-1 ; i++)
    {
        //Rotation et normalisation des normales
        Point<T> P(0,0);
        P.x = (M[i+1].y-M[i].y);
        P.y = (-M[i+1].x+M[i].x);
        T norme = sqrt(P.x*P.x+P.y*P.y) ;
        P /= norme ;
        N.push_back(P);

    }
    //calcul de la derniere normale
    Point<T> P(0,0);
    P.x = M[0].y-M[nb-1].y;
    P.y = -M[0].x+M[nb-1].x;
    double norme = sqrt(P.x*P.x+P.y*P.y) ;
    P /= norme ;
    N.push_back(P);
}

template <class T>
graphe<T> arcs_diag(Obstacle<T> Obs)                //Une fonction qui élimine les arcs inutiles
{
    graphe<T> graphe_final;
    for (int i=0; i<Obs.nb; i++)
    {
        graphe_final.A.push_back(Obs.G.A[i]);//On crée une liste d'arcs qui contient pour le moment chaque arc de l'obstacle
    }
    for (int i=0; i<Obs.nb; i++)
    {   Point<T> n1;
        Point<T> n2;
        int nb=Obs.nb;
        if (i==0)             //On affecte les normales à chaque arc à de nouvelles variables
        {
            n1=Obs.N[0];
            n2=Obs.N[Obs.nb-1];
        }
        else
        {
            n1=Obs.N[i];
            n2=Obs.N[i-1];
        }
        for (int j=i+2; j<nb; j++)
        {
                //On doit verifier si l'arc entre le point i et j est à l'exterieur
                //pour qu'il le soit, il faut que le produit scalaire avec la normale entrante moyenne soit negatif
                if ((((n1.x*(Obs.S[j].x-Obs.S[i].x) + n1.y*(Obs.S[j].y-Obs.S[i].y))<0) && ((n2.x*(Obs.S[j].x-Obs.S[i].x) + n2.y*(Obs.S[j].y-Obs.S[i].y))>=0)) ||
                    (((n1.x*(Obs.S[j].x-Obs.S[i].x) + n1.y*(Obs.S[j].y-Obs.S[i].y))>=0) && ((n2.x*(Obs.S[j].x-Obs.S[i].x) + n2.y*(Obs.S[j].y-Obs.S[i].y))<0)))
                //maintenant l'arc est bien à l'exterieur, mais si il coupe une arrete?
                {   int inters=0;
                    for(int k=0; k<Obs.nb; k++)
                    {
                        if (intersect(Obs.S[i],Obs.S[j],Obs.G.A[k].s1,Obs.G.A[k].s2)==1)
                            inters=1;

                    }
                    if (inters==0)

                    {
                        arc<T> new_arc(Obs.S[i],Obs.S[j]);
                        graphe_final.A.push_back(new_arc);
                    }
                }
        }
    }



    return graphe_final;
}

template <class T>
vector<int> sommet_convexe(Obstacle<T> O) //On va remplir le vecteur coins qui détermine si un sommet est "convexe" ou pas
{
    vector<int> V(O.nb) ;
    if (vect(O.S[O.nb-1],O.S[0],O.S[0],O.S[1]) < 0) //Cas spécial du premier sommet
    {
        V[0] = 1 ;
    }

    for (int i = 1; i < O.nb - 1; i++) //On boucle sur chaque sommet sauf le dernier
    {
        if (vect(O.S[i-1],O.S[i],O.S[i], O.S[i+1]) < 0)
        {
            V[i] = 1 ;
        }
    }

    if (vect(O.S[O.nb-2],O.S[O.nb-1],O.S[O.nb-1],O.S[0]) < 0) //Cas spécial du dernier sommet
    {
        V[O.nb-1] = 1 ;
    }
    return V ;
}


template <class T>
void Obstacle<T>::vecteur_sommet(vector<Point<T> > & V, T rayon) //Une fonction qui crée les vecteurs qui sortent des sommets de manière colinéaire à la bissectrice de norme le rayon de l'objet
{
    unsigned int n = S.size() ;
    Point<T> U = N[0] + N[n-1] ; //On crée pour le premier sommet, qui est spécial et ne rentre pas dans le cadre de la boucle
    double norme = sqrt(U.x*U.x+U.y*U.y) ;   //On transforme le vecteur en un vecteur colinéaire de norme égale à rayon
    U /= norme ;
    U *= rayon ;
    U += S[0] ;
    V.push_back(U) ;
    for (unsigned int i = 1; i < n; i++)
    {
        Point<T> U = N[i] + N[i-1] ; //On fait pour les autres sommets
        double norme = sqrt(U.x*U.x+U.y*U.y) ;   //On normalise le vecteur à 0.02, ce qui représente la taille de l'objet
        U /= norme ;
        U *= rayon ;
        U += S[i] ;
        V.push_back(U) ;  //On stocke le tout dans un vector de point qui contient les deux coordonnées du vecteur sortant
    }
}

template <class T>
vector<Obstacle<T> > create_point(int nb_iter, vector<Obstacle<T> > O, T rayon ) //Une fonction qui va créer nb_iter points pour contourner l'obstacle avec un certain rayon
{
    vector<Obstacle<T> > R ; //On initialise un vecteur d'obstacle qui va tout contenir à la fin
    ofstream fichier("resultat_points.txt", ios::out | ios::trunc);  //On ouvre le fichier dans lequel on va écrire les nouveaux points
    fichier<<"DEPART"<<endl;
    fichier<<"2.5 2"<<endl;
    for (int k = 0; k < O.size(); k++)
    {
        fichier<<"OBSTACLE"<<endl;
        vector<int> coins = sommet_convexe(O[k]) ; //On crée le vecteur qui va déterminer si les points sont "convexes"
        vector<Point<T> > U ; //On crée le vecteur qui va contenir les points de l'obstacle existant
        O[k].vecteur_sommet(U, rayon) ;
        vector<Point<T> > V ;  //On crée le vecteur qui va recevoir les nouveaux points
        int n = U.size() ;
        Point<T> P;
        if (coins[0] == 0)
        {
            P = rotation(U[0], O[k].S[0], -M_PI_4) ; //On effectue la rotation du point décalé d'un angle pi/4 dans le sens horaire
            V.push_back(P) ;    //On insère ce point dans V
            fichier << P.x << " " << P.y << "\n" << endl ;   //On écrit les coordonnées du point dans le fichier
            for (int i = 0; i < nb_iter; i++)   //On itère nb_iter fois pour tourner d'un angle alpha en tout
            {
                P = rotation(P, O[k].S[0], M_PI/(2*nb_iter)) ; //On effectue la rotation du point P d'un angle pi/(2*nb_iter) dans le sens trigonométrique
                V.push_back(P) ; //On insère ce point dans V
                fichier << P.x << " " << P.y << "\n" << endl ;
            }
        }
        else
        {
            V.push_back(U[0]) ;
            fichier << U[0].x << " " << U[0].y << "\n" << endl ;
        }
        for(int i = 1; i < n-1; i++)  //On boucle sur le reste des sommets
        {
            if (coins[i] == 0)            //Si le sommet est "convexe"
            {
                P = rotation(U[i], O[k].S[i], -M_PI_4) ;         //Rotation de pi/4 dans le sens horaire
                V.push_back(P) ;
                fichier << P.x << " " << P.y << "\n"  << endl ;
                for (int j = 0; j < nb_iter; j++)
                {
                    P = rotation(P, O[k].S[i], M_PI/(2*nb_iter)) ;   //On effectue la rotation du point P d'un angle pi/(2*nb_iter) dans le sens trigonométrique
                    V.push_back(P) ;
                    fichier << P.x << " " << P.y<< "\n"  << endl ;
                }
            }
            else          //Si le point est "non convexe" on ne fait pas la rotation
            {
                V.push_back(U[i]) ;
                fichier << U[i].x << " " << U[i].y << "\n"  << endl ;
            }
        }
        int i =n-1;
        if (coins[i] == 0)           //Pour le dernier sommet
            {
                P = rotation(U[i], O[k].S[i], -M_PI_4) ;
                V.push_back(P) ;
                fichier << P.x << " " << P.y << "\n"  << endl ;
                for (int j = 0; j < nb_iter - 1; j++)
                {
                    P = rotation(P, O[k].S[i], M_PI/(2*nb_iter)) ;
                    V.push_back(P) ;
                    fichier << P.x << " " << P.y<< "\n"  << endl ;
                }
                P = rotation(P, O[k].S[i], M_PI/(2*nb_iter)) ;
                V.push_back(P) ;
                fichier << P.x << " " << P.y << endl ;
            }
            else
            {
                V.push_back(U[i]) ;
                fichier << U[i].x << " " << U[i].y << "\n"  << endl ;
            }
        Obstacle<T> Q(V) ;
        R.push_back(Q) ;
        fichier <<"FIN_OBSTACLE"<<endl;
        }
        fichier<<"ARRIVEE"<<endl;
        fichier<<"10.5 7.5"<<endl;
        return R ;
}





#endif // OBSTACLE_HPP_INCLUDED
