#include "stdlib.h"
#include "stdio.h"
#include "math.h"

main(int argc, char *argv[])
{
 int i, n;
 double R,phi, costheta, sintheta;

 n=atoi(argv[1]);

 for(i=0;i<n;i++)
   {
     R = pow(rand()/(RAND_MAX+1.),1./3.); 
     phi      = 2*M_PI*rand()/(RAND_MAX+1.);
     costheta = 2.*rand()/(RAND_MAX+1.) -1.;
     sintheta = sqrt(1.-costheta*costheta);
     printf("%lf %lf %lf\n", R*cos(phi)*sintheta, R*sin(phi)*sintheta, R*costheta); 
   }

}
