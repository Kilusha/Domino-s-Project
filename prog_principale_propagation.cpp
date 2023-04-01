#include "graphic.cpp" // Directive de préprocesseur en C++. Elle permet d'inclure le fichier graphic dans le programme, qui contient la définition des fonctions permettant d'effectuer des opérations particulières.
#include "graphic.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque graphic dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "matrice.cpp" // Directive de préprocesseur en C++. Elle permet d'inclure le fichier matrice dans le programme, qui contient la définition des fonctions permettant d'effectuer des opérations particulières.
#include "matrice.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque matrice dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "saveData.cpp" // Directive de préprocesseur en C++. Elle permet d'inclure le fichier saveData dans le programme, qui contient la définition des fonctions permettant d'effectuer des opérations particulières.
#include "saveData.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque saveData dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "trouveAlpha.cpp" // Directive de préprocesseur en C++. Elle permet d'inclure le fichier trouveAlpha dans le programme, qui contient la définition des fonctions permettant d'effectuer des opérations particulières.
#include "trouveAlpha.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque trouveAlpha dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.
#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de
                     // l'espace de noms standard (std).

// J=m*h*h/3 est le moment d'inertie.
// alpha[t][n] est l'angle alpha du domino n a l'instant t.
// alpha[t+1][n] est l'angle alpha du domino n a l'instant t+dt.
// alpha[t-1][n] est l'angle alpha du domino n a l'instant t-dt.
// l[t][n] est la longueur du ressort n a l'instant t

// Pour propager les équations on fait des tableaux alpha et l a 2 indices (du
// type alpha[t][n]) afin de conserver la valeur des angles aux différents
// instants.

int main() { // Fonction spéciale dans un programme C++ qui est appelée
             // automatiquement lorsque le programme démarre. Elle est le point
             // d'entrée du programme et définit l'endroit où l'exécution du
             // programme commence. Elle doit être définie avec un type de
             // retour "int" qui sera renvoyé en exécutant ce code si tout s'est
             // bien déroulé.

  /* Déclaration de toutes les variables utiles pour le programme */
  const int Nmax = 10;    // Nombre de colonne de nos 2 tableaux (équivalent au
                          // nombre de dominos)
  const int Tmax = 2000;  // Nombre de lignes maximale de nos 2 tableaux
                          // (équivalent au temps maximal)
  const double l0 = 3e-3; // Longueur du ressort au repos en cm
  const double delta =
      1e-2; // Correspond à la distance entre 2 dominos successifs
  const double h = 3.0e-2; // Correspond à la taille en hauteur des dominos
  const double alphaChoc = trouve_Alpha(
     delta, l0, h); // Stocke la valeur de l'angle choc dans la variable
                     // alphaChoc en la déterminant par dichotomie à l'aide des
                     // fonctions trouve_Alpha et calcul_Membre_Gauche
  //const double alphaChoc = M_PI/2 -atan(l0/h) - acos(delta/sqrt(h*h+l0*l0));
  const double w0 = M_PI / 4; // Vitesse de chute du domino en rad.s^(-1)
  const double dt = 0.001;    // intervalle de temps en s
  /* double gamma = 15.8e-6; // Définition de la viscosité du milieu de
     propagation
                          // (ici l'air) */
  const double gamma = 1.81 / 100000; // Définition de la viscosité du milieu de
                                      // propagation (ici l'air)
  //const double gamma = 1.15 / 1000; // Viscosité dans l'eau
  //const double gamma = 6; //Viscosité du miel
  const double m = 10e-3; // Définition de la masse de l'objet en kg
  /*   double J = m * h * h / 3; // Définition du moment d'inertie */
  const double J = 7.5 / 10000000; // Définition du moment d'inertie
  const double g = 9.8;            // Définition de la pesanteur
  const double k = 1.0; // Définition de la constante du raideur du ressort
  const double lmin =
      0.0001; // Longueur minimale du ressort proche de 0 mais
              // différet de 0 pour ne pas créer de problèmes
              // dans les formules lors des calculs et pour définir la longueur
              // minimale lors de l'impact avec le domino voisin ou le sol dans
              // le cas du dernier domino, avant décompression pour valeur
              // d'équilibre

  double **alpha =
      new double *[Tmax]; // Déclaration du pointeur alpha qui pointera vers la
                          // case ou sera stocké la valeur de l'angle alpha.
  double **l = new double
      *[Tmax]; // Déclaration du pointeur l qui pointera vers la case
               // ou sera stocké la valeur de la longueur du ressort l.

  /* Initialisation des 2 tableaux à 2 dimensions en allouant de la mémoire
   * dynamique pour y stocker des variables de type "doubles" qui seront la
   * valeur de l'angle alpha du domino n à l'nstant t, ainsi que la longueur de
   * son ressort à ce même instant : */

  creation_Matrice(
      alpha, Tmax, Nmax, 0.,
      M_PI / 2); // Créé le tableau alpha qui gardera en mémoire la valeur des
                 // angles de tous les dominos à chaque instant de l'expérience
  creation_Matrice(l, Tmax, Nmax, l0,
                   lmin); // Créé le tableau l qui gardera en mémoire la valeur
                          // des longueurs des ressorts de tous les dominos à
                          // chaque instant de l'expérience

  cout << endl
       << "L'angle de choc est : " << alphaChoc << " rad."
       << endl; // Affiche la valeur de l'angle choc

  /* Initialisation de l'angle du premier domino a l'instant t+dt => t = 1 */

  alpha[1][0] =
      w0 *
      dt; // Stockage de la valeur de l'angle alpha du 1er domino à l'instant
          // t+dt qui correspond à t = 1. (Vitesse de chute * temps = angle)

  int t = 1; // Initialisation du temps t pour la suite du prog

  /* le 1er domino en mouvement jusqu'au choc*/
  while (alpha[t][0] <
         alphaChoc) { // Condition portant sur l'angle signifiant : Tant que le
                      // premier domino n'entre pas en contact avec son voisin.
    alpha[t + 1][0] =
        (2 * alpha[t][0] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][0] +
         (3 * g * dt * dt / (2 * h)) * sin(alpha[t][0])) /
        (1 +
         gamma * dt /
             (2 *
              J)); // Calcul et stockage dans le tableau des angles alpha de la
                   // valeur de l'angle alpha à l'instant t + dt pour le 1 er
                   // domino indice 0, à l'aide de l'équation du pdf n°1.

    t++; // Incrémentation du temps pour changer de ligne dans notre tableau et
         // pour passer à l'instant suivant. Ajout de 1 à t donc de dt à t.
  }

  /* Sortie de la boucle while. Ainsi le temps t correspond au temps pour lequel
   * il y a le choc entre le domino 0 et le domino 1 */

  int t_choc = t; // Sauvegarde de la valeur du temps requis avant le choc entre
                  // le domino 0 et le domino 1.

  cout << "La date du premier choc est : " << t_choc * dt
       << " secondes après le début de l'expérience."
       << endl; // Affiche la valeur du temps nécessaire avant le choc du domino
                // 0 avec le domino 1.

  /* Poursuite de la chute du 1er domino d'indice 0 après contact avec le
   * deuxième d'indice 1 */

  for (t = t_choc; t < Tmax - 1;
       t++) // ou for(t=0;t<Tmax;t++)  Poursuite de temps en partant de
            // l'instant du choc entre les 2 premiers dominos (t = t_choc,
            // jusqu'au moment ou les dominos seront tous à terre (t = Tmax=)
  {
    /* mouvement du 1er domino n°0 après choc avec le 2ème domino n°1 */

    l[t][0] =
        h * tan(alpha[t][1] - alpha[t][0]) +
        delta / ((1. + tan(alpha[t][0]) * tan(alpha[t][1])) *
                 cos(alpha[t][0])); // Calcul et stockage dans le tableau des
                                    // longueurs des ressorts l de la valeur de
                                    // la longueur l à l'instant t du ressort du
                                    // domino n°0, à l'aide de l'équation du pdf
                                    // tout en bas. */

    if (l[t][0] >
        l0) // Vérifie si le calcul de la longueur du ressort du domino 0 est
            // plus grande que sa longueur à vide car pour des petites valeurs
            // d'angles, la formule peut donner des valeurs supérieures.
      l[t][0] = l0; // Dans ce cas nous la remettons égale à la longueur à vide.
    if (l[t][0] < lmin) // A l'inverse, cette commande permet de vérifier que le
                        // ressort du domino 0 ne soit pas surcompréssé avec une
                        // longueur plus petite que la longueur minimale.
      l[t][0] =
          lmin; // Dans ce cas nous la remettons égale à la valeur minimale.

    alpha[t + 1][0] =
        (2 * alpha[t][0] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][0] +
         3 * g * dt * dt / (2 * h) * sin(alpha[t][0]) -
         dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][0])) /
        (1 +
         gamma * dt /
             (2 * J)); // Calcul et stockage dans le tableau des angles alpha de
                       // la valeur de l'angle alpha à l'instant t + dt pour le
                       // 1 er domino indice 0 après le choc avec son voisin le
                       // domino indice 1, à l'aide de l'équation du pdf n°2.

    if (alpha[t + 1][0] >= (M_PI / 2 - (Nmax) * (lmin / h))) {
      alpha[t + 1][0] = M_PI / 2 - (Nmax) * (lmin / h);
    } // Nous considérons ici l'angle formé par le premier domino
      // avec la verticale. Nous prenons en compte que l'angle maximal avec la
      // verticale est donnée par cette condition. En effet, l'angle min est
      // atteint lorsque tous les dominos sont couchés et donc que leur ressorts
      // ont tous une longueur de lmin. Nous avons dans ce cas fait
      // l'approximation aux petits angles en considerant que arctan((Nmax) *
      // (lmin / h)) =
      //(Nmax) * (lmin / h)

    /* mouvement domino n>=1 */
    int n = 1; // Initialisation du numéro du domino
               // domino n en contact avec domino n-1 et avec domino n+1

    while (
        alpha[t][n] > alphaChoc &&
        (n <
         Nmax -
             1)) // Traduit la condition : tant que le domino n est en contact
                 // avec son voisin (que l'angle alpha est supérieur à l'angle
                 // choc) et que le domino n existe (que n ne soit pas plus
                 // grand que le nombre maximal en indice de dominos).
    {
      l[t][n] =
          h * tan(alpha[t][n + 1] - alpha[t][n]) +
          delta / ((1. + tan(alpha[t][n]) * tan(alpha[t][n + 1])) *
                   cos(alpha[t][n])); // Calcul et stockage dans le tableau des
                                      // longueurs des ressorts l de la valeur
                                      // de la longueur l à l'instant t du
                                      // ressort du domino indice n, à l'aide de
                                      // l'équation du pdf tout en bas.

      if (l[t][n] >
          l0) // Vérifie si le calcul de la longueur du ressort du domino n est
              // plus grande que sa longueur à vide car pour des petites valeurs
              // d'angles, la formule peut donner des valeurs supérieures.
        l[t][n] =
            l0; // Dans ce cas nous la remettons égale à la longueur à vide.
      if (l[t][n] <
          lmin) // A l'inverse, cette commande permet de vérifier que le ressort
                // du domino 0 ne soit pas surcompréssé avec une longueur plus
                // petite que la longueur minimale.
        l[t][n] =
            lmin; // Dans ce cas nous la remettons égale à la valeur minimale.

      alpha[t + 1][n] =
          (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
           3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
           dt * dt * (1. / 2 * J) * k * (l0 - l[t][n - 1]) *
               (h - delta * sin(alpha[t][n - 1])) -
           dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][n])) /
          (1 + gamma * dt /
                   (2 * J)); // Calcul et stockage dans le tableau des angles
                             // alpha de la valeur de l'angle alpha à l'instant
                             // t + dt pour le domino d'indice n en contact avec
                             // ses 2 voisins à l'aide de l'équation du pdf n°4.

      if (alpha[t + 1][n] >= (M_PI / 2 - (Nmax - n) * (lmin / h))) {
        alpha[t + 1][n] = M_PI / 2 - (Nmax - n) * (lmin / h);
      }

      n++; // Permet de passer au domino suivant
    }

    if (n < Nmax) // Verification si il nous reste des dominos. Cette prochaine
                  // ligne est dédié au mouvement du domino n en contact avec
                  // domino n-1 (mais n'a pas encore touche domino n+1). Ainsi
                  // contrairemet à ce qui était codé au départ, le condition
                  // doit aller jusqu'au domino Nmax et pas Nmax - 1.
    {
      alpha[t + 1][n] =
          (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
           3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
           dt * dt * (1. / J) * k * (l0 - l[t][n - 1]) *
               (h - delta * sin(alpha[t][n - 1]))) /
          (1 +
           gamma * dt /
               (2 *
                J)); // Calcul et stockage dans le tableau des angles alpha de
                     // la valeur de l'angle alpha à l'instant t + dt pour le
                     // domino d'indice n à l'aide de l'équation du pdf n°3.

      if (alpha[t + 1][n] >= (M_PI / 2 - (lmin / h))) {
        alpha[t + 1][n] = M_PI / 2 - (lmin / h);
      }
    }

    n = Nmax - 2;  // Nous nous plaçons à l'avant dernier domino indice Nmax-2
    while (n >= 0) // Tant que nous désignons un domino avec la lettre n. Mise
                   // en place d'une sécurité : évite que le domino n traverse
                   // le domino n+1 (ça peut ariver lors de la simulation ...)
    {
      if (alpha[t + 1][n] >
          (alpha[t + 1][n + 1] + asin(delta * cos(alpha[t + 1][n + 1]) / h))) {
        alpha[t + 1][n] =
            alpha[t + 1][n + 1] + asin(delta * cos(alpha[t + 1][n + 1]) / h);
      }
      n = n - 1;
    }

    n = Nmax - 1; // On se place dans le cas du dernier domino (son ressort ne
                  // touche pas d'autre domino mais le sol)
    if (alpha[t][n] <=
        M_PI / 2 -
            atan(l0 /
                 h)) { // Si l'angle alpha du domino n est plus petit qu'une
                       // certaine valeur qui correspond à la valeur ou le
                       // ressort du domino entre en contact avec le sol
      l[t][n] = l0; // La longueur de son ressort correspond à la longueur du
                    // ressort à vide l0
    } else {        // Sinon, après contact du ressort avec le sol, alors :
      l[t][n] = l[t][n] =
          h * tan(M_PI / 2 - alpha[t][n]) +
          delta / ((1. + tan(alpha[t][n]) * tan(M_PI / 2)) *
                   cos(alpha[t][n])); // Calcul de la valeur de la longueur du
                                      // ressort l en fonction du temps. La
                                      // formule reste la même que celle donnée
                                      // dans le pdf avec juste un ajustement :
                                      // celui qu'il n existe pas de domino
                                      // après le dernier de la chaîne. Alors on
                                      // remplace alpha[t][n + 1] par la valeur
                                      // pi/2 soit 90 degrés car il s'agit de
                                      // l'angle entre la normale et le sol.
    }
  }

  save_Data(alpha, Tmax, Nmax,
            "alpha.txt"); // Sauvegarde du tableau alpha dans alpha.txt.
  save_Data(l, Tmax, Nmax,
            "longueur.txt"); // Sauvegarde du tableau l dans longueur.txt.

  trace_Graph(alpha, dt, Tmax,
              1); // Trace le graphe de l'évolution des angles alpha en fonction
                  // du temps (1 ici st un sélecteur pour savoir si nous voulons
                  // tracer alpha ou l)

  trace_Graph(l, dt, Tmax,
              2); // Trace le graphe de l'évolution de la longueur des ressorts
                  // en fonction du temps (2 ici st un sélecteur pour savoir si
                  // nous voulons tracer alpha ou l)

  // QUESTIONS :
  // Commenter le tracé des courbes.
  // Vitesse limite pprofil
}
