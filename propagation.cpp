#include <iostream>
#include <cmath>

using namespace std;

//Trame pour projet domino a inserer dans votre programme
//
//J=m*h*h/3 est le moment d'inertie.
//alpha[t][n] est l'angle alpha du domino n a l'instant t.
//alpha[t+1][n] est l'angle alpha du domino n a l'instant t+dt.
//alpha[t-1][n] est l'angle alpha du domino n a l'instant t-dt.
//l[t][n] est la longueur du ressort n a l'instant t

//Pour propager les équations on fait des tableaux alpha et l a 2 indices (du type alpha[t][n]) afin de conserver la valeur des angles aux différents instants.

	double f(double alphaChoc, double d, double l0, double h) {
    return sin(alphaChoc) - (d - l0 * cos(alphaChoc))/h;
}

double findRoot(double d, double l0, double h) {
    double alphaMin = 0.0; // borne inférieure
    double alphaMax = M_PI/2; // borne supérieure
    double tol = 1e-1; // tolérance
    double alphaChoc = (alphaMin + alphaMax)/2.0; // valeur initiale
    while (fabs(f(alphaChoc, d, l0, h)) > tol) {
        if (f(alphaChoc, d, l0, h) > 0) {
            alphaMax = alphaChoc;
        } else {
            alphaMin = alphaChoc;
        }
        alphaChoc = (alphaMin + alphaMax)/2.0;
    }
    return alphaChoc;
}
    
    
    
    
    /* Initialisation des tableaux : */

    int main() {

    int Nmax = 10; //Nombre de dominos
    int Tmax = 20; //Temps maximale
    double l0 = 2; //Longueur du ressort au repos

	
	double** alpha = new double* [Tmax];
	double** l = new double* [Tmax];

    for (int i = 0; i < Tmax; i++) Tmax = Tmax + 1;

	
	for (int i = 0; i < Tmax; i++) 
		alpha[i] = new double[Nmax];

	for (int i = 0; i < Tmax; i++)
		l[i] = new double[Nmax];

	
	
	/* Initialisation des tableaux alpha et longueur ressort */

	 for(int t=0;t<Tmax;t++) 
	 {
	 	 for(int n=1; n < Nmax ;n++)
		 {
	 	 	 alpha[t][n]=0.;
	 	 	 l[t][n]=l0;
	 	 }
	 	 alpha[t][Nmax-1]=M_PI/2.; 
	 	 l[t][Nmax-1]=0.;
	 }


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
   
