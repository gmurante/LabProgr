/*********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)              */
/*********************************************************************/
/* The program implements a Montecarlo method of finding the area of */
/* a circle and pi.                                                  */
/* The program assumes a circle of radius 1                          */
/* N.B. The program is not well optimized since it relies on rand()  */
/* function.                                                         */
/*                                                                   */
/* Compile the code using the command:                               */
/* $ gcc -Wall pi_greco.c -o pi_greco -lm                            */
/*                                                                   */
/* Run the program using the command:                                */
/* $ ./pi_greco                                                      */
/*                                                                   */
/* Author: David Goz - david.goz@inaf.it                             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define _N_  10000 /* number of random point      */
#define _A_  0.0
#define _B_  1.0   /* get random number in [a, b) */

/* get random number in [a, b) */
double random_number(const double, const double);
/* initialize the seed */
void set_seed(void);


int main()
{
  /* set random seed */
  set_seed();
  
  /* hit rate */
  long int hit = 0;

  /* generate random series */
  for (int i=0 ; i<_N_ ; i++)
    {
      double x = random_number(_A_, _B_);
      double y = random_number(_A_, _B_);

      hit = (((x*x + y*y) < 1.0) ? (hit + 1) : hit);
    } /* loop over random series */

  const double myPI = (double)hit/_N_ * 4.0;
  
  printf("\n\t myPI = %lf using %ld random points",
	 myPI, (long int)_N_);

  printf("\n\t Relative error %lg\n\n",
	 fabs((myPI - M_PI) / M_PI));
  
  return 0;
}

double random_number(const double a,
		     const double b)
{
  double rendfrac = rand() / (RAND_MAX + 1.0);

  return (rendfrac * (b - a) + a);
}

void set_seed()
{
  srand(time(NULL));
  
  return;
}
