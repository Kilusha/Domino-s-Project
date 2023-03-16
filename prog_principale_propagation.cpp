#include <cmath>
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

/* Création de la fonction f qui permet de calculer le membre de gauche trouvé
 * dans la partie théorique qui est censé valoir 0 lorsqu'un domino entre en
 * contact avec son voisin. Ainsi il nous permettra de déterminer le bon angle
 * alpha qui correspond à l'angle de choc */

double f(double alphaChoc, double d, double l0, double h) {
  return sin(alphaChoc) - (d - l0 * cos(alphaChoc)) / h;
}

/* Création de la fonction findRoot qui permet de déterminer par dichotomie la
 * valeur de l'angle pour le quel un domino entre en contact avec son voisin */

double findRoot(double d, double l0, double h) {
  double alphaMin =
      0.0; // Définition de la borne inférieure de notre intervalle
  double alphaMax =
      M_PI / 2;      // Définition de la borne supérieure de notre intervalle
  double tol = 1e-1; // définition de la tolérance
  double alphaChoc = (alphaMin + alphaMax) /
                     2.0; // Définition de la valeur initiale de l'angle choc
  while (fabs(f(alphaChoc, d, l0, h)) >
         tol) { // Vérifie si le membre de gauche de l'équation théorique vaut
                // quasi 0 en prenant en compte la tolérance. Sinon, alors nous
                // rentrons dans la boucle.
    if (f(alphaChoc, d, l0, h) >
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

    int main() {

    int Nmax = 10; //Nombre de colonne de nos 2 tableau (équivalent au nombre de dominos)
    int Tmax = 5; //Nombre de lignes maximale de nos 2 tableaux (équivalent au temps maximal)
    double l0 = 2; //Longueur du ressort au repos

double **alpha =
    new double *[Tmax]; // Déclaration du pointeur alpha qui pointera vers la
                        // case ou sera stocké la valeur de l'angle alpha.
double **l =
    new double *[Tmax]; // Déclaration du pointeur l qui pointera vers la case
                        // ou sera stocké la valeur de la longueur du ressort l.


 /* Initialisation des 2 tableaux à 2 dimensions en allouant de la mémoire
   * dynamique pour y stocker des variables de type "doubles" qui seront la
   * valeur de l'angle alpha du domino n à l'nstant t, ainsi que la longueur de
   * son ressort à ce même instant : */

    creation_Matrice(alpha, Tmax, Nmax, 0., M_PI/2);
    creation_Matrice(l, Tmax, Nmax, l0, 0.);


    
    /*HELP JSP POURQUOI ON A MIS ÇA !
    
    for (int i = 0; i < Tmax; i++) Tmax = Tmax + 1;

    */


   

	/* Dichotomie pour calculer l'angle de choc entre les dominos : */
	
//la fonction f est a ecrire ************************************************

    double d = 2.5; //Vaut delta dans le pdf (distance entre les 2 dominos)
    double h = 3.0;
    double alphaChoc = findRoot(d, l0, h);
    cout << endl << "L'angle de choc est : " << alphaChoc << endl;

/*

    while( abs(alphaMax-alphaMin) >= epsi)
    {
           alphaChoc = (alphaMin+alphaMax) /2  ;
           if (f(alphaMin)*f(alphaChoc) < 0)
           {
                         alphaMax=alphaChoc;
           }
           else
           {
               alphaMin=alphaChoc;
           }
    }
    
    */



   
    /* Initialisation de l'angle du premier domino a l'instant t = 0 et l'instant t+1 */

    double w0 = 0.2; //Vitesse de chute du domino en rad.s^(-1)
    double dt = 0.5; //intervalle de temps en s
    
    alpha[0][0] = 0;
    alpha[1][0] = w0*dt; //Vitesse de chute * temps = angle
    int t = 1;
    double gamma = 15.8e-6;
    double m = 8e-3;
    double J = m*h*h/3;
    double g = 9.8;
    double k = 20.0; //Constante du raideur du ressort

   
  /* le 1er domino en mouvement jusqu'au choc*/ 
      while (alpha[t][0] < alphaChoc){
    	    alpha[t+1][0] = (2*alpha[t][0] - (1-gamma*dt/(2*J))*alpha[t-1][0] + (3*g*dt*dt/(2*h))*sin(alpha[t][0]))/(1 + gamma*dt/(2*J));
    	    t++;
    }
    int t_choc = t;
    
    cout << "La date du premier choc est : " << t_choc << endl;
   
  for(t=t_choc;t < Tmax-1;t++)//ou for(t=0;t<Tmax;t++)
   {
   /* mouvement du 1er domino apres choc avec le 2eme domino */
       l[t][0] = (d + h*cos(alpha[t][0])*(tan(alpha[t][1]) - tan(alpha[t][0])))/((1. + tan(alpha[t][0])*tan(alpha[t][1]))*cos(alpha[t][0]));
       
       if(l[t][0]>l0)
       	       l[t][0]=l0;

       alpha[t+1][0] = (2*alpha[t][0] - (1-gamma*dt/(2*J))*alpha[t-1][0]+3*g*dt*dt/(2*h)*sin(alpha[t][0]) - dt*dt*k*h*(1/(2*J))*(l0-l[t][0]))/(1 + gamma*dt/(2*J));

    /* mouvement domino n>=1 */
       int n=1; //Numéro du domino
 					//domino n en contact avec domino n-1 et avec domino n+1
       while( alpha[t][n]>alphaChoc && (n<Nmax-1) )
       {
           l[t][n]=h*tan(alpha[t][n+1]-alpha[t][n])+d/((1.+tan(alpha[t][n])*tan(alpha[t][n+1]))*cos(alpha[t][n]));
          
           if(l[t][n]>l0)
           	   l[t][n]=l0;
        
           alpha[t+1][n]=(2*alpha[t][n]-(1-gamma*dt/(2*J))*alpha[t-1][n]+3*g*dt*dt/(2*h)*sin(alpha[t][n])+dt*dt*(1./J)*k*(l0-l[t][n-1])*(h-d*sin(alpha[t][n-1]))-dt*dt*k*h*(1/(2*J))*(l0-l[t][n]))/(1+gamma*dt/(2*J));
           n++;
       }

       if(n<Nmax-1)			//domino n en contact avec domino n-1 (mais n'a pas encore touche domino n+1)
       {
           alpha[t+1][n]=(2*alpha[t][n]-(1-gamma*dt/(2*J))*alpha[t-1][n]+3*g*dt*dt/(2*h)*sin(alpha[t][n])+dt*dt*(1./J)*k*(l0-l[t][n-1])*(h-d*sin(alpha[t][n-1])))/(1+gamma*dt/(2*J));
       }


       n=Nmax-1;
       while(n>=0)			//securite : evite que le domino n traverse le domino n+1 (ca peut ariver lors de la simulation ...)
       {
           if(alpha[t+1][n]>(alpha[t+1][n+1]+asin(d*cos(alpha[t+1][n+1])/h))){
           alpha[t+1][n]=alpha[t+1][n+1]+asin(d*cos(alpha[t+1][n+1])/h);
           }
           n=n-1;
       }

   }

    }