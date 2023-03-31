#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;
// Trame pour projet domino a inserer dans votre programme
// J=m*h*h/3 est le moment d'inertie.
// alpha[t][n] est l'angle alpha du domino n a l'instant t.
// alpha[t+1][n] est l'angle alpha du domino n a l'instant t+dt.
// alpha[t-1][n] est l'angle alpha du domino n a l'instant t-dt.
// l[t][n] est la longueur du ressort n a l'instant t

// Pour propager les équations on fait des tableaux alpha et l a 2 indices (du
// type alpha[t][n]) afin de conserver la valeur des angles aux différents
// instants.

/* Création de la fonction calcul_Membre_Gauche qui permet de calculer le membre
 * de gauche trouvé dans la partie théorique qui est censé valoir 0 lorsqu'un
 * domino entre en contact avec son voisin. Ainsi il nous permettra de
 * déterminer le bon angle alpha qui correspond à l'angle de choc */

double calcul_Membre_Gauche(double alphaChoc, double delta, double l0,
                            double h) {
  return sin(alphaChoc) - (delta - l0 * cos(alphaChoc)) / h;
}

/* Création de la fonction trouve_Alpha qui permet de déterminer par dichotomie
 * la valeur de l'angle pour lequel un domino entre en contact avec son voisin
 */

double trouve_Alpha(double delta, double l0, double h) {
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
}

/* Création d'une fonction créant les matrices alpha et l qui prend
 * respectivementcomme argument le nom de la matrice, le nombre de lignes, le
 * nombre de colonnes, la valeur par défaut et une valeur spéciale réservé à la
 * dernière ligne expliqué ultérieurement */

void creation_Matrice(
    double **matrice, int Tmax, int Nmax,
    double valeur_def, // Fonction void car elle ne renvoie rien
    double valeur_spe) {

  // Nous pouvons noter ici que le temps correspond aux lignes et le numéro du
  // domino aux colonnes.

  // ATTENTION : TABLEAUX DYNAMIQUES ! PENSER À LIBÉRER L'ESPACE MÉMOIRE PAR LA
  // SUITE POUR ÉVITER LES FUITES MÉMOIRES

  for (int i = 0; i < Tmax; i++)   // Parcourt les lignes du tableau alpha
                                   // (parcourt des différents temps)
    matrice[i] = new double[Nmax]; // Création d'un tableau de Nmax colonnes
                                   // (une case pour chaque domino) à la ligne i

  /* Initialisation des tableaux alpha et longueur ressort.
Concernant le tableau alpha créée à l'aide de cette fonction appelée dans le
main, toutes les valeurs des angles sont initialisées à 0 rad qui correspond à
la valeur par défaut mise en argument de la fonction, exceptées celles de la
dernière ligne qui représentent les valeurs d'angles quand tous les dominos sont
tombés, au temps maximal, ce qui signifie que alpha vaut pi/2 radians (valeur
spéciale prise en argument dans la fonction). Concernant le tableau l créée à
l'aide de cette fonction appelée dans le main, toutes les valeurs des longueurs
des ressorts sont initialisées à l0 cm qui correspond à la valeur par défaut
mise en argument de la fonction, exceptées celles de la dernière ligne qui
représentent les valeurs des ressorts lorsque les dominos sont au sol soient :
des longueurs de 0 cm (valeur spéciale prise en argument dans la fonction).*/

  for (int n = 0; n < Nmax; n++) // Parcourt les colonnes des tableau alpha et
                                 // l (parcourt les différents dominos).
  {
    for (int t = 0; t < Tmax; t++) // Parcourt les lignes des tableau alpha et l
                                   // (parcourt des différents temps).
    {
      matrice[t][n] =
          valeur_def; // Initialisation de la case ligne t colonne n dans le
                      // tableau matrice à 0 (autrement dit initialisation de
                      // l'angle du domino n à l'instant t à 0 radian pour le
                      // tableau alpha et initialisation de la
      // longueur du ressort du domino n à l'instant t à l0 cm pour le tableau
      // l).
    }
    matrice[Tmax - 1][n] =
        valeur_spe; // Initialisation de la case ligne Tmax-1 (ici la dernière
                    // ligne car les indices commencent à 0) colonne n
                    // (correspondant au nième domino) dans le tableau alpha à
                    // pi/2 rad (autrement dit initialisation des angles de tout
                    // les dominos à l'instant t final à pi/2 radian) te dans le
                    // tableau l à 0 cm (autrement dit initialisation des
    // longueurs des ressorts de tout les dominos à l'instant t final à 0
    // cm).
  }
}

void save_Data(double **matrice, int Tmax, int Nmax,
               const string &nomfichier) { // Création d'une fonction permettant
                                           // de sauvegarder
  // les valeurs de nos tableau alpha et l en imposant le nom du fichier à
  // chaque fois.

  ofstream fichier(
      nomfichier); // Création du fichier de sortie qui va permettre la
                   // sauvegarde des valeurs de la matrice en question
                   // (enregistre le tableau dans un fichier).

  if (fichier.is_open()) {           // Commande qui permet d'ouvrir le fichier.
    for (int t = 0; t < Tmax; t++) { // Parcout les lignes du tableau.
      for (int n = 0; n < Nmax; n++) { // Parcourt les colonnes du tableau.
        fichier << matrice[t][n]
                << " "; // Enregistre la valeur du tableau en question
                        // concernant le domino n à l'instant t dans le fichier.
      }
      fichier << endl; // Retour à la ligne pour changer de temporalité et
                       // revenir au domino 0.
    }
    fichier.close(); // Ferme le fichier.
    cout << "Les valeurs ont été sauvegardées dans le fichier " << nomfichier
         << endl; // Permet d'informer que les valeurs ont bien été stocké et
                  // que la sauvegarde du tableau en question dans le fichier
                  // texte s'est déroulé avec succès.
  } else { // Si impossible d'ouvrir le fichier ou que la sauvegarde n'a pas pu
           // être éffectuée.
    cerr << "Erreur : impossible d'ouvrir le fichier alpha.txt."
         << endl; // Affiche un code d'erreur en précisant que le fichier n'a
                  // pas pu être ouvert.
  }
}

int main() {

  /* Déclaration de toutes les variables utiles pour le programme */
  const int Nmax = 10;    // Nombre de colonne de nos 2 tableau (équivalent au
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
  const double w0 = M_PI / 4; // Vitesse de chute du domino en rad.s^(-1)
  const double dt = 0.001;    // intervalle de temps en s
  /* double gamma = 15.8e-6; // Définition de la viscosité du milieu de
     propagation
                          // (ici l'air) */
  const double gamma = 1.81 / 100000; // Définition de la viscosité du milieu de
                                      // propagation (ici l'air)
  const double m = 10e-3; // Définition de la masse de l'objet en kg
  /*   double J = m * h * h / 3; // Définition du moment d'inertie */
  const double J = 7.5 / 10000000; // Définition du moment d'inertie
  const double g = 9.8;            // Définition de la pesanteur
  const double k = 1.0; // Définition de la constante du raideur du ressort
  const double lmin = 0.0001; // Longueur minimale du ressort proche de 0 mais
                              // différet de 0 pour ne pas créer de problèmes
                              // dans les formules lors des calculs

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
       << "L'angle de choc est : " << alphaChoc << " rad"
       << endl; // Affiche la valeur de l'angle choc

  /* Initialisation de l'angle du premier domino a l'instant t+dt => t = 1 */

  /* alpha[0][0] = 0;  Inutile je pense car tableau déjà initialisé */

  alpha[1][0] =
      w0 *
      dt; // Stockage de la valeur de l'angle alpha du 1er domino à l'instant
          // t+dt qui correspond à t = 1. (Vitesse de chute * temps = angle)

  // Pas sûr de l'utilité de la ligne suivante
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
    /* if(alpha[t+1][0] >
         alphaChoc) { //Vérifie que l'angle est inférieur à l'angle choc pour
       éviter la singularité. alpha[t+1][0] = alphaChoc; //Si c'est le cas,
       l'angle calculé précédemment prend la valeur d'alphaChoc.
         } */

    t++; // Inrémentation du temps pour changer de ligne dans notre tableau et
         // pour passer à l'instant suivant. Ajout de 1 à t donc de dt à t.
  }

  /* Sortie de la boucle while. Ainsi le temps t correspond au temps pour lequel
   * il y a le choc entre le domino 0 et le domino 1 */

  int t_choc = t; // Sauvegarde de la valeur du temps requis avant le choc entre
                  // le domino 0 et le domino 1.

  cout << "La date du premier choc est : " << t_choc
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

    /* CA RESSEMBLE PAS A LA FORMULE DU PDF JCAPTE PAS MAIS C'EST CELLE LÀ QUI
     * FAUT PRENDRE */
    l[t][0] =
        (delta + h * cos(alpha[t][0]) * (tan(alpha[t][1]) - tan(alpha[t][0]))) /
        ((1. + tan(alpha[t][0]) * tan(alpha[t][1])) *
         cos(alpha[t][0])); // Calcul et
    // stockage dans le tableau des longueurs des ressorts l de la valeur de la
    //  longueur l à l'instant t du ressort du domino n°0, à l'aide de
    //  l'équation du pdf tout en bas.

    /* DU COUP JE L AI REECRITE */

    /* FORMULE DU MOODLE INCORRECTE OU DU MOINS PAS UTILISÉ ICI
    l[t][0] =
        h * (tan(alpha[t][1]) - (alpha[t][0])) +
        delta / ((1 + tan(alpha[t][0]) * tan(alpha[t][1])) *
                 cos(alpha[t][0])); // Calcul et stockage dans le tableau des
                                    // longueurs des ressorts l de la valeur de
                                    // la longueur l à l'instant t du ressort du
                                    // domino n°0, à l'aide de l'équation du pdf
                                    // tout en bas. */

    /* Sécurité mais pas utile selon moi EXCEPTE si la formule est fausse mais
     * formule fausse pour petits angles */

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
    }

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

      /* Sécurité mais pas utile selon moi EXCEPTE si la formule est fausse */
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

      /* Selon moi il y a une erreur dans l'écriture de cette formule... Je
      pense qu'il manque un 2 au dénominateur avec le J vers la fin de
      l'expression. SERT A RIEN
      alpha[t+1][n]=(2*alpha[t][n]-(1-gamma*dt/(2*J))*alpha[t-1][n]+3*g*dt*dt/(2*h)*sin(alpha[t][n])+dt*dt*(1./J)*k*(l0-l[t][n-1])*(h-delta*sin(alpha[t][n-1]))-dt*dt*k*h*(1/(2*J))*(l0-l[t][n]))/(1+gamma*dt/(2*J));
      //Calcul et stockage dans le tableau des angles alpha de la valeur de
      l'angle alpha à l'instant t + dt pour le domino d'indice n à l'aide de
      l'équation du pdf n°3.
*/

      // Je l'ai donc réécrite ci-dessous

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

  }



  save_Data(alpha, Tmax, Nmax,
            "alpha.txt"); // Sauvegarde du tableau alpha dans alpha.txt.
  save_Data(l, Tmax, Nmax,
            "longueur.txt"); // Sauvegarde du tableau l dans longueur.txt.

  // Trace les courbes moyenne et écart type pour la méthode rand() à l'aide de
  // Gnuplot
  FILE *gnuplot = popen("gnuplot -persist",
                        "w"); // Ouvrir une connexion entre le programme C++ et
                              // l'application de traçage de courbes gnuplot.
  fprintf(
      gnuplot,
      "set title 'Évolution des angles en fonction du temps'\n"); // Précise le
                                                                  // titre du
                                                                  // graphique.
  fprintf(gnuplot,
          "set xlabel 'Temps'\n"); // Plus précisément, cette commande
                                   // Gnuplot set xlabel est utilisée
                                   // pour définir l'étiquette de l'axe
                                   // des abscisses (x) sur le graphique
                                   // tracé. Ici, la commande 'set ylabel
                                   // 'x'' indique que l'étiquette de
                                   // l'axe des ordonnées doit être 'N'
  fprintf(gnuplot,
          "set ylabel 'Angles'\n"); // Plus précisément, cette
                                    // commande Gnuplot set ylabel
                                    // est utilisée pour définir
                                    // l'étiquette de l'axe des
                                    // ordonnées (y) sur le
                                    // graphique tracé. Ici, la
                                    // commande 'set ylabel 'y''
                                    // indique que l'étiquette de
                                    // l'axe des ordonnées doit
                                    // être 'Moyenne / Ecart type'
  fprintf(gnuplot, "set yrange [*:*] reverse\n");
  fprintf(
      gnuplot,
      "plot '-' using 1:2 with lines title 'Domino 0', '-' using 1:2 with "
      "lines title 'Domino 1', '-' using 1:2 with lines title 'Domino 2', "
      "'-' using 1:2 with lines title 'Domino 3', '-' using 1:2 with lines "
      "title 'Domino 4', '-' using 1:2 with lines title 'Domino 5', '-' "
      "using 1:2 with lines title 'Domino 6', '-' using 1:2 with lines "
      "title 'Domino 7', '-' using 1:2 with lines title 'Domino 8', '-' using "
      "1:2 with lines title 'Domino 9'\n"); // Envoie une commande au processus
                                            // Gnuplot ouvert par le programme
                                            // pour tracer 2 courbes à partir
                                            // du flux de sortie du processus
                                            // Gnuplot ouvert par le programme
                                            // C++. La commande using 1:2 qui
                                            // indique que la première colonne
                                            // du fichier de données sera
                                            // utilisée pour les valeurs de x
                                            // et la deuxième colonne sera
                                            // utilisée pour les valeurs de y.
                                            // La courbe sera tracée avec des
                                            // lignes pleines (with lines) et
                                            // portera le titre "Moyenne"
                                            // (title 'Moyenne'). La deuxième
                                            // courbe (Ecart type) est tracée
                                            // avec la même commande using 1:2,
                                            // mais elle sera tracée avec un
                                            // autre titre
                                            // ("Ecart type") (title 'Ecart
                                            // type'). La commande '-' est
                                            // utilisée pour dire à Gnuplot
                                            // d'utiliser les données qui vont
                                            // être envoyées via le flux
                                            // d'entrée standard, plutôt que
                                            // d'un fichier. La commande '\n'
                                            // est utilisée pour terminer la
                                            // commande Gnuplot.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y1.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][0]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][1]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][2]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][3]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][4]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][5]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][6]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][7]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][8]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][9]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une chaîne
                          // de formatage qui indique que les deux arguments
                          // suivants doivent être des nombres à virgule
                          // flottante, et que la chaîne "\n" (retour à la
                          // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  // Fermeture du canal de communication avec gnuplot
  pclose(gnuplot);

  // Trace les courbes moyenne et écart type pour la méthode rand() à l'aide de
  // Gnuplot
  FILE *gnuplot2 = popen("gnuplot -persist",
                         "w"); // Ouvrir une connexion entre le programme C++ et
                               // l'application de traçage de courbes gnuplot.
  fprintf(gnuplot2,
          "set title 'Évolution des longueurs des ressorts en fonction du "
          "temps'\n"); // Précise le
                       // titre du
                       // graphique.
  fprintf(gnuplot2,
          "set xlabel 'Temps'\n"); // Plus précisément, cette commande
                                   // Gnuplot set xlabel est utilisée
                                   // pour définir l'étiquette de l'axe
                                   // des abscisses (x) sur le graphique
                                   // tracé. Ici, la commande 'set ylabel
                                   // 'x'' indique que l'étiquette de
                                   // l'axe des ordonnées doit être 'N'
  fprintf(
      gnuplot2,
      "set ylabel 'Longueurs des ressorts'\n"); // Plus précisément, cette
                                                // commande Gnuplot set ylabel
                                                // est utilisée pour définir
                                                // l'étiquette de l'axe des
                                                // ordonnées (y) sur le
                                                // graphique tracé. Ici, la
                                                // commande 'set ylabel 'y''
                                                // indique que l'étiquette de
                                                // l'axe des ordonnées doit
                                                // être 'Moyenne / Ecart type'
  fprintf(
      gnuplot2,
      "plot '-' using 1:2 with lines title 'Domino 0', '-' using 1:2 with "
      "lines title 'Domino 1', '-' using 1:2 with lines title 'Domino 2', "
      "'-' using 1:2 with lines title 'Domino 3', '-' using 1:2 with lines "
      "title 'Domino 4', '-' using 1:2 with lines title 'Domino 5', '-' "
      "using 1:2 with lines title 'Domino 6', '-' using 1:2 with lines "
      "title 'Domino 7', '-' using 1:2 with lines title 'Domino 8', '-' using "
      "1:2 with lines title 'Domino 9'\n"); // Envoie une commande au processus
                                            // Gnuplot ouvert par le programme
                                            // pour tracer 2 courbes à partir
                                            // du flux de sortie du processus
                                            // Gnuplot ouvert par le programme
                                            // C++. La commande using 1:2 qui
                                            // indique que la première colonne
                                            // du fichier de données sera
                                            // utilisée pour les valeurs de x
                                            // et la deuxième colonne sera
                                            // utilisée pour les valeurs de y.
                                            // La courbe sera tracée avec des
                                            // lignes pleines (with lines) et
                                            // portera le titre "Moyenne"
                                            // (title 'Moyenne'). La deuxième
                                            // courbe (Ecart type) est tracée
                                            // avec la même commande using 1:2,
                                            // mais elle sera tracée avec un
                                            // autre titre
                                            // ("Ecart type") (title 'Ecart
                                            // type'). La commande '-' est
                                            // utilisée pour dire à Gnuplot
                                            // d'utiliser les données qui vont
                                            // être envoyées via le flux
                                            // d'entrée standard, plutôt que
                                            // d'un fichier. La commande '\n'
                                            // est utilisée pour terminer la
                                            // commande Gnuplot.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y1.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][0]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][1]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][2]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][3]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][4]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][5]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][6]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][7]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][8]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot2, "%lf %lf\n", j * dt,
            l[j][9]); // Permet d'écrire une chaîne de caractères formatée
                      // dans un flux de sortie. "%lf %lf\n" est une chaîne
                      // de formatage qui indique que les deux arguments
                      // suivants doivent être des nombres à virgule
                      // flottante, et que la chaîne "\n" (retour à la
                      // ligne) doit être ajoutée à la fin.
  }
  fprintf(
      gnuplot2,
      "e\n"); // Indiquer à Gnuplot que les données pour la première courbe sont
              // terminées et que Gnuplot doit passer à la deuxième courbe.

  // Fermeture du canal de communication avec gnuplot
  pclose(gnuplot2);

  // QUESTIONS : LA LONGUEUR DU RESSORT DU DERNIER DOMINO NE VARIE PAS (jamais
  // copmpréssé): Y A T-IL UNE RAISON ? Les valeurs des angles finaux lorsque
  // tous les dominos sont tombés est étrange (pas égales) ! Mais pas pour les
  // ressorts.
  // Reprendre le tracé des graphs de la longueur des ressorts en fonction du
  // temps et de la variation de la valeur des angles en fonction du temps
  // (prévoir si Tmax bien supérieur au
  // temps de chute de tous les dominos). Commentarisez conditions angles
  // négatifs et longueur infinies. Commenter le tracé des courbes. Optimiser le
  // code.
  // Faire des bibliothèques peut-être ?
  // Vitesse limite pprofil
  // Pourquoi les ressorts se rallongent après se comprimer ?
}
