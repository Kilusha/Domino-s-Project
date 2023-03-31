#ifndef MATRICE_H // Directive de préprocesseur qui permet de vérifier si la macro MATRICE_H n'a pas été définie auparavant. Si MATRICE_H n'a pas été définie, alors le code contenu entre #ifndef et #endif est inclus, sinon ce code est ignoré. Cette technique permet d'éviter les problèmes de double inclusion de fichiers d'en-tête.
#define MATRICE_H // Directive de préprocesseur qui permet de définir la macro MATRICE_H à une valeur donnée (ici, rien, car MATRICE_H est juste une macro de protection). Cette technique est couramment utilisée pour éviter les problèmes de double inclusion de fichiers d'en-tête et pour faciliter la gestion des dépendances entre fichiers.

#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.
#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.

void creation_Matrice(double **matrice, int Tmax, int Nmax, double valeur_def, double valeur_spe); // Annonce l'existence d'une fonction creation_Matrice qui ne renvoie rien.

#endif // Termine le code de création de la macro MATRICE_H.
