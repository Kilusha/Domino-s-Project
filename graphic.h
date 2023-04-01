#ifndef GRAPHIC_H // Directive de préprocesseur qui permet de vérifier si la
                  // macro GRAPHIC_H n'a pas été définie auparavant. Si
                  // GRAPHIC_H n'a pas été définie, alors le code contenu entre
                  // #ifndef et #endif est inclus, sinon ce code est ignoré.
                  // Cette technique permet d'éviter les problèmes de double
                  // inclusion de fichiers d'en-tête.
#define GRAPHIC_H // Directive de préprocesseur qui permet de définir la macro
                  // GRAPHIC_H à une valeur donnée (ici, rien, car GRAPHIC_H est
                  // juste une macro de protection). Cette technique est
                  // couramment utilisée pour éviter les problèmes de double
                  // inclusion de fichiers d'en-tête et pour faciliter la
                  // gestion des dépendances entre fichiers.

#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.
#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.

void trace_Graph(double **alpha, int dt,
                 int Tmax); // Annonce l'existence d'une fonction trace_Graph
                            // qui ne renvoie rien.

#endif // Termine le code de création de la macro GRAPHIC_H.
