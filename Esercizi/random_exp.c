/************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                 */
/************************************************************************/
/* The program relies on the Transformation Method in order to generate */
/* a random number distribution following f(x) = exp(-x)                */
/*                                                                      */
/* N.B. The program is not well optimized since it relies on rand()     */
/* function.                                                            */
/*                                                                      */
/* Compile the code using the command:                                  */
/* $ gcc -Wall random_exp.c -o random_exp -lm                           */
/*                                                                      */
/* Run the program using the command:                                   */
/* $ ./random_exp                                                       */
/*                                                                      */
/* Then visualize the file "rnd_exp.dat" (for instance using gnuplot)   */
/* and check that the distribution follows f(x) = exp(-x)               */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define _N_     100000 /* number of random point          */
#define _NBIN_  200    /* number of bins of the histogram */
#define _DELTA_ (2.0 / (double)_NBIN_)

/* global variables/arrays */
int histogram[_NBIN_];

/* function prototypes */
void histogram_init(void);
void set_seed(void);
double rnd_exp_distribution(void);
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
      double rnd = rnd_exp_distribution();

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

double rnd_exp_distribution()
{
  /* random number uniformly distributed in (0,1) */
  double x;
  do
    {
      x = rand() / (RAND_MAX + 1.0);
    } while (x <= 0.0);

  return -log(x);
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
  const char filename[] = "rnd_exp.dat";
  
  FILE *fp = NULL;
  if (!(fp = fopen(filename, "w")))
    {
      printf("\n\t Cannot create %s ... aborting \n", filename);
      return -1;
    }

  /* Write header file */
  fprintf(fp, "# Random numbers distributed as f(x) = exp(-x)\n#\n");
  
  for (int bin=0 ; bin<_NBIN_ ; bin++)
    fprintf(fp, "%lf   %lf\n", (double)bin*_DELTA_, (double)histogram[bin]/_N_/_DELTA_);

  /* close file */
  fclose(fp);
  
  return 0;
}
