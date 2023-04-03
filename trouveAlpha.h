#ifndef TROUVEALPHA_H // Directive de préprocesseur qui permet de vérifier si la macro TROUVEALPHA_H n'a pas été définie auparavant. Si TROUVEALPHA_H n'a pas été définie, alors le code contenu entre #ifndef et #endif est inclus, sinon ce code est ignoré. Cette technique permet d'éviter les problèmes de double inclusion de fichiers d'en-tête.
#define TROUVEALPHA_H // Directive de préprocesseur qui permet de définir la macro TROUVEALPHA_H à une valeur donnée (ici, rien, car TROUVEALPHA_H est juste une macro de protection). Cette technique est couramment utilisée pour éviter les problèmes de double inclusion de fichiers d'en-tête et pour faciliter la gestion des dépendances entre fichiers.

#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.
#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.

double trouve_Alpha_dicho(double delta, double l0, double h); // Annonce l'existence d'une fonction trouve_Alpha_dicho qui renvoie un double.
double calcul_Membre_Gauche(double alphaChoc, double delta, double l0, double h); // Annonce l'existence d'une fonction calcul_Membre_Gauche qui renvoie un double.
double trouve_Alpha(double delta, double l0, double h, int Nmax); // Annonce l'existence d'une fonction trouve_Alpha qui renvoie un double.

#endif // Termine le code de création de la macro TROUVEALPHA_H.
