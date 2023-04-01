#include "trouveAlpha.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque dicho dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de l'espace de noms standard (std).

/* Création de la fonction calcul_Membre_Gauche qui permet de calculer le membre
 * de gauche trouvé dans la partie théorique qui est censé valoir 0 lorsqu'un
 * domino entre en contact avec son voisin. Ainsi il nous permettra de
 * déterminer le bon angle alpha qui correspond à l'angle de choc */
/*
double calcul_Membre_Gauche(double alphaChoc, double delta, double l0,
                            double h) {
  return sin(alphaChoc) - (delta - l0 * cos(alphaChoc)) / h;
}*/
double trouve_Alpha(double delta, double l0,
                            double h) {
  return M_PI/2 -atan(l0/h) - acos(delta/sqrt(h*h +l0*l0));
                            }
/* Création de la fonction trouve_Alpha_dicho qui permet de déterminer par dichotomie
 * la valeur de l'angle pour lequel un domino entre en contact avec son voisin
 */
/*
double trouve_Alpha_dicho(double delta, double l0, double h) {
  double alphaMin =
      0.0; // Définition de la borne inférieure de notre intervalle
  double alphaMax =
      M_PI / 2; // Définition de la borne supérieure de notre intervalle
  const double epsi = 1e-1; // définition de la tolérance
  double alphaChoc = (alphaMin + alphaMax) /
                     2.0; // Définition de la valeur initiale de l'angle choc
  while (fabs(calcul_Membre_Gauche(alphaChoc, delta, l0, h)) >
         epsi) { // Vérifie si le membre de gauche de l'équation théorique vaut
                 // quasi 0 en prenant en compte la tolérance. Sinon, alors nous
                 // rentrons dans la boucle.
    if (calcul_Membre_Gauche(alphaChoc, delta, l0, h) >
        0) { // Si la valeur du membre de gauche est trop grand par rapport à 0
      alphaMax =
          alphaChoc; // La valeur de l'angle représentant le choc entre 2
                     // dominos se situera dans la partie inférieure de
                     // l'intervalle de départ. On définit donc notre ancienne
                     // valeur de alphachoc comme étant nouvelle borne
                     // supérieure puisque nous sommes sûr que la valeur de cet
                     // angle ne peut pas se trouver au dessus.
    } else { // Si la valeur du membre de gauche est trop petite par rapport à 0
      alphaMin =
          alphaChoc; // La valeur de l'angle représentant le choc entre 2
                     // dominos se situera dans la partie supérieure de
                     // l'intervalle de départ. On définit donc notre ancienne
                     // valeur de alphachoc comme étant nouvelle borne
                     // inférieure puisque nous sommes sûr que la valeur de cet
                     // angle ne peut pas se trouver au dessous.
    }
    alphaChoc = (alphaMin + alphaMax) /
                2.0; // Detemination du nouvel alphachoc comme le centre du
                     // nouvel intervalle crée juste au dessus
  }
  return alphaChoc; // Renvoie la valeur de l'angle pour lequel un domino entre
                    // en contact avec son voisin.
} */
