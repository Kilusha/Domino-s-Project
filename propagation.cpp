//Trame pour projet domino a inserer dans votre programme
//
//J=m*h*h/3 est le moment d'inertie.
//alpha[t][n] est l'angle alpha du domino n a l'instant t.
//alpha[t+1][n] est l'angle alpha du domino n a l'instant t+dt.
//alpha[t-1][n] est l'angle alpha du domino n a l'instant t-dt.
//l[t][n] est la longueur du ressort n a l'instant t

//Pour propager les équations on fait des tableaux alpha et l a 2 indices (du type alpha[t][n]) afin de conserver la valeur des angles aux différents instants.

	/* Initialisation des tableaux : */
	
	double** alpha = new double* [Tmax];
	double** l = new double* [Tmax];
	
	for (int i = 0; i < Tmax; i++)
		alpha[i] = new double[Nmax];
	for (int i = 0; i < Tmax; i++)
		l[i] = new double[Nmax];

	
	
	/* Initialisation des tableaux alpha et longueur ressort */

	 for(t=0;t<Tmax;t++) 
	 {
	 	 for(n=1; n < Nmax ;n++)
		 {
	 	 	 alpha[t][n]=0.;
	 	 	 l[t][n]=l0;
	 	 }
	 	 alpha[t][Nmax-1]=pi/2.; 
	 	 l[t][Nmax-1]=0.;
	 }


	/* Dichotomie pour calculer l'angle de choc entre les dominos : */
	
//la fonction f est a ecrire ************************************************
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
    
    
    cout << endl << "L'angle de choc est : " << alphaChoc << endl;
   
    /* Initialisation de l'angle du premier domino a l'instant t = 0 et l'instant t+1 */
    
    alpha[0][0] = 0;
    alpha[1][0] = w0*dt;
    t = 1;
   
  /* le 1er domino en mouvement jusqu'au choc*/ 
      while (alpha[t][0] < alphaChoc){
    	    alpha[t+1][0] = (2*alpha[t][0] - (1-gamma*dt/(2*J))*alpha[t-1][0] + (3*g*dt*dt/(2*h))*sin(alpha[t][0]))/(1 + gamma*dt/(2*J));
    	    t++;
    }
    t_choc = t;
    
    cout << "La date du premier choc est : " << t_choc << endl;
   
  for(t=t_choc;t < Tmax-1;t++)//ou for(t=0;t<Tmax;t++)
   {
   /* mouvement du 1er domino apres choc avec le 2eme domino */
       l[t][0] = (delta + h*cos(alpha[t][0])*(tan(alpha[t][1]) - tan(alpha[t][0])))/((1. + tan(alpha[t][0])*tan(alpha[t][1]))*cos(alpha[t][0]));
       
       if(l[t][0]>l0)
       	       l[t][0]=l0;

       alpha[t+1][0] = (2*alpha[t][0] - (1-gamma*dt/(2*J))*alpha[t-1][0]+3*g*dt*dt/(2*h)*sin(alpha[t][0]) - dt*dt*k*h*(1/(2*J))*(l0-l[t][0]))/(1 + gamma*dt/(2*J));

    /* mouvement domino n>=1 */
       n=1;
 					//domino n en contact avec domino n-1 et avec domino n+1
       while( alpha[t][n]>alphaChoc && (n<Nmax-1) )
       {
           l[t][n]=h*tan(alpha[t][n+1]-alpha[t][n])+delta/((1.+tan(alpha[t][n])*tan(alpha[t][n+1]))*cos(alpha[t][n]));
          
           if(l[t][n]>l0)
           	   l[t][n]=l0;
        
           alpha[t+1][n]=(2*alpha[t][n]-(1-gamma*dt/(2*J))*alpha[t-1][n]+3*g*dt*dt/(2*h)*sin(alpha[t][n])+dt*dt*(1./J)*k*(l0-l[t][n-1])*(h-delta*sin(alpha[t][n-1]))-dt*dt*k*h*(1/(2*J))*(l0-l[t][n]))/(1+gamma*dt/(2*J));
           n++;
       }

       if(n<Nmax-1)			//domino n en contact avec domino n-1 (mais n'a pas encore touche domino n+1)
       {
           alpha[t+1][n]=(2*alpha[t][n]-(1-gamma*dt/(2*J))*alpha[t-1][n]+3*g*dt*dt/(2*h)*sin(alpha[t][n])+dt*dt*(1./J)*k*(l0-l[t][n-1])*(h-delta*sin(alpha[t][n-1])))/(1+gamma*dt/(2*J));
       }


       n=Nmax-1;
       while(n>=0)			//securite : evite que le domino n traverse le domino n+1 (ca peut ariver lors de la simulation ...)
       {
           if(alpha[t+1][n]>(alpha[t+1][n+1]+asin(delta*cos(alpha[t+1][n+1])/h))){
           alpha[t+1][n]=alpha[t+1][n+1]+asin(delta*cos(alpha[t+1][n+1])/h);
           }
           n=n-1;
       }

   }
   
