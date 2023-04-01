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
// l[t][n] est la longueur du ressort n a l'instant t.

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
  int Nmax; // Nombre de colonnes de nos 2 tableaux (équivalent au
            // nombre de dominos).
  cout << "Combien de dominos composent votre chef d'oeuvre artistique ? "
          "(Valeur "
          "conséillée : 10) ";
  cin >> Nmax;
  const int Tmax = 2000;  // Nombre de lignes maximale de nos 2 tableaux
                          // (équivalent au temps maximal).
  const double l0 = 3e-3; // Longueur du ressort au repos en m.
  double delta; // Correspond à la distance entre 2 dominos successifs en m.
  cout << endl
       << "Quelle est la distance (en mètres) qui sépare 2 dominos successifs "
          "éperdument amoureux l'un de l'autre et qui ne vont pas tarder à se "
          "rejoindre ^^ ? "
          "(Valeur conséillée 0.01 m) ";
  cin >> delta;
  double h; // Correspond à la taille en hauteur des dominos en m.
  cout << endl
       << "Quelle est la hauteur (en mètres) de vos dominos ? "
          "(Valeur conséillée 0.03 m) ";
  cin >> h;
  const double alphaChoc = trouve_Alpha(
      delta, l0,
      h); // Stocke la valeur de l'angle choc en rad dans la variable
          // alphaChoc en la déterminant à l'aide d'une formule utilisant de la
          // trigonométrie stocké dans la fonction trouve_Alpha.
  double w0 = M_PI / 4; // Vitesse de chute du domino en rad.s^(-1).
  cout << endl
       << "Quelle est la vitesse de rotation initale (en rad par seconde) du "
          "1er "
          "domino ? "
          "(Valeur conséillée pi sur 4 rad.s^-1 soit 0.7854 rad.s^(-1)) ";
  cin >> w0;
  const double dt = 0.001; // Intervalle de temps en s.
  double gamma;            // Définition de la viscosité moléculaire
                           // du milieu de propagation (ici l'air).
  cout
      << endl
      << "Quelle est la viscosité moléculaire (en Newton seconde par mètre) du "
         "milieu de propagation ? "
         "(Valeur conséillée 0.00001881 N.s.m^(-1) pour l'air,"
      << endl;
  cout << "sinon 0.00115 N.s.m^(-1) pour l'eau ou encore 6 N.s.m^(-1) pour le "
          "miel) ";
  cin >> gamma;
  double m; // Définition de la masse de l'objet en kg.
  cout << endl
       << "Quelle est la masse (en kilogramme) de vos dominos ? "
          "(Valeur conséillée 0.010 kg) ";
  cin >> m;
  const double J = m * h * h / 3; // Définition du moment d'inertie en kg.m².
  double g;                       // Définition de la pesanteur en m.s^(-2).
  cout << endl
       << "Quelle est la pesanteur (en mètre par seconde carré) de votre "
          "planète, car, après tout n'ooubliez pas que ce code a été codé par "
          "des M1 Astrophysique :) ? "
       << endl;
  cout << "(Valeur conséillée 9.81 m.s^(-2) pour la Terre, 3.7 m.s^(-2) pour "
          "Mercure, 8.87 m.s^(-2) pour Vénus, 3.71 m.s^(-2) pour Mars, 24.79 "
          "m.s^(-2) pour Jupiter,"
       << endl;
  cout << "10.44 m.s^(-2) pour Saturne, 8.69 m.s^(-2) pour "
          "Uranus et 11.15 m.s^(-2) pour Neptune) ";
  cin >> g;
  double k; // Définition de la constante du raideur du ressort en N.m^(-1).
  cout << endl
       << "Quelle est la constante de raideur du ressort (en Newton par "
          "mètre) des "
          "dominos dans cette modélisation ? "
          "(Valeur conséillée 1 N.m^(-1)) ";
  cin >> k;
  cout << endl
       << "Merci pour toutes ces informations, la simulation est à présent en "
          "cours de calcul... "
       << endl;
  cout << endl
       << "Histoire de patienter voici de quoi réfléchir : "
          "Patience et longueur de temps font plus que force ni que rage... "
          "Surtout en informatique, n'est-il pas ? :) "
       << endl;
  const double lmin =
      1e-4; // Longueur minimale du ressort proche de 0 mais
            // différet de 0 pour ne pas créer de problème
            // dans les formules lors des calculs et pour définir la longueur
            // minimale lors de l'impact avec le domino voisin ou le sol dans
            // le cas du dernier domino, avant décompression pour valeur
            // atteindre la longueur "d'équilibre" qui correspond au moment ou
            // la longueur sera stable, tout en supportant le poids de tous
            // les dominos précédents déjà écroulés. Elle est en m.

  double **alpha =
      new double *[Tmax]; // Déclaration du pointeur alpha qui pointera vers la
                          // case ou sera stockée la valeur de l'angle alpha de
                          // chaque domino.
  double **l = new double *[Tmax]; // Déclaration du pointeur l qui pointera
                                   // vers la case ou sera stockée la valeur de
                                   // la longueur du ressort l de chaque domino.

  /* Initialisation des 2 tableaux à 2 dimensions en allouant de la mémoire
   * dynamique pour y stocker des variables de type "double" qui seront la
   * valeur de l'angle alpha du domino n à l'nstant t, ainsi que la longueur de
   * son ressort à ce même instant : */

  creation_Matrice(
      alpha, Tmax, Nmax, 0.,
      M_PI / 2); // Créé le tableau alpha qui gardera en mémoire la valeur des
                 // angles de tous les dominos à chaque instant de l'expérience.
  creation_Matrice(l, Tmax, Nmax, l0,
                   lmin); // Créé le tableau l qui gardera en mémoire la valeur
                          // des longueurs des ressorts de tous les dominos à
                          // chaque instant de l'expérience.

  cout << endl
       << "L'angle de choc entre les 2 peremiers dominos d'indice 0 et 1 "
          "correspond à : "
       << alphaChoc << " rad." << endl; // Affiche la valeur de l'angle choc

  /* Initialisation de l'angle du premier domino a l'instant t+dt => t = 1 */

  alpha[1][0] =
      w0 *
      dt; // Stockage de la valeur de l'angle alpha du 1er domino à l'instant
          // t+dt qui correspond à t = 1. (Vitesse de chute * temps = angle).

  int t = 1; // Initialisation du temps t pour la suite du prog.

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

  cout << endl
       << "Le temps correspondant au choc du 1er domino d'indice 0 avec son "
          "voisin de droite (i.e. le 2ème domino d'indice 1) est : "
       << t_choc * dt << " secondes après le début de l'expérience."
       << endl; // Affiche la valeur du temps nécessaire avant le choc du domino
                // d'indice 0 avec le domino d'indice 1.

  /* Poursuite de la chute du 1er domino d'indice 0 après contact avec le
   * deuxième domino d'indice 1 */

  for (t = t_choc; t < Tmax - 1;
       t++) // Poursuite de l'expérience en parcourant le temps à partir de
            // l'instant du choc entre les 2 premiers dominos (t = t_choc),
            // jusqu'au moment où les dominos seront tous "à terre" (ou du
            // moins, lorsqu'il se chevaucheront tous) (t = Tmax-1).
  {
    /* Mouvement du 1er domino d'indice 0 après choc avec le 2ème domino n°1 */

    l[t][0] =
        h * tan(alpha[t][1] - alpha[t][0]) +
        delta / ((1. + tan(alpha[t][0]) * tan(alpha[t][1])) *
                 cos(alpha[t][0])); // Calcul et stockage dans le tableau des
                                    // longueurs des ressorts l de la valeur de
                                    // la longueur l à l'instant t du ressort du
                                    // 1er domino d'indice 0, à l'aide de
                                    // l'équation du pdf tout en bas. */

    if (l[t][0] > l0) // Vérifie si le calcul de la longueur du ressort du 1er
                      // domino d'indice 0 est plus grande que sa longueur à
                      // vide car pour des petites valeurs d'angles, la formule
                      // peut donner ce genre de valeur abérrantes.
      l[t][0] = l0; // Dans ce cas nous la remettons égale à la longueur à vide
                    // du ressort.
    if (l[t][0] <
        lmin) // À l'inverse, cette commande permet de vérifier que le
              // ressort du 1er domino d'indice 0 ne soit pas surcompréssé avec
              // une longueur plus petite que la longueur minimale car ici aussi
              // pour des petites valeurs
      // d'angles, la formule peut donner ce genre de valeur abérrantes (des
      // longueurs de rerssort négatives).
      l[t][0] = lmin; // Dans ce cas nous la remettons égale à la valeur
                      // minimale lors de sa compression.

    alpha[t + 1][0] =
        (2 * alpha[t][0] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][0] +
         3 * g * dt * dt / (2 * h) * sin(alpha[t][0]) -
         dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][0])) /
        (1 +
         gamma * dt /
             (2 *
              J)); // Calcul et stockage dans le tableau des angles alpha de
                   // la valeur de l'angle alpha à l'instant t + dt pour le
                   // 1 er domino d'indice 0 après le choc avec son voisin le
                   // 2ème domino d'indice 1, à l'aide de l'équation du pdf n°2.

    if (alpha[t + 1][0] >= (M_PI / 2 - (Nmax) * (lmin / h))) {
      alpha[t + 1][0] = M_PI / 2 - (Nmax) * (lmin / h);
    } // Nous considérons ici l'angle formé par le premier domino d'indice 0
      // avec la verticale. Nous prenons en compte que l'angle maximal est
      // donnée par la condition écrite ici. En effet, ce dernier est atteint
      // lorsque tous les dominos sont couchés les uns sur les autres et donc
      // que leur ressorts ont tous une longueur de lmin. Nous avons dans ce cas
      // fait l'approximation aux petits angles en considerant que arctan((Nmax)
      // * (lmin / h)) =
      //(Nmax) * (lmin / h)

    /* Mouvement du domino d'indice n>=1 */
    int n = 1; // Initialisation de l'indice du domino
               // (ici à 1) qui est en contact avec le domino d'indice n-1 et
               // celui d'indice n+1.

    while (
        alpha[t][n] > alphaChoc &&
        (n <
         Nmax - 1)) // Traduit la condition : tant que le domino d'indice n
                    // est en contact avec son voisin de droite (i.e. que
                    // l'angle alpha est supérieur à l'angle choc) et que
                    // l'indice n désigne bel et bien un domino autre que le
                    // dernier qui n'a naturellement pas de voisin à sa droite.
    {
      l[t][n] =
          h * tan(alpha[t][n + 1] - alpha[t][n]) +
          delta / ((1. + tan(alpha[t][n]) * tan(alpha[t][n + 1])) *
                   cos(alpha[t][n])); // Calcul et stockage dans le tableau des
                                      // longueurs des ressorts l de la valeur
                                      // de la longueur l à l'instant t du
                                      // ressort du domino d'indice n, à l'aide
                                      // de l'équation du pdf tout en bas.

      if (l[t][n] >
          l0) // Vérifie si le calcul de la longueur du ressort du nième + 1
              // domino d'indice n est plus grande que sa longueur à vide car
              // pour des petites valeurs d'angles, la formule peut donner ce
              // genre de valeurs aberrantes.
        l[t][n] =
            l0; // Dans ce cas nous la remettons égale à la longueur à vide.
      if (l[t][n] < lmin) // A l'inverse, cette commande permet de vérifier que
                          // le ressort du nième + 1 domino d'indice n ne soit
                          // pas surcompréssé avec une longueur plus petite que
                          // la longueur minimale car ici aussi
        // pour des petites valeurs
        // d'angles, la formule peut donner ce genre de valeur abérrantes (des
        // longueurs de rerssort négatives).
        l[t][n] = lmin; // Dans ce cas nous la remettons égale à la valeur
                        // minimale lors de sa compression.

      alpha[t + 1][n] =
          (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
           3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
           dt * dt * (1. / 2 * J) * k * (l0 - l[t][n - 1]) *
               (h - delta * sin(alpha[t][n - 1])) -
           dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][n])) /
          (1 +
           gamma * dt /
               (2 *
                J)); // Calcul et stockage dans le tableau des angles
                     // alpha de la valeur de l'angle alpha à l'instant
                     // t + dt pour le nième + 1 domino d'indice n en contact
                     // avec ses 2 voisins à l'aide de l'équation du pdf n°4.

      if (alpha[t + 1][n] >= (M_PI / 2 - (Nmax - n) * (lmin / h))) {
        alpha[t + 1][n] = M_PI / 2 - (Nmax - n) * (lmin / h);
      }

      n++; // Permet de passer au domino suivant
    }

    if (n < Nmax) // Verification s'il nous reste des dominos parmi tous les
                  // dominos y compris le dernier, qui ne seraientt pas encore
                  // en contact avec leur voisin de droite tout en étant en
                  // contact avec leur voisin de gauche. Ainsi, la prochaine
                  // ligne est dédié au mouvement du  nième + 1 domino d'indice
                  // n en contact avec le nième domino d'indice n-1 (mais qui
                  // n'a pas encore touché le nième + 2 domino d'indice n+1).
    {
      alpha[t + 1][n] =
          (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
           3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
           dt * dt * (1. / J) * k * (l0 - l[t][n - 1]) *
               (h - delta * sin(alpha[t][n - 1]))) /
          (1 + gamma * dt /
                   (2 * J)); // Calcul et stockage dans le tableau des angles
                             // alpha de la valeur de l'angle alpha à l'instant
                             // t + dt pour le nième + 1 domino d'indice n à
                             // l'aide de l'équation du pdf n°3.

      if (alpha[t + 1][n] >= (M_PI / 2 - (lmin / h))) {
        alpha[t + 1][n] = M_PI / 2 - (lmin / h);
      }
    }

    n = Nmax - 2; // Nous nous plaçons à l'avant dernier domino d'indice Nmax-2.
    while (n >= 0) // Tant que nous désignons un domino avec la lettre n. Mise
                   // en place d'une sécurité : évite que le domino n traverse
                   // le domino n+1 (ça peut ariver lors de la simulation ...).
    {
      if (alpha[t + 1][n] >
          (alpha[t + 1][n + 1] + asin(delta * cos(alpha[t + 1][n + 1]) / h))) {
        alpha[t + 1][n] =
            alpha[t + 1][n + 1] + asin(delta * cos(alpha[t + 1][n + 1]) / h);
      }
      n -= 1; // Décrémentation de l'indice parcourant les dominos pour
              // passer au domino inférieur.
    }

    n = Nmax - 1; // On se place dans le cas du dernier domino (son ressort ne
                  // touche pas d'autre domino mais le sol). Stockagfe dans une
                  // variable pour éviter de refaire le calcul plusieurs fois.
    if (alpha[t][n] >
        M_PI / 2 -
            atan(l0 / h)) { // Si l'angle alpha du nième + 1 domino d'indice n
                            // (ici le dernier domino car n vaut Nmax - 1) est
                            // plus grand qu'une certaine valeur qui correspond
                            // à la valeur où le ressort du dernier domino entre
                            // en contact avec le sol.
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

  trace_Graph(alpha, dt, Tmax, Nmax,
              1); // Trace le graphe de l'évolution des angles alpha en fonction
                  // du temps (1 ici st un sélecteur pour savoir si nous voulons
                  // tracer alpha ou l).

  trace_Graph(l, dt, Tmax, Nmax,
              2); // Trace le graphe de l'évolution de la longueur des ressorts
                  // en fonction du temps (2 ici st un sélecteur pour savoir si
                  // nous voulons tracer alpha ou l).

  // Libération de la mémoire pour les tableaux alpha et l
  for (int i = 0; i < Tmax; i++) { // Parcourt les lignes des 2 tableaux.
    delete[] alpha[i]; // delete [] permet de supprimer les valeurs de chaque
                       // colonne de la ligne i du tableau alpha.
    delete[] l[i];     // delete [] permet de supprimer les valeurs de chaque
                       // colonne de la ligne i du tableau l.
  }
  delete[] alpha; // Libère le pointeur alpha.
  delete[] l;     // Libère le pointeur l.

  return 0; // Renvoie 0 une fois que le code a été exécuté avec succès.

  // QUESTIONS :
  // Paramétrer Tmax correctement pour qu'il soit toujours supérieur au temps de
  // chute de tous les dominos.
  // Commenter conditions angles.
  // Commenter coonditions non transperçage des dominos voisins.
  // Vitesse limite profil.
}
