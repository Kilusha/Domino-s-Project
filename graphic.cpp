#include "graphic.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque graphic dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de
                     // l'espace de noms standard (std).

void trace_Graph(
    double **alpha, double dt, int Tmax,
    int s) { // Création d'une fonction de type void, qui ne renvoie rien, et
             // permettant d'identifier les nombres premiers entre 2 bornes.
  // Trace les courbes moyenne et écart type pour la méthode rand() à l'aide de
  // Gnuplot
  FILE *gnuplot = popen("gnuplot -persist",
                        "w"); // Ouvrir une connexion entre le programme C++ et
                              // l'application de traçage de courbes gnuplot.
  if (s == 1) {
    fprintf(
        gnuplot,
        "set title 'Évolution des angles en fonction du temps'\n"); // Précise
                                                                    // le titre
                                                                    // du
                                                                    // graphique.
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
  }

  else {
    fprintf(gnuplot,
            "set title 'Évolution des longueurs des ressorts en fonction du "
            "temps'\n"); // Précise le
                         // titre du
                         // graphique.

    fprintf(
        gnuplot,
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
  }

  fprintf(gnuplot,
          "set xlabel 'Temps'\n"); // Plus précisément, cette commande
                                   // Gnuplot set xlabel est utilisée
                                   // pour définir l'étiquette de l'axe
                                   // des abscisses (x) sur le graphique
                                   // tracé. Ici, la commande 'set ylabel
                                   // 'x'' indique que l'étiquette de
                                   // l'axe des ordonnées doit être 'N'

  fprintf(
      gnuplot,
      "plot '-' using 1:2 with lines title 'Domino 0', '-' using 1:2 with "
      "lines title 'Domino 1', '-' using 1:2 with lines title 'Domino 2', "
      "'-' using 1:2 with lines title 'Domino 3', '-' using 1:2 with lines "
      "title 'Domino 4', '-' using 1:2 with lines title 'Domino 5', '-' "
      "using 1:2 with lines title 'Domino 6', '-' using 1:2 with lines "
      "title 'Domino 7', '-' using 1:2 with lines title 'Domino 8', '-' "
      "using "
      "1:2 with lines title 'Domino 9'\n"); // Envoie une commande au
                                            // processus Gnuplot ouvert par le
                                            // programme pour tracer 2 courbes
                                            // à partir du flux de sortie du
                                            // processus Gnuplot ouvert par le
                                            // programme C++. La commande
                                            // using 1:2 qui indique que la
                                            // première colonne du fichier de
                                            // données sera utilisée pour les
                                            // valeurs de x et la deuxième
                                            // colonne sera utilisée pour les
                                            // valeurs de y. La courbe sera
                                            // tracée avec des lignes pleines
                                            // (with lines) et portera le
                                            // titre "Moyenne" (title
                                            // 'Moyenne'). La deuxième courbe
                                            // (Ecart type) est tracée avec la
                                            // même commande using 1:2, mais
                                            // elle sera tracée avec un autre
                                            // titre
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
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][1]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][2]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][3]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][4]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][5]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][6]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][7]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][8]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  for (int j = 0; j < Tmax;
       j++) { // Parcourt toutes les lignes des tableaux x, y2.
    fprintf(gnuplot, "%lf %lf\n", j * dt,
            alpha[j][9]); // Permet d'écrire une chaîne de caractères formatée
                          // dans un flux de sortie. "%lf %lf\n" est une
                          // chaîne de formatage qui indique que les deux
                          // arguments suivants doivent être des nombres à
                          // virgule flottante, et que la chaîne "\n" (retour
                          // à la ligne) doit être ajoutée à la fin.
  }
  fprintf(gnuplot,
          "e\n"); // Indiquer à Gnuplot que les données pour la première
                  // courbe sont terminées et que Gnuplot doit passer à la
                  // deuxième courbe.

  // Fermeture du canal de communication avec gnuplot
  pclose(gnuplot);
}
