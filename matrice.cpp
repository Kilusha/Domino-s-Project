#include "matrice.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque matrice dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de l'espace de noms standard (std).

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
