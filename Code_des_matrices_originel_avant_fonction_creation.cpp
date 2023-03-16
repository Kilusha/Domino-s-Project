/* Initialisation des 2 tableaux à 2 dimensions en allouant de la mémoire
 * dynamique pour y stocker des variables de type "doubles" qui seront la valeur
 * de l'angle alpha du domino n à l'nstant t, ainsi que la longueur de son
 * ressort à ce même instant : */
// Nous pouvons noter que le temps correspond aux lignes et le nméro du domino
// aux colonnes.

// ATTENTION : TABLEAUX DYNAMIQUES ! PENSER À LIBÉRER L'ESPACE MÉMOIRE PAR LA
// SUITE POUR ÉVITER LES FUITES MÉMOIRES

double **alpha =
    new double *[Tmax]; // Déclaration du pointeur alpha qui pointera vers la
                        // case ou sera stocké la valeur de l'angle alpha.
double **l =
    new double *[Tmax]; // Déclaration du pointeur l qui pointera vers la case
                        // ou sera stocké la valeur de la longueur du ressort l.

// Création des cases, où seront rangés les coeffs, des 2 tableaux.

for (int i = 0; i < Tmax; i++) // Parcourt les lignes du tableau alpha (parcourt
                               // des différents temps)
  alpha[i] = new double[Nmax]; // Création d'un tableau de Nmax colonnes (une
                               // case pour chaque domino) à la ligne i

for (int i = 0; i < Tmax;
     i++) // Parcourt les lignes du tableau l (parcourt des différents temps)
  l[i] = new double[Nmax]; // Création d'un tableau de Nmax colonnes (une case
                           // pour chaque domino) à la ligne i

/* Initialisation des tableaux alpha et longueur ressort.
Concernant le tableau alpha, toutes les valeurs des angles sont initialisées à 0
exceptées celles de la dernière ligne qui représentent les valeurs d'angles
quand tous les dominos sont tombés, au temps maximal, ce qui signifie que alpha
vaut pi/2 radians. Concernant le tableau l, toutes les valeurs des longueurs des
ressorts sont initialisées à l0 exceptées celles de la dernière ligne qui
représentent les valeurs des ressorts lorsque les dominos sont au sol soient :
des longueurs de 0 cm.*/

for (int n = 0; n < Nmax; n++) // Parcourt les colonnes des tableau alpha et
                               // l (parcourt les différents dominos)
{
  for (int t = 0; t < Tmax; t++) // Parcourt les lignes des tableau alpha et l
                                 // (parcourt des différents temps)
  {
    alpha[t][n] = 0.; // Initialisation de la case ligne t colonne n dans le
                      // tableau alpha à 0 (autrement dit initialisation de
                      // l'angle du domino n à l'instant t à 0 radian)
    l[t][n] = l0;     // Initialisation de la case ligne t colonne n dans le
                      // tableau l à l0 (autrement dit initialisation de la
    // longueur du ressort du domino n à l'instant t à l0 cm)
  }
  alpha[Tmax - 1][n] =
      M_PI /
      2.; // Initialisation de la case ligne Tmax-1 (ici la dernière ligne
          // car les indices commencent à 0) colonne n (correspondant au nième
          // domino) dans le tableau alpha à pi/2 (autrement dit initialisation
          // des angles de tout les dominos à l'instant t final à pi/2 radian).
  l[Tmax - 1][n] =
      0.; // Initialisation de la case ligne Tmax-1 (ici la dernière ligne
          // car les indices commencent à 0) colonne n (correspondant au nième
          // domino) dans le tableau l à 0 (autrement dit initialisation des
          // longueurs des ressorts de tout les dominos à l'instant t final à 0
          // cm).
}