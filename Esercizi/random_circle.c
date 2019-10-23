/***************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                    */
/***************************************************************************/
/* The program relies on the Transformation Method in order to generate    */

/*                                                                         */
/* N.B. The program is not well optimized since it relies on rand()        */
/* function.                                                               */
/*                                                                         */
/* Compile the code using the command:                                     */
/* $ gcc -Wall -std=c99 random_circle.c -o random_circle -lm               */
/*                                                                         */
/* Run the program using the command:                                      */
/* $ ./random_circle                                                       */
/*                                                                         */
/* Then visualize the file "rnd_circle.dat" (for instance using gnuplot)   */
/*                                                                         */
/* Author: David Goz - david.goz@inaf.it                                   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define _N_       100000                    /* number of random point */
#define _TWO_PI_  (2.0 * 3.141592653589793) /* 2*pi                   */
#define _R_       (5.0)                     /* radius of the circle   */

/* function prototypes */
void set_seed(void);
double rnd_uniform_distribution(void);

int main()
{
  /* initialize the seed */
  set_seed();

  /* open file */
  const char filename[] = "rnd_circle.dat";
  FILE *fp=NULL;
  if (!(fp = fopen(filename, "w")))
    {
      printf("\n\t Cannot create the file %s ... aborting \n", filename);
      return -1;
    }

  /* file header */
  fprintf(fp, "# 1] x coordinate\n# 2] y coordinate\n#\n");
  
  /* generate _N_ random number within the circle */
  for (int i=0 ; i<_N_ ; i++)
    {
      /* phi = 2 * pi * x, where x is uniformly distributed */
      double phi = (_TWO_PI_ * rnd_uniform_distribution());
      /* r = _R_ * sqrt(x), where x is uniformly distributed */
      double r   = (_R_ * sqrt(rnd_uniform_distribution()));

      /* get coordinates */
      double x = (r * cos(phi));
      double y = (r * sin(phi));

      /* write on file */
      fprintf(fp, "%lf  %lf\n", x, y);   
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

double rnd_uniform_distribution()
{
  return (rand() / (RAND_MAX + 1.0));
}
