#include "stdlib.h"
#include "stdio.h"
#include "math.h"

main(int argc, char *argv[])
{
 int i, n;
 double R,phi, x;

 n=atoi(argv[1]);

 for(i=0;i<n;i++)
   {
     R = sqrt(rand()/(RAND_MAX-1.));    
     //     R = rand()/(RAND_MAX+1.);    
     phi = 2*M_PI*rand()/(RAND_MAX+1.);
     printf("%lf %lf\n", R*cos(phi), R*sin(phi)); 
   }

}
