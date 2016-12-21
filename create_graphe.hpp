#ifndef CREATE_GRAPHE_HPP
#define CREATE_GRAPHE_HPP
#include <fstream>      //lecture dans les fichiers
#include <iostream>
#include "obstacle.hpp"
#include "Point.hpp"
#include "arc.hpp"
#include "vecteur.hpp"
#include <string>
#include <cstdlib>
#include <vector>

using namespace std ;


template <class T>
void create_graphe() //Une fonction qui ouvre un fichier texte, en lit les coordonn�es pr�sentes et modifie un fichier o� sera �crit p
{
    ifstream fichier("coordonnees.txt",ios::in) ; //Ouverture du fichier texte qui contient les coordonn�es des points des obstacles
    vector<Point<T> > X(0) ; //On cr�e un vector de points vide
    vector<Obstacle<T> > Obs(0) ; //On cr�e un vecteur d'obstacles vide
    vector<Obstacle<T> > Obs_pad(0) ;
    T a ;
    Point<double> Arr ;
    Point<double> D(0,0) ;
    T b ;
    string c, c1,c2;
    string str;
 if (fichier)
 {
    getline (fichier,str);
    fichier >> c >> c1 ;
    getline(fichier,str);
    a = atof(c.c_str()) ;
    b = atof(c1.c_str()) ;
    Point<double> D(0,0) ; //On cr�e le point qui va recevoir les coordonn�es puis on le remplit
    D.x = a ;
    D.y = b ;
    c.clear() ; //On vide les cha�nes pour le prochain caract�re
    c1.clear() ;
    getline (fichier,str);
    while (str.compare("OBSTACLE")==0) //Tant qu'on n'est pas � la fin du fichier..
    {
        fichier >> c >> c1 ; //On remplit les cha�nes
        getline(fichier,str);
        a = atof(c.c_str()) ; //Conversion d'un char en string puis en double
        b = atof(c1.c_str()) ;
        Point<double> P(0,0) ; //On cr�e le point qui va recevoir les coordonn�es puis on le remplit
        P.x = a ;
        P.y = b ;
        X.push_back(P) ; //On remplit la cha�ne avec les points
        c.clear() ; //On vide les cha�nes pour le prochain caract�re
        c1.clear() ;
        getline(fichier,str);
        while (str.compare("FIN_OBSTACLE")!=0) //Tant qu'on ne lit pas le caract�re -1, utilis� pour s�parer les obstacles dans le fichier texte, on continue de lire
        {
            fichier >> c >> c1 ; //Remplissage
            getline(fichier,str);
            a = atof(c.c_str()) ; //Conversion
            b = atof(c1.c_str()) ;
            Point<double> P(0,0) ; //On cr�e le point qui va recevoir les coordonn�es puis on le remplit
            P.x = a ;
            P.y = b ;
            P.print();
            X.push_back(P) ; //On remplit la cha�ne avec les points
            c.clear() ; //On vide les cha�nes pour le prochain caract�re
            c1.clear() ;
            getline(fichier,str);
        }
        Obstacle<double> O(X);
        Obs.push_back(O);
        X.clear();
        getline(fichier,str);
    }
    cout<<str.compare("ARRIVEE")<<endl;
    fichier >> c >> c1 ;
    a = atof(c.c_str()) ;
    b = atof(c1.c_str()) ;
    Point<double> Arr(a,b) ; //On cr�e le point qui va recevoir les coordonn�es puis on le remplit
    c.clear() ; //On vide les cha�nes pour le prochain caract�re
    c1.clear() ;
    matrice<double> C = matrice<double>(couts(D,Arr,Obs,Obs.size()));   //On cr�� la matrice des co�ts relative au probl�me
    vector<double>  l = vector<double> (C.dim_(),0);   //On cr�� les vecteurs co�ts et parents
    vector<double>  p = vector<double> (C.dim_(),0);
    vector<int> S = vector<int> (1,0);     //On cr�� les vecteurs qui listent les sommets
    vector<int> U = vector<int>(1,1);
    for (int i =2; i<C.dim_(); i++)
         U.push_back(i);
    dijkstra<double>(C.dim_(),C,S,U,l,p);   //On fait tourner l'algorithme de Dijkstra

    ofstream fichier2("dijkstra.txt", ios::out | ios::trunc);     //On �crit les vecteurs co�ts et parents dans un fichier
    for (int i =0; i<C.dim_(); i++)
    {
       fichier2<<p[i]<<" ";
    }
    fichier2<< "\n" ;

    for (int i = 0; i<C.dim_(); i++)
    {
        fichier2<<l[i] << " " ;
    }
 }
 else
    cout<<"impossible"<<endl;
 fichier.close() ;

}






#endif // CREATE_GRAPHE_HPP
