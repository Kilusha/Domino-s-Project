/*
 * Projet des Dominos C++
 *
 * main.cpp
 *
 * @auteurs PALAY Kiliann & SERRE Marina
 */

#include "graphique.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque graphique dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "matrice.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque matrice dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "sauvegardeDonnees.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque sauvegardeDonnes dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include "trouveAlpha.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque trouveAlpha dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include <cmath> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque cmath dans le programme, qui contient toutes les fonctions mathématiques.
#include <iostream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque iostream dans le programme, qui contient des fonctions permettant d'effectuer des entrées/sorties de données.
#include <string> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque string dans le programme, qui contient des fonctions qui vont être utilisées dans le code.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de
                     // l'espace de noms standard (std).

/* Pour propager les équations on fait des tableaux alpha et l a 2 indices (du
type alpha[t][n]) afin de conserver la valeur des angles aux différents
instants, ainsi que la longueur des ressorts de chaque dominos aux différents
instants. Nous construisons également un tableau v qui servira a enregistrer les
valeurs de la vitesse de l'onde de propagation à chaque instant. Il s'agira en
réalité de la vitesse linéaire de chaque domino selon l'axe de propagation de
l'onde. C'est pour cette raison que ce tableau possède également Nmax colonnes
et Tmax lignes. */

/* alpha[t][n] est l'angle alpha du domino n a l'instant t.
alpha[t+1][n] est l'angle alpha du domino n a l'instant t+dt.
alpha[t-1][n] est l'angle alpha du domino n a l'instant t-dt.
l[t][n] est la longueur du ressort n a l'instant t.
Et concernant le tableau v, il fonctionne de la même manière que le tableau
alpha ou encore l.*/

int main() { /* Fonction spéciale dans un programme C++ qui est appelée
             automatiquement lorsque le programme démarre. Elle est le point
             d'entrée du programme et définit l'endroit où l'exécution du
             programme commence. Elle doit être définie avec un type de
             retour "int" qui sera renvoyé en exécutant ce code si tout s'est
             bien déroulé. */

  /* Déclaration de toutes les variables utiles pour le programme */

  const double l0 = 3e-3; // Longueur du ressort au repos en m.

  const double dt = 0.001; // Intervalle de temps en s.

  double delta; // Correspond à la distance entre 2 dominos successifs en m.

  double h; // Correspond à la taille en hauteur des dominos en m.

  double w0; // Vitesse de chute du domino en rad.s^(-1).

  double gamma; /* Définition de la viscosité moléculaire
                du milieu de propagation (ici l'air). */

  double m; // Définition de la masse de l'objet en kg.

  double g; // Définition de la pesanteur en m.s^(-2).

  double k; // Définition de la constante du raideur du ressort en N.m^(-1).

  int c; /*  Simple compteur qui va nous servir à pouvoir afficher le temps
          de chute total de tous les dominos. */

  const double lmin =
      1e-4; /* Longueur minimale du ressort proche de 0 mais différent de 0 pour
               ne pas créer de problème dans les formules lors des calculs et
               pour définir la longueur minimale lors de l'impact avec le domino
               voisin ou le sol dans le cas du dernier domino, avant
               décompression pour valeur atteindre la longueur "d'équilibre" qui
               correspond au moment ou la longueur sera stable, tout en
               supportant le poids de tous les dominos précédents déjà écroulés.
               Elle est en m. */

  int Nmax; /* Nombre de colonnes de nos 2 tableaux (équivalent au
            nombre de dominos). */

  /* Toutes les boucles do while ci-dessous sont utilisées pour demander à
   * l'utilisateur les valeurs de chaque variable en ajoutant une sécurité afin
   * de ne pas planter le pogramme au cas où les valeurs rentrées sont erronées
   */

  string saisie; // Déclaration d'une variable nommée "saisie" de type string
                 // (chaine de caractères) qui va récupérer la saisie de
                 // l'utilisateur lorsqu'elle lui est demandée.

  do { // Exécute le code ci-dessous de manière certaine.

    cout << "Combien de dominos composent votre chef d'oeuvre artistique ? "
            "(Valeur "
            "conséillée : 10) : "; // Demande à l'utilisateur le nombre de
                                   // dominos qui composent sa chaine.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* La fonction/méthode find_first_not_of permet de vérifier si la chaîne de
     * caractères contient uniquement des chiffres (entre 0 et 9) en cherchant
     * la première occurence d'un caractère qui n'appartient pas à la chaine de
     * caractères placé en argument (ici tous les chgiffres de 0 à 9). Si elle
     * ne trouve pas de caractère qui n'est pas un chiffre, la méthode renvoie
     * la constante string::npos qui est de type size_t. qui vaut en général, la
     * valeur maximale que peut prendre un size_t (i.e. size_t-1). Elle traduit
     * l'absence de position valide ou de résultat dans les opérations de
     * recherche de chaînes de caractères.  Et par convention, lorsque
     * find_first_not_of ou find_last_not_of ne trouvent pas le caractère
     * recherché dans la chaîne de caractères, elles renvoient string::npos.
     * Ainsi, si la saisie de l'utilisateur ne contient aucun autre caractère,
     * dans ce cas la condition n'est pas vérifié, la comparaison renvoie un
     * booléen de la valeur Faux puisque la fonction renverra la valeur
     * string::npos. En revanche, si d'autres caractères sont contenus dans la
     * saisie de l'utilisateur, alors la fonction renverra la position dans la
     * saisie du caractère qui n'est pas un chiffre et donc la condition sera
     * varifiée et la comparaison renverra un booléen de la valeur True". Et le
     * code dans la boucle sera exécuté. */

    if (saisie.find_first_not_of("0123456789") != string::npos) {

      cerr << "Erreur : Vous devez entrer un nombre entier et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier. Ici, la commande "break;" nous arait totalement fait
                // soirtir de la boucle dans son entièreté (même de la boucle
                // while).
    }

    Nmax = stoi(saisie); // Convertit la chaîne de caractères entrée par
                         // l'utilisateur en entier puisqu'elle ne comporte que
                         // des chiffres, et la stocke dans la variable Nmax.

    if (Nmax == 0) // Si le nombre de domino est nul (le cas négatif ayant déjà
                   // été prévu dans le "if" précédent puisque le signe "-"
                   // n'est pas un chiffre).
    {
      cerr << "Erreur : Le nombre de dominos que vous avez choisi est "
              "incorrect. "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }

  } while (Nmax ==
           0); // Condition qui permet de répété la boucle do tant que le nombre
               // de domino entré par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout
        << endl
        << "Quelle est la distance (en mètres) qui sépare 2 dominos successifs "
           "éperdument amoureux l'un de l'autre et qui ne vont pas tarder à se "
           "rejoindre ^^ ? "
           "(Valeur conséillée 0.01 m) : "; // Demande à l'utilisateur la
                                            // distance qui sépare deux dominos
                                            // successifs.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici même principe que lors de la dernière utilisation de la méthode
     * find_first_not_of mais cette fois ci avec une chaîne de caractère qui
     * contient un point (qui fait office de virgule) car la valeur que doit
     * entrer l'utilisateur est un double donc nous pouvons nous attendre à la
     * présence d'une décimale. Si l'utilisateur entre un entier alors celui-ci
     * sera caster en doute par la suite donc il n'y a pas de problème. Nous
     * rajoutons juste la condition que la saisie ne soit pas uniquement égale à
     * un point sinon ça n'aurait pas de sens. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "supérieur ou égal à 0.004 m (limite de fonctionnement fixées "
              "par les formules)."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    delta = stod(saisie); // Convertit la chaîne de caractères entrée par
                          // l'utilisateur en double puisqu'elle ne comporte que
                          // des chiffres avec une virgule potentiellement, et
                          // la stocke dans la variable delta.

    if (delta == 0) { // Si l'espacement entre deux dominos successifs est
                      // nul (le cas négatif ayant déjà
                      // été prévu dans le "if" précédent puisque le signe "-"
                      // n'est pas un chiffre).
      cerr
          << "Erreur : La distance que vous avez choisie entre les dominos est "
             "incorrect (trop petite). "
             "Veuillez rééssayer. "
          << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (delta == 0); // Condition qui permet de répété la boucle do tant
                        // que la distance qui sépare 2 dominos successifs
                        // entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout << endl

         << "Quelle est la hauteur (en mètres) de vos dominos ? "
            "(Valeur conséillée 0.03 m) : "; // Demande à l'utilisateur la
                                             // hauteur des dominos qui
                                             // composent sa chaine.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    h = stod(saisie); // Convertit la chaîne de caractères entrée par
                      // l'utilisateur en double puisqu'elle ne comporte que
                      // des chiffres avec une virgule potentiellement, et la
                      // stocke dans la variable h.

    if (h == 0) { // Si la hauteur des dominos est nulle (le cas négatif ayant
                  // déjà été prévu dans le "if" précédent puisque le signe "-"
                  // n'est pas un chiffre).
      cerr << "Erreur : La hauteur des domninos que vous avez choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (h ==
           0); // Condition qui permet de répété la boucle do tant que la
               // hauteur des dominos entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout
        << endl
        << "Quelle est la vitesse de rotation initale (en rad par seconde) du "
           "1er "
           "domino ? "
           "(Valeur conséillée pi sur 4 rad.s^-1 soit 0.7854 rad.s^(-1)) : "; // Demande à l'utilisateur
    // la vitesse initiale du 1er domino qui compose sa chaine.

    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    w0 = stod(saisie); // Convertit la chaîne de caractères entrée par
                       // l'utilisateur en double puisqu'elle ne comporte que
                       // des chiffres et une virgule potentiellement, et la
                       // stocke dans la variable w0.

    if (w0 == 0) { // Si la vitesse de rotation initiale est nulle (le cas
                   // négatif ayant déjà été prévu dans le "if" précédent
                   // puisque le signe "-" n'est pas un chiffre).
      cerr << "Erreur : La vitesse de rotation initiale du 1er domino que vous "
              "avez "
              "choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (
      w0 ==
      0); // Condition qui permet de répété la boucle do tant que la vitesse de
          // rotation du 1er domino entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout << endl
         << "Quelle est la viscosité moléculaire (en Newton seconde par mètre) "
            "du "
            "milieu de propagation ? "
            "(Valeur conséillée 0.0000175 N.s.m^(-1) pour l'air,"
         << endl;
    cout
        << "sinon 0.00115 N.s.m^(-1) pour l'eau) : "; // Demande à l'utilisateur
                                                      // la viscosité
                                                      // moléculaire du milieu
                                                      // de propagation de
                                                      // l'onde de chute à
                                                      // travers les dominos.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    gamma = stod(saisie); // Convertit la chaîne de caractères entrée par
                          // l'utilisateur en double puisqu'elle ne comporte que
                          // des chiffres et pôtentiellement une virgule, et la
                          // stocke dans la variable gamma.

    if (gamma == 0) { // Si la viscosité du milieu de propagation est nulle (le
                      // cas négatif ayant déjà été prévu dans le "if" précédent
                      // puisque le signe "-" n'est pas un chiffre).
      cerr << "Erreur : La viscosité du milieu de propagation que vous avez "
              "choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (gamma == 0); // Condition qui permet de répété la boucle do tant que
                        // lla viscosité moléculaire du milieu de propagation
                        // entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout << endl
         << "Quelle est la masse (en kilogramme) de vos dominos ? "
            "(Valeur conséillée 0.01 kg) : "; // Demande à l'utilisateur la
                                              // masse des dominos qui composent
                                              // sa chaine.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    m = stod(saisie); // Convertit la chaîne de caractères entrée par
                      // l'utilisateur en double puisqu'elle ne comporte que
                      // des chiffres et potentiellement une virgule, et la
                      // stocke dans la variable m.

    if (m == 0) { // Si la masse des dominos est nulle (le
                  // cas négatif ayant déjà été prévu dans le "if" précédent
                  // puisque le signe "-" n'est pas un chiffre).
      cerr << "Erreur : La masse des domino que vous avez "
              "choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (m ==
           0); // Condition qui permet de répété la boucle do tant que la masse
               // des dominos entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout
        << endl
        << "Quelle est la pesanteur (en mètre par seconde carré) de votre "
           "planète, car, après tout n'ooubliez pas que ce code a été codé par "
           "des M1 Astrophysique :) ? "
        << endl;
    cout << "(Valeur conséillée 9.81 m.s^(-2) pour la Terre, 3.7 m.s^(-2) pour "
            "Mercure, 8.87 m.s^(-2) pour Vénus, 3.71 m.s^(-2) pour Mars, 24.79 "
            "m.s^(-2) pour Jupiter,"
         << endl;
    cout << "10.44 m.s^(-2) pour Saturne, 8.69 m.s^(-2) pour "
            "Uranus et 11.15 m.s^(-2) pour Neptune) : "; // Demande à
                                                         // l'utilisateur le
                                                         // champ de pesanteur
                                                         // de la planète sur
                                                         // laquelle il réalise
                                                         // son expérience.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    g = stod(saisie); // Convertit la chaîne de caractères entrée par
                      // l'utilisateur en double puisqu'elle ne comporte que
                      // des chiffres et une virgule potentiellement, et la
                      // stocke dans la variable g.

    if (g == 0) { // Si la pesanteur est nulle (le
                  // cas négatif ayant déjà été prévu dans le "if" précédent
                  // puisque le signe "-" n'est pas un chiffre).
      cerr << "Erreur : La pesanteur que vous avez "
              "choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (g == 0); // Condition qui permet de répété la boucle do tant que la
                    // pesanteur entrée par l'utilisateur n'est pas valide.

  do { // Exécute le code ci-dessous de manière certaine.
    cout << endl
         << "Quelle est la constante de raideur du ressort (en Newton par "
            "mètre) des "
            "dominos dans cette modélisation ? "
            "(Valeur conséillée 1 N.m^(-1)) : "; // Demande à l'utilisateur la
                                                 // constante de raideur des
                                                 // ressorts qui sont fixés sur
                                                 // chaque domino.
    cin >> saisie; // Stocke l'entrée de l'utilisateur comme une chaine de
                   // caractères dans la variable saisie.

    /* Ici exactement même principe que précédemment pour vérifier si la valeur
     * entrer par l'utilisateur est bien un double ou un entier peu importe. */

    if (saisie.find_first_not_of("0123456789.") != string::npos ||
        saisie == ".") {

      cerr << "Erreur : Vous devez entrer un nombre réel et strictement "
              "positif."
           << endl; //, Une erreur est affichée
      continue; // Permet de relancer la boucle à partir du début du do sans
                // traiter la suite des caractères contenu dans la chaîne de
                // caractères puisque nous savons déjà que ce n'est pas un
                // entier ou un double. Ici, la commande "break;" nous arait
                // totalement fait soirtir de la boucle dans son entièreté (même
                // de la boucle while).
    }

    k = stod(saisie); // Convertit la chaîne de caractères entrée par
                      // l'utilisateur en double puisqu'elle ne comporte que
                      // des chiffres et une virgule potentiellement, et la
                      // stocke dans la variable k.

    if (k == 0) { // Si la constante de raideur des ressorts des dominos est
                  // nulle (le cas négatif ayant déjà été prévu dans le "if"
                  // précédent puisque le signe "-" n'est pas un chiffre).
      cerr << "Erreur : La constante de raideur des ressorts de chaque domino "
              "que vous "
              "avez "
              "choisie est "
              "incorrect (trop petite). "
              "Veuillez rééssayer. "
           << endl; // Demande une nouvelle saisie à l'utilisateur.
    }
  } while (
      k ==
      0); // Condition qui permet de répété la boucle do tant que la constante
          // de raideur des ressorts entrée par l'utilisateur n'est pas valide.

  const double alphaChoc = trouve_Alpha(
      delta, l0, h,
      Nmax); /* Stocke la valeur de l'angle choc en rad dans la variable
       alphaChoc en la déterminant à l'aide d'une formule utilisant de
       la trigonométrie stocké dans la fonction trouve_Alpha. */

  const double J = m * h * h / 3; // Définition du moment d'inertie en kg.m².

  cout << endl
       << "Merci pour toutes ces informations, la simulation est à présent en "
          "cours de calcul... "
       << endl; // Affiche un message de remerciement.
  cout << endl
       << "Histoire de patienter voici de quoi réfléchir : "
          "Patience et longueur de temps font plus que force ni que rage... "
          "Surtout en informatique, n'est-il pas ? :) "
       << endl; // Affiche un message de méditation le temps de l'affichage des
                // graphes.

  int Tmax; /* Déclaration du nombre de lignes maximale de nos 2 tableaux
            (équivalent au temps maximal). */

  /*  Attention : Étant donné que le programme de base disponnible sur le
   * moodle nous faisait travailler avec des tableaux (pointeurs), nous avons
   * alors continué. Cependant, les vecteurs auraient été bien plus approprié
   * étant donné qu'ils ont l'avantage d'avoir une taille non fixe, que l'on
   * peut agrandir au fil du code. Ici la taille des tableaux doit-être fixe
   * lors de sa déclaration même si l'allocation de mémoire se fait
   * dynamiquement.Cela nous oblige à faire une étude (tester toutes les
   * combinaisons possibles avec notre code) pour prévoir la taille du tableau
   * qu'il nous faut afin d'éviter tout problème de segmentation. C'est donc
   * ce que nous avons réalisé dans les lignes de codes ci-dessous. La seule
   * chose que nous n'avons pas pris en compte pour éviter d'allonger le code
   * est un nombre de domino trop important. En effet il faudrait agrandir la
   * fenêtre où le graphique est tracé pour voir apparaître la chute de 100
   * dominos par exemple. Mais nous ne l'avons volontairement pas prévu pour
   * éviter un code trop lourd et inutile. Sachant qu'ici, nous proposons déjà
   * pas mal de combinaisons possibles et sympathiques avec 10 dominos ou plus
   * (15 dominos par exemple). */

  /* Attention : Évidemment les tests réalisés sur les différentes planètes à
   * travers cette simulation ne sont pas à prendre au sérieux, l'atmosphère
   * terrestre ne représentant pas l'atmosphère de toutes les planètes
   * malheureusement. Les simulations sont donc faite avec l'hyppothèse que
   * les planètes ont un atmosphère avec la même viscosité moléculaire que
   * celle de la Terre. */

  /* Les prochaines lignes de codes sont écrites pour pouvoir dimensionner les
   * tableaux alpha, l, et v en fonction des paramètres de l'expérience qui ont
   * été choisies par l'utilisateur */

  if (gamma == 0.00115) { // Si le fluide choisi est l'eau.
    if (g == 24.79) {     // Si Jupiter est choisie.
      Tmax = 12000;       // Nombre de lignes maximale de nos 2 tableaux
                          // (équivalent au temps maximal).
    } else if (g == 11.15 || g == 10.44 ||
               g == 9.81) { // Si Neptune, Saturne ou Jupiter est choisie.
      Tmax = 20000;         // Nombre de lignes maximale de nos 2 tableaux
                            // (équivalent au temps maximal).
    } else if (g == 8.69 || g == 8.87) { // Si Uranus ou Venus est choisie.
      Tmax = 22000; // Nombre de lignes maximale de nos 2 tableaux
                    // (équivalent au temps maximal).
    } else {        // Si Mars ou Mercure est choisie.
      Tmax = 40000; // Nombre de lignes maximale de nos 2 tableaux
                    // (équivalent au temps maximal).
    }
  } else {       // Si le fluide choisie est l'air.
    Tmax = 2000; // Nombre de lignes maximale de nos 2 tableaux
                 // (équivalent au temps maximal).
  }

  double **alpha =
      new double *[Tmax]; /* Déclaration du pointeur alpha qui pointera vers
                          la case ou sera stockée la valeur de l'angle
                          alpha de chaque domino. */

  double **l = new double *[Tmax]; /* Déclaration du pointeur l qui pointera
                                   vers la case ou sera stockée la valeur de
                                   la longueur du ressort l de chaque domino. */
  double **v = new double
      *[Tmax]; /* Déclaration du pointeur v qui pointera
               vers la case ou sera stockée la valeur de
               la vitesse de propagation de l'onde en fonction du domino. */

  /* Initialisation des 2 tableaux à 2 dimensions en allouant de la mémoire
   * dynamique pour y stocker des variables de type "double" qui seront la
   * valeur de l'angle alpha du domino n à l'nstant t, ainsi que la longueur
   * de son ressort à ce même instant : */

  creation_Matrice(
      alpha, Tmax, Nmax, 0.,
      M_PI / 2); // Créé le tableau alpha qui gardera en mémoire la valeur des
                 // angles de tous les dominos à chaque instant de l'expérience.
  creation_Matrice(l, Tmax, Nmax, l0,
                   lmin); /* Créé le tableau l qui gardera en mémoire la
                                      valeur des longueurs des ressorts de tous
                             les dominos à chaque instant de l'expérience. */
  creation_Matrice(
      v, Tmax, Nmax, 0.,
      0.); /* Créé le tableau v qui gardera en mémoire la
                       valeur des vitesses de propagation linéaire de tous
                       les dominos à chaque instant de l'expérience. */

  if (Nmax == 1) { // Si l'utilisateur décide faire une chaine composé que d'un
                   // seul domino.
    cout << endl
         << "Vous avez choisi un seul domino. Celui-ci n'ayant pas de "
            "voisin, il ne peut donc pas entrer en collision avec qui que ce "
            "soit. L'angle choc n'existe donc pas."
         << endl;

  } else { // Si la chaine de dominos comporte plus de 1 domino.

    if (delta > h) { // Si la distance choisie entre les dominos par
                     // l'utilisateur est supérieure à la taille des dominos.
      cout << endl
           << "Vous avez choisi une distance entre vos dominos plus grande que "
              "la "
              "hauteur de vos dominos. Ainsi il ne peut pas y avoir de choc. "
           << "L'angle choc n'existe donc pas, le seul domino, "
              "qui chute n'entrant en contact avec aucun autre domino."
           << endl;

    } else { // Si la distance choisie par l'utilisateur entre les dominos est
             // correcte pour qu'il y ait un choc lors de la chute de ces
             // derniers.

      cout << endl
           << "L'angle choc entre les 2 premiers dominos d'indice 0 et 1 "
              "correspond à : "
           << alphaChoc << " rad, soit : " << alphaChoc * 180 / M_PI
           << " degrés." << endl; // Affiche la valeur de l'angle choc
    }
  }

  /* Initialisation de l'angle du premier domino a l'instant t+dt => t = 1 */

  alpha[1][0] =
      w0 *
      dt; /* Stockage de la valeur de l'angle alpha du 1er domino à l'instant
          t+dt qui correspond à t = 1. (Vitesse de chute * temps = angle). */

  int t = 1; // Initialisation du temps t pour la suite du prog.

  v[t][0] = (sin(alpha[t][0]) - sin(alpha[t - 1][0])) * h /
            dt; // Calcul de la vitesse de propagation de l'onde à travers le
                // 1er domino d'indice 0.

  /* Description du mouvement du 1er domino jusqu'au choc*/

  while (alpha[t][0] <
         alphaChoc) { // Condition portant sur l'angle signifiant : Tant que le
                      // premier domino n'entre pas en contact avec son voisin.
    alpha[t + 1][0] =
        (2 * alpha[t][0] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][0] +
         (3 * g * dt * dt / (2 * h)) * sin(alpha[t][0])) /
        (1 +
         gamma * dt /
             (2 * J)); /* Calcul et stockage dans le tableau des angles alpha de
                       la valeur de l'angle alpha à l'instant t + dt pour le 1
                       er domino indice 0, à l'aide de l'équation du pdf n°1. */

    v[t][0] = (sin(alpha[t + 1][0]) - sin(alpha[t][0])) * h /
              dt; // Calcul de la vitesse de propagation de l'onde à travers le
                  // 1er domino d'indice 0.

    t++; // Incrémentation du temps pour changer de ligne dans notre tableau
    // et pour passer à l'instant suivant. Ajout de 1 à t donc de dt à t.
  }

  /* Sortie de la boucle while. Ainsi le temps t correspond au temps pour
   * lequel il y a le choc entre le domino 0 et le domino 1 */

  int t_choc = t; /* Sauvegarde de la valeur du temps requis avant le choc
                  entre le domino 0 et le domino 1. */

  if (alphaChoc !=
      M_PI / 2) { // Nous posons cette condition qui permet de ne pas annoncer
                  // la valeur de l'angle choc si ce dernier n'existe pas.

    cout << endl
         << "Le temps correspondant au choc du 1er domino d'indice 0 avec son "
            "voisin de droite (i.e. le 2ème domino d'indice 1) est de : "
         << t_choc * dt << " secondes après le début de l'expérience."
         << endl; // Affiche la valeur du temps nécessaire avant le choc du
                  // domino d'indice 0 avec le domino d'indice 1.
  }

  /* Poursuite de la chute du 1er domino d'indice 0 après contact avec le
   * deuxième domino d'indice 1 */

  for (t = t_choc; t < Tmax - 1;
       t++) /* Poursuite de l'expérience en parcourant le temps à partir de
            l'instant du choc entre les 2 premiers dominos (t = t_choc),
            jusqu'au moment où les dominos seront tous "à terre" (ou du
            moins, lorsqu'il se chevaucheront tous) (t = Tmax-1). */
  {
    /* Mouvement du 1er domino d'indice 0 après choc avec le 2ème domino n°1 */

    if (alphaChoc == M_PI / 2) { // Si il n'y a aucun choc car 1 seul domino ou
                                 // distance trop grande entre les dominos.
      l[t][0] =
          h * tan(M_PI / 2 - alpha[t][0]) +
          delta / ((1. + tan(alpha[t][0]) * tan(M_PI / 2)) *
                   cos(alpha[t][0])); /* Calcul et stockage dans le tableau des
                                        longueurs des ressorts l de la valeur de
                                        la longueur l à l'instant t du ressort
                                        du 1er domino d'indice 0, à l'aide de
                                        l'équation du pdf tout en bas. */

    } else {

      l[t][0] =
          h * tan(alpha[t][1] - alpha[t][0]) +
          delta / ((1. + tan(alpha[t][0]) * tan(alpha[t][1])) *
                   cos(alpha[t][0])); /* Calcul et stockage dans le tableau des
                                        longueurs des ressorts l de la valeur de
                                        la longueur l à l'instant t du ressort
                                        du 1er domino d'indice 0, à l'aide de
                                        l'équation du pdf tout en bas. */
    }

    if (l[t][0] > l0) /* Vérifie si le calcul de la longueur du ressort du 1er
                      domino d'indice 0 est plus grande que sa longueur à
                      vide car pour des petites valeurs d'angles, la
                      formule peut donner ce genre de valeur abérrantes. */
      l[t][0] = l0;   /* Dans ce cas nous la remettons égale à la longueur à
                      vide du ressort. */
    if (l[t][0] < lmin) /* À l'inverse, cette commande permet de vérifier que le
                        ressort du 1er domino d'indice 0 ne soit pas
                        surcompréssé avec une longueur plus petite que la
                        longueur minimale car ici aussi pour des petites valeurs
                        d'angles, la formule peut donner ce genre de valeur
                        abérrantes (des longueurs de rerssort négatives). */
      l[t][0] = lmin;   /* Dans ce cas nous la remettons égale à la valeur
                        minimale lors de sa compression. */

    alpha[t + 1][0] =
        (2 * alpha[t][0] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][0] +
         3 * g * dt * dt / (2 * h) * sin(alpha[t][0]) -
         dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][0])) /
        (1 +
         gamma * dt / (2 * J)); /* Calcul et stockage dans le tableau des angles
                                alpha de la valeur de l'angle alpha à l'instant
                                t + dt pour le 1 er domino d'indice 0 après le
                                choc avec son voisin le 2ème domino d'indice 1,
                                à l'aide de l'équation du pdf n°2. */

    if (delta < h &&
        alpha[t + 1][0] >=
            (M_PI / 2 -
             (Nmax)*atan(
                 (lmin /
                  h)))) { /* Nous considérons ici l'angle maximal que peut formé
                             le premier domino d'indice 0 avec la verticale.
                             Cette condition est atteinte lorsque tous les
                             dominos (soit Nmax) sont couchés les uns sur les
                             autres et donc que leur ressorts ont tous une
                             longueur de lmin. si le calcul de l'angle a donné
                             une valeur supérieure à celle ci : */

      alpha[t + 1][0] =
          M_PI / 2 -
          (Nmax)*atan(
              (lmin /
               h)); // Alors on fixe la valeur erronnée à la valeur maximale.

    } else if (delta > h && // Nous différencions les delta supérieur à h ou non
                            // car lorsque ce dernier est trop grand, il ne faut
                            // pas prendre en compte tous les dominos. Il faut
                            // utiliser uniquement le 1er domino.
               alpha[t + 1][0] >=
                   (M_PI / 2 - (1) * atan((lmin / h)))) { /* Nous considérons
              ici l'angle maximal que peut formé le premier domino d'indice 0
              avec la verticale. Cette condition est atteinte lorsque tous les
              dominos (soit Nmax) sont couchés les uns sur les
              autres et donc que leur ressorts ont tous une
              longueur de lmin. si le calcul de l'angle a donné
              une valeur supérieure à celle ci : */

      alpha[t + 1][0] =
          M_PI / 2 -
          (1) *
              atan((
                  lmin /
                  h)); // Alors on fixe la valeur erronnée à la valeur maximale.
    }

    /* Mouvement du domino d'indice n>=1 */

    if (alphaChoc !=
        M_PI / 2) { // Si il existe plus de 1 dominos et que la distance
                    // séparant 2 dominos successifs n'est pas trop grande.

      int n = 1; /* Initialisation de l'indice du domino
                 (ici à 1) qui est en contact avec le domino d'indice n-1 et
                 celui d'indice n+1. */

      while (alpha[t][n] > alphaChoc &&
             (n < Nmax - 1)) /* Traduit la condition : tant que le domino
                    d'indice n est en contact avec son voisin de droite (i.e.
                    que l'angle alpha est supérieur à l'angle choc) et que
                    l'indice n désigne bel et bien un domino autre que le
                    dernier qui n'a naturellement pas de voisin à sa droite. */
      {
        l[t][n] =
            h * tan(alpha[t][n + 1] - alpha[t][n]) +
            delta /
                ((1. + tan(alpha[t][n]) * tan(alpha[t][n + 1])) *
                 cos(alpha[t][n])); /* Calcul et stockage dans le tableau des
                                      longueurs des ressorts l de la valeur
                                      de la longueur l à l'instant t du
                                      ressort du domino d'indice n, à l'aide
                                      de l'équation du pdf tout en bas. */

        if (l[t][n] >
            l0) /* Vérifie si le calcul de la longueur du ressort du nième + 1
                domino d'indice n est plus grande que sa longueur à vide car
                pour des petites valeurs d'angles, la formule peut donner ce
                genre de valeurs aberrantes. */
          l[t][n] =
              l0; // Dans ce cas nous la remettons égale à la longueur à vide.
        if (l[t][n] < lmin) /* À l'inverse, cette commande permet de vérifier
                            que le ressort du nième + 1 domino d'indice n ne
                            soit pas surcompréssé avec une longueur plus
                            petite que la longueur minimale car ici aussi
                            pour des petites valeurs
                            d'angles, la formule peut donner ce genre de valeur
                            abérrantes (des longueurs de rerssort négatives). */
          l[t][n] = lmin;   /* Dans ce cas nous la remettons égale à la valeur
                            minimale lors de sa compression. */

        alpha[t + 1][n] =
            (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
             3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
             dt * dt * (1. / 2 * J) * k * (l0 - l[t][n - 1]) *
                 (h - delta * sin(alpha[t][n - 1])) -
             dt * dt * k * h * (1 / (2 * J)) * (l0 - l[t][n])) /
            (1 +
             gamma * dt /
                 (2 *
                  J)); /*  Calcul et stockage dans le tableau des angles
                        alpha de la valeur de l'angle alpha à l'instant
                        t + dt pour le nième + 1 domino d'indice n en contact
                        avec ses 2 voisins à l'aide de l'équation du pdf n°4. */

        if (alpha[t + 1][n] >= (M_PI / 2 - (Nmax - n) * atan((lmin / h)))) {
          alpha[t + 1][n] = M_PI / 2 - (Nmax - n) * atan((lmin / h));
        } /* Nous considérons ici l'angle maximal que peut formé le n-ieme +1
          domino d'indice n
          avec la verticale. Cette condition est atteinte
          lorsque tous les dominos suivant (soit Nmax-n) sont couchés les uns
          sur les autres et donc que leur ressorts ont tous une longueur de
          lmin. */

        n++; // Permet de passer au domino suivant
      }

      if (n < Nmax) /* Verification s'il nous reste des dominos parmi tous les
                    dominos y compris le dernier, qui ne seraientt pas encore
                    en contact avec leur voisin de droite tout en étant en
                    contact avec leur voisin de gauche. Ainsi, la prochaine
                    ligne est dédié au mouvement du  nième + 1 domino d'indice
                    n en contact avec le nième domino d'indice n-1 (mais qui
                    n'a pas encore touché le nième + 2 domino d'indice n+1). */
      {
        alpha[t + 1][n] =
            (2 * alpha[t][n] - (1 - gamma * dt / (2 * J)) * alpha[t - 1][n] +
             3 * g * dt * dt / (2 * h) * sin(alpha[t][n]) +
             dt * dt * (1. / J) * k * (l0 - l[t][n - 1]) *
                 (h - delta * sin(alpha[t][n - 1]))) /
            (1 + gamma * dt /
                     (2 * J)); /* Calcul et stockage dans le tableau des angles
                               alpha de la valeur de l'angle alpha à
                               l'instant t + dt pour le nième + 1 domino
                               d'indice n à l'aide de l'équation du pdf n°3. */

        if (alpha[t + 1][n] >= (M_PI / 2 - atan((lmin / h)))) {
          alpha[t + 1][n] = M_PI / 2 - atan((lmin / h));
        }

      } /* Nous considérons ici l'angle maximal que peut former le dernier
        domino avec la verticale. Cette condition est atteinte lorsque ce domino
        est couché et que que son ressort a une longueur lmin. */

      n = Nmax -
          2; // Nous nous plaçons à l'avant dernier domino d'indice Nmax-2.
      while (n >=
             0) /* Tant que nous désignons un domino avec la lettre n. Mise
                  en place d'une sécurité : évite que le domino n traverse
                  le domino n+1 (ça peut ariver lors de la simulation ...). */
      {
        if (alpha[t + 1][n] > (alpha[t + 1][n + 1] +
                               asin(delta * cos(alpha[t + 1][n + 1]) / h))) {
          alpha[t + 1][n] =
              alpha[t + 1][n + 1] + asin(delta * cos(alpha[t + 1][n + 1]) / h);
        } /* Condition si l'angle d'inclinaison du domino d'indice n est
        trop grand par rapport à l'angle d'inclinaison du domino à sa droite
        d'indice n+1, alors l'angle d'inclinaison de ce premier sera ajusté pour
        éviter que les dominos se transpercent les uns les autres. */

        v[t][n] = (sin(alpha[t + 1][n]) - sin(alpha[t][n])) * h /
                  dt; // Calcul de la vitesse de propagation de l'onde à travers
                      // le nième + 1 domino d'indice n.

        n -= 1; /* Décrémentation de l'indice parcourant les dominos pour
                passer au domino inférieur. */
      }
    }

    int n = Nmax - 1; /* On se place dans le cas du dernier domino (son ressort
                 ne touche pas d'autre domino mais le sol). Stockagfe dans une
                 variable pour éviter de refaire le calcul plusieurs fois. */

    v[t][n] = (sin(alpha[t + 1][n]) - sin(alpha[t][n])) * h /
              dt; // Calcul de la vitesse de propagation de l'onde à travers le
                  // ernier domino d'indice Nmax - 1.

    if (alpha[t][n] >
        M_PI / 2 -
            atan(l0 / h)) { /* Si l'angle alpha du nième + 1 domino d'indice n
                              (ici le dernier domino car n vaut Nmax - 1) est
                              plus grand qu'une certaine valeur qui
                              correspond à la valeur où le ressort du dernier
                              domino entre en contact avec le sol. */
      l[t][n] =
          h * tan(M_PI / 2 - alpha[t][n]) +
          delta / ((1. + tan(alpha[t][n]) * tan(M_PI / 2)) *
                   cos(alpha[t][n])); /* Calcul de la valeur de la longueur du
                                        ressort l en fonction du temps. La
                                        formule reste la même que celle donnée
                                        dans le pdf avec juste un ajustement :
                                        celui qu'il n existe pas de domino
                                        après le dernier de la chaîne. Alors on
                                        remplace alpha[t][n + 1] par la valeur
                                        pi/2 soit 90 degrés car il s'agit de
                                        l'angle entre la normale et le sol. */

      if (l[t][0] > l0) /* Vérifie si le calcul de la longueur du ressort du 1er
                           domino d'indice 0 est plus grande que sa longueur à
                           vide car pour des petites valeurs d'angles, la
                           formule peut donner ce genre de valeur abérrantes. */
        l[t][0] = l0; /* Dans ce cas nous la remettons égale à la longueur à
                      vide du ressort. */
      if (l[t][0] <
          lmin) { /* À l'inverse, cette commande permet de vérifier que le
                ressort du 1er domino d'indice 0 ne soit pas
                surcompréssé avec une longueur plus petite que la
                longueur minimale car ici aussi pour des petites valeurs
                d'angles, la formule peut donner ce genre de valeur
                abérrantes (des longueurs de rerssort négatives). */
        l[t][0] = lmin; /* Dans ce cas nous la remettons égale à la valeur
                        minimale lors de sa compression. */
      }
    }

    /* Lignes suivantes permettent d'afficher le temps de chute de tous les
     * dominos */

    if ((c == 0 &&
         alpha[t][Nmax - 1] ==
             alpha[t - 1]
                  [Nmax - 1] && // Nous veillons à faire la différence sur le
                                // delta par rapport au h car selon sa valeur,
                                // il faut ou non prendre en compte l'ensemble
                                // des dominos (ainsi il faut changer l'indice
                                // des angle alpha que l'on compare).
         alpha[t - 1][Nmax - 1] != 0 &&
         delta < h) ||
        (c == 0 && alpha[t][0] == alpha[t - 1][0] && alpha[t - 1][0] != 0 &&
         delta > h)) { /* Traduit la condition : si le compteur est à 0 et que
         les deux valeurs des angles alphas successives du dernier domino
         sont différentes de 0 et égales, alors dans ce cas : */

      cout << endl
           << "Le temps de chute total de votre chaine de domino est de : "
           << t * dt << " secondes."
           << endl; /* Affichage du temps de chute globale qui correspond à la
                    durée de l'expérience. */
      c++; /* Incrémentation du compteur de 1 pour nous permettre de ne passer
           qu'une fois dans cette boucle. */
    }
  }

  sauvegarde_Donnees(alpha, Tmax, Nmax,
            "alpha.txt"); // Sauvegarde du tableau alpha dans alpha.txt.

  sauvegarde_Donnees(l, Tmax, Nmax,
            "longueur.txt"); // Sauvegarde du tableau l dans longueur.txt.

  sauvegarde_Donnees(v, Tmax, Nmax,
            "vitesse.txt"); // Sauvegarde du tableau v dans vitesse.txt.

  trace_Graph(alpha, dt, Tmax, Nmax,
              1); /* Trace le graphe de l'évolution des angles alpha en
                    fonction du temps (1 ici st un sélecteur pour savoir si
                    nous voulons tracer alpha ou l ou v). */

  if (delta < h) { // Nous avons besoin de faire cette disjonction de cas sinon
                   // le graphique s'affiche avec une echelle en ordonnée qui
                   // est troip importante (c'est le seul cas où ça le fait sans
                   // savoir réellement pourquoi).
    trace_Graph(
        v, dt, Tmax, Nmax,
        3); /* Trace le graphe de l'évolution de la vitesse de propagation de
               l'onde de chute en fonction du temps (3 ici st un sélecteur pour
               savoir si nous voulons tracer alpha ou l ou v). */
  } else {
    trace_Graph(
        v, dt, Tmax, 1,
        3); /* Trace le graphe de l'évolution de la vitesse de propagation de
               l'onde de chute en fonction du temps (3 ici st un sélecteur pour
               savoir si nous voulons tracer alpha ou l ou v). */
  }

  trace_Graph(l, dt, Tmax, Nmax,
              2); /* Trace le graphe de l'évolution de la longueur des
                    ressorts en fonction du temps (2 ici st un sélecteur pour
                    savoir si nous voulons tracer alpha ou l ou v). */

  // Libération de la mémoire pour les tableaux alpha et l
  for (int i = 0; i < Tmax; i++) { // Parcourt les lignes des 2 tableaux.
    delete[] alpha[i]; // delete [] permet de supprimer les valeurs de chaque
                       // colonne de la ligne i du tableau alpha.
    delete[] l[i];     // delete [] permet de supprimer les valeurs de chaque
                       // colonne de la ligne i du tableau l.
    delete[] v[i];
  }
  delete[] alpha; // Libère le pointeur alpha.
  delete[] l;     // Libère le pointeur l.
  delete[] v;     // Libère le pointeur l.

  return 0; // Renvoie 0 une fois que le code a été exécuté avec succès.
}
