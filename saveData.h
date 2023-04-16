/*
* Projet des Dominos C++
*
* saveData.h.cpp
*
* @auteurs PALAY Kiliann & SERRE Marina
*/

#ifndef SAVEDATA_H // Directive de préprocesseur qui permet de vérifier si la macro SAVEDATA_H n'a pas été définie auparavant. Si SAVEDATA_H n'a pas été définie, alors le code contenu entre #ifndef et #endif est inclus, sinon ce code est ignoré. Cette technique permet d'éviter les problèmes de double inclusion de fichiers d'en-tête.
#define SAVEDATA_H // Directive de préprocesseur qui permet de définir la macro SAVEDATA_H à une valeur donnée (ici, rien, car SAVEDATA_H est juste une macro de protection). Cette technique est couramment utilisée pour éviter les problèmes de double inclusion de fichiers d'en-tête et pour faciliter la gestion des dépendances entre fichiers.

#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.
#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.

void save_Data(double **matrice, int Tmax, int Nmax, const std::string &nomfichier); // Annonce l'existence d'une fonction save_Data qui ne renvoie rien.
double vitesse(double alpha1, double alpha2, double dt); // Annonce l'existence d'une fonction vitesse qui renvoie un double.

#endif // Termine le code de création de la macro SAVEDATA_H.
