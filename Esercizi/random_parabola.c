/***************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                    */
/***************************************************************************/
/* The program relies on the Transformation Method in order to generate    */
/* a random number distribution following f(x) = 3x^2.                     */
/*                                                                         */
/* N.B. The program is not well optimized since it relies on rand()        */
/* function.                                                               */
/*                                                                         */
/* Compile the code using the command:                                     */
/* $ gcc -Wall -std=c99 random_parabola.c -o random_parabola -lm           */
/*                                                                         */
/* Run the program using the command:                                      */
/* $ ./random_parabola                                                     */
/*                                                                         */
/* Then visualize the file "rnd_parabola.dat" (for instance using gnuplot) */
/* and check that the distribution follows f(x) = 3x^2                     */
/*                                                                         */
/* Author: David Goz - david.goz@inaf.it                                   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define _N_     100000 /* number of random point          */
#define _NBIN_  100    /* number of bins of the histogram */
#define _DELTA_ (1.0 / (double)_NBIN_)
#define _INV_3_ (1.0 / 3.0)

/* global variables/arrays */
int histogram[_NBIN_];

/* function prototypes */
void histogram_init(void);
void set_seed(void);
double rnd_parabola_distribution(void);
void histogram_count(const double);
int write_histogram(void);

int main()
{
  /* initialize the histogram */
  histogram_init();

  /* initialize the seed */
  set_seed();

  /* generate _N_ random number with exp(-x) distribution */
  for (int i=0 ; i<_N_ ; i++)
    {
      double rnd = rnd_parabola_distribution();

      /* update the histogram */
      histogram_count(rnd);
    } /* loop over random nunber */

  /* write histogram */
  if (write_histogram())
    {
      printf("\n\t Cannot write histogram \n");
      return -1;
    }
  
  return 0;
}

void histogram_init()
{
  for (int bin=0 ; bin<_NBIN_ ; bin++)
    histogram[bin] = 0;
  
  return;
}

void set_seed()
{
  srand(time(NULL));
  
  return;
}

double rnd_parabola_distribution()
{
  /* random number uniformly distributed in (0,1) */
  double x;
  do
    {
      x = rand() / (RAND_MAX + 1.0);
    } while (x <= 0.0);

  return pow(x, _INV_3_);
}

void histogram_count(const double x)
{
  const int l = (int)(x / _DELTA_);

  /* update the histogram */
  if (l < _NBIN_)
    histogram[l]++;

  return;
}

int write_histogram()
{
  const char filename[] = "rnd_parabola.dat";
  
  FILE *fp = NULL;
  if (!(fp = fopen(filename, "w")))
    {
      printf("\n\t Cannot create %s ... aborting \n", filename);
      return -1;
    }

  /* Write header file */
  fprintf(fp, "# Random numbers distributed as f(x) = 3x^2\n#\n");
  
  for (int bin=0 ; bin<_NBIN_ ; bin++)
    fprintf(fp, "%lf   %lf\n", (double)bin*_DELTA_, (double)histogram[bin]/_N_/_DELTA_);

  /* close file */
  fclose(fp);
  
  return 0;
}
