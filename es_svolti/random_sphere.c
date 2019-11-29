/***************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                    */
/***************************************************************************/
/* The program relies on the Transformation Method in order to generate    */
/* random points distributed within a sphere.                              */
/*                                                                         */
/* N.B. The program is not well optimized since it relies on rand()        */
/* function.                                                               */
/*                                                                         */
/* Compile the code using the command:                                     */
/* $ gcc -Wall -std=c99 random_sphere.c -o random_sphere -lm               */
/*                                                                         */
/* Run the program using the command:                                      */
/* $ ./random_sphere                                                       */
/*                                                                         */
/* Then visualize the file "rnd_sphere.dat" (for instance using gnuplot)   */
/*                                                                         */
/* Author: David Goz - david.goz@inaf.it                                   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define _N_       10000                      /* number of random point */
#define _TWO_PI_  (2.0 * 3.141592653589793)  /* 2*pi                   */
#define _R_       (10.0)                     /* radius of the sphere   */

/* function prototypes */
void set_seed(void);
double rnd_uniform_distribution(const double, const double);

int main()
{
  /* initialize the seed */
  set_seed();

  /* open file */
  const char filename[] = "rnd_sphere.dat";
  FILE *fp=NULL;
  if (!(fp = fopen(filename, "w")))
    {
      printf("\n\t Cannot create the file %s ... aborting \n", filename);
      return -1;
    }

  /* file header */
  fprintf(fp, "# 1] x coordinate\n# 2] y coordinate\n# 3] z coordinate\n#\n");
  
  /* generate _N_ random number within the circle */
  for (int i=0 ; i<_N_ ; i++)
    {
      double theta = _TWO_PI_ * rnd_uniform_distribution(0.0, 1.0);
      double phi   = acos(1.0 - 2.0 * rnd_uniform_distribution(0.0, 1.0));
      double r     = _R_ * pow(rnd_uniform_distribution(0.0, 1.0), 1./3.);

      double x = r * sin(phi) * cos(theta);
      double y = r * sin(phi) * sin(theta);
      double z = r * cos(phi);
      
      /* write on file */
      fprintf(fp, "%lf  %lf  %lf\n", x, y, z);   
    } /* loop over random nunber */

  /* close file */
  fclose(fp);
  
  return 0;
}

void set_seed()
{
  srand(time(NULL));
  
  return;
}

double rnd_uniform_distribution(const double a,
				const double b)
{
  double rnd =  (rand() / (RAND_MAX + 1.0));

  return (rnd * (b - a) + a);
}
