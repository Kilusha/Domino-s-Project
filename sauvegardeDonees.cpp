/*
* Projet des Dominos C++
*
* sauvegardeDonnees.cpp
*
* @auteurs PALAY Kiliann & SERRE Marina
*/

#include "sauvegardeDonnees.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque saveData dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.
#include <fstream> // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque fstream dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de
                     // l'espace de noms standard (std).

void sauvegarde_Donnees(double **matrice, int Tmax, int Nmax,
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
    cout << endl
         << "Les valeurs ont été sauvegardé dans le fichier " << nomfichier
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

double vitesse(double alpha1, double alpha2,
               double dt) { // Création d'une fonction qui permet de calculer la
                            // vitesse de chute d'un domino à un instant donné.
  return (alpha1 - alpha2) / dt; // REnvoie la vitesse en question.
}
