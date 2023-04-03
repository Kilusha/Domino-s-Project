#include "graphic.h" // Directive de préprocesseur en C++. Elle permet d'inclure la bibliothèque graphic dans le programme, qui contient des fonctions permettant d'effectuer des opérations particulières.

using namespace std; // Directive en C++ qui facilite l'utilisation des noms de
                     // l'espace de noms standard (std).

void trace_Graph(double **tableau, double dt, int Tmax, int Nmax,
                 int s) { // Création d'une fonction de type void, qui ne
                          // renvoie rien, et permettant de tracer le graph de
                          // n'importe quel tableau (alpha ou l).
  // Trace les courbes moyenne et écart type pour la méthode rand() à l'aide de
  // Gnuplot
  FILE *gnuplot = popen("gnuplot -persist",
                        "w"); // Ouvre une connexion entre le programme C++ et
                              // l'application de traçage de courbes gnuplot.

  if (s == 1) { // Si nous souhaitons tracer le graphe des angles en fonction du
                // temps.
    fprintf(
        gnuplot,
        "set title 'Évolution des angles en fonction du temps'\n"); // Précise
                                                                    // le titre
                                                                    // du
                                                                    // graphique.
    fprintf(gnuplot,
            "set ylabel 'Angles en degrés'\n"); // Plus précisément, cette
                                             // commande Gnuplot set ylabel
                                             // est utilisée pour définir
                                             // l'étiquette de l'axe des
                                             // ordonnées (y) sur le
                                             // graphique tracé. Ici, la
                                             // commande 'set ylabel 'y''
                                             // indique que l'étiquette de
                                             // l'axe des ordonnées doit
                                             // être 'Angles'
    fprintf(gnuplot,
            "set yrange [*:*] reverse\n"); // Permet de renverser le sens de
                                           // l'axe des ordonnées.
  }

  else if (s == 2) { // Si nous souhaitons tracer la longueur des ressorts en
                     // fonction du temps.
    fprintf(gnuplot,
            "set title 'Évolution des longueurs des ressorts en fonction du "
            "temps'\n"); // Précise le
                         // titre du
                         // graphique.

    fprintf(
        gnuplot,
        "set ylabel 'Longueurs des ressorts en m'\n"); // Plus précisément,
                                                       // cette commande Gnuplot
                                                       // set ylabel est
                                                       // utilisée pour définir
                                                       // l'étiquette de l'axe
                                                       // des ordonnées (y) sur
                                                       // le graphique tracé.
                                                       // Ici, la commande 'set
                                                       // ylabel 'y'' indique
                                                       // que l'étiquette de
                                                       // l'axe des ordonnées
                                                       // doit être 'Longueur
                                                       // des ressorts'
  } else if (s == 3) { // Si nous souhaitons tracer la vitesse de propagation de
                       // l'onde en fonction du temps.

    fprintf(gnuplot, "set title 'Évolution de la vitesse de propagation de "
                     "l onde de chute  en focntion du temps'\n"); // Précise
                                                                  // le titre
                                                                  // du
                                                                  // graphique.

    fprintf(gnuplot,
            "set ylabel 'Vitesses en m.s^(-1)'\n"); // Plus précisément,
                                                    // cette commande Gnuplot
                                                    // set ylabel est
                                                    // utilisée pour définir
                                                    // l'étiquette de l'axe
                                                    // des ordonnées (y) sur
                                                    // le graphique tracé.
                                                    // Ici, la commande 'set
                                                    // ylabel 'y'' indique
                                                    // que l'étiquette de
                                                    // l'axe des ordonnées
                                                    // doit être 'Vitesses
                                                    // en m.s^(-1)'
  }
  fprintf(gnuplot,
          "set xlabel 'Temps en s'\n"); // Plus précisément, cette commande
                                        // Gnuplot set xlabel est utilisée
                                        // pour définir l'étiquette de l'axe
                                        // des abscisses (x) sur le graphique
                                        // tracé. Ici, la commande 'set ylabel
                                        // 'x'' indique que l'étiquette de
                                        // l'axe des abscisses doit être 'Temps'

  fprintf(gnuplot, "plot "); // Envoie une commande au
                             // processus Gnuplot ouvert par le
                             // programme pour tracer des courbes
                             // à partir du flux de sortie du
                             // processus Gnuplot ouvert par le
                             // programme C++.
  for (int i = 0; i < Nmax;
       i++) { // Parcourt tous les dominos. Boucle permettant de tracer Nmax
              // graphiques (1 par dominos).
    fprintf(
        gnuplot, "'-' using 1:2 with lines title 'Domino %d'",
        i); // La commande '-' est utilisée pour
            // dire à Gnuplot d'utiliser les
            // données qui vont être envoyées
            // via le flux d'entrée standard,
            // plutôt que d'un fichier. using 1:2 qui indique que la
            // première colonne du fichier de
            // données sera utilisée pour les
            // valeurs de x et la deuxième
            // colonne sera utilisée pour les
            // valeurs de y. La courbe sera
            // tracée avec des lignes pleines
            // (with lines) et portera le
            // titre "Domino i", i représentant l'indice du domino en question.
            // Le %d ici signifie qu'il faudra y placer une valeur de type
            // double qui est indiqué après la virgule (ici la valeur de i).

    if (i < Nmax - 1) {       // Condition permettant de vérifier s'il sagit du
                              // dernier domino. Si ça ne l'est pas alors :
      fprintf(gnuplot, ", "); // Ajout d'une virgule pour pouvoir programmer le
                              // prochain graphe à tracer.
    } else {                  // S'il sagit du dernier domino :
      fprintf(gnuplot, "\n"); // Ajoute la
                              // commande '\n' qui est utilisée pour
                              // terminer la commande Gnuplot.
    }
  }

  for (int i = 0; i < Nmax;
       i++) { // Parcourt toutes les lignes du tableaux placé en argument.
    for (int j = 0; j < Tmax;
         j++) { // Parcourt toutes les colonnes du tableaux placé en argument.

      if (s == 1) {

        fprintf(
            gnuplot, "%lf %lf\n", j * dt,
            tableau[j][i] * 180 / M_PI); // Permet d'écrire une chaîne de caractères formatée
                            // dans un flux de sortie. "%lf %lf\n" est une
                            // chaîne de formatage qui indique que les deux
                            // arguments suivants doivent être des nombres à
                            // virgule flottante, et que la chaîne "\n" (retour
                            // à la ligne) doit être ajoutée à la fin.

      } else {

        fprintf(
            gnuplot, "%lf %lf\n", j * dt,
            tableau[j][i]); // Permet d'écrire une chaîne de caractères formatée
                            // dans un flux de sortie. "%lf %lf\n" est une
                            // chaîne de formatage qui indique que les deux
                            // arguments suivants doivent être des nombres à
                            // virgule flottante, et que la chaîne "\n" (retour
                            // à la ligne) doit être ajoutée à la fin.
      }
    }
    fprintf(gnuplot,
            "e\n"); // Indique à Gnuplot que les données pour la
                    // courbe en question sont terminées et que Gnuplot doit
                    // passer à la prochaine courbe.
  }
  // Fermeture du canal de communication avec gnuplot
  pclose(gnuplot);
}
