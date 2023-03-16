#include <cmath>
#include <iostream>

using namespace std;

int main() {

  int Nmax = 10; // Nombre de colonne de nos 2 tableau (équivalent au nombre de
                 // dominos)
  int Tmax = 5;  // Nombre de lignes maximale de nos 2 tableaux (équivalent au
                 // temps maximal)
  double l0 = 2; // Longueur du ressort au repos

  double **alpha =
      new double *[Tmax]; /* Déclaration du pointeur alpha qui pointera vers la
                case ou sera stocké la valeur de l'angle alpha. */

  double **l = new double
      *[Tmax]; // Déclaration du pointeur l qui pointera vers la case ou sera
               // stocké la valeur de la longueur du ressort l.

  for (int i = 0; i < Tmax; i++) // Parcourt les lignes du tableau alpha
                                 // (parcourt des différents temps)
    alpha[i] = new double[Nmax]; // Création d'un tableau de Nmax colonnes (une
                                 // case pour chaque domino) à la ligne i

  for (int i = 0; i < Tmax;
       i++) // Parcourt les lignes du tableau l (parcourt des différents temps)
    l[i] = new double[Nmax]; // Création d'un tableau de Nmax colonnes (une case
                             // pour chaque domino) à la ligne i

  /*VERSION PROF*/
  /*
    for (int t = 0; t < Tmax; t++)
      (parcourt des différents temps) {
        for (int n = 1; n < Nmax; n++) // Parcourt les colonnes des
          tableau alpha et l(parcourt les différents dominos) {
            alpha[t][n] = 0.;
            l[t][n] =
                l0;
          }
        alpha[t][Nmax - 1] = M_PI / 2.;
        l[t][Nmax - 1] = 0.;
      }
   */

  for (int n = 0; n < Nmax; n++) // Parcourt les lignes des tableau alpha et l
                                 // (parcourt des différents temps)
  {
    for (int t = 0; t < Tmax; t++) // Parcourt les colonnes des tableau alpha et
                                   // l (parcourt les différents dominos)
    {
      alpha[t][n] = 0.; // Initialisation de la case ligne t colonne n dans le
                        // tableau alpha à 0 (autrement dit initialisation de
                        // l'angle du domino n à l'instant t à 0 radian)
      l[t][n] = l0;     // Initialisation de la case ligne t colonne n dans le
                        // tableau l à l0 (autrement dit initialisation de la
      // longueur du ressort du domino n à l'instant t à l0 cm)
    }
    alpha[Tmax - 1][n] =
        M_PI / 2.; // Initialisation de la case ligne t (ici la dernière ligne
                   // car hors de la deuxième boucle for) colonne finale (Nmax -
                   // 1 car les indices commencent à 0) dans le tableau alpha à
                   // pi/2 (autrement dit initialisation de l'angle du dernier
                   // domino à l'instant t final à 0 radian)
    l[Tmax - 1][n] = 0.;
  }

  // Affichage de la matrice alpha
  cout << "Matrice alpha : " << endl;
  for (int i = 0; i < Tmax; i++) {
    for (int j = 0; j < Nmax; j++) {
      cout << alpha[i][j] << " ";
    }
    cout << endl;
  }

  // Affichage de la matrice l
  cout << "Matrice l : " << endl;
  for (int i = 0; i < Tmax; i++) {
    for (int j = 0; j < Nmax; j++) {
      cout << l[i][j] << " ";
    }
    cout << endl;
  }

  // cout << l[0][9] << " ";

  return 0;
}