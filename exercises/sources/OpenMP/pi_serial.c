/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* The program numerically computes the integral of the following function:      */
/*                                                                               */
/*                      f(x) = 4.0 / (1 + x*x)                                   */
/*                                                                               */
/* from 0 to 1. The value of the intergral is pi.                                */
/* This is the serial implementation.                                            */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra pi_serial.c -o pi_serial -lm                              */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./pi_serial                                                            */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* Assigned tasks:                                                               */
/*                - parallelize the code targeting the for loop over the steps   */
/*                  of the integral. Check the result, and then measure the      */
/*                  time-to-solution (this can be done smoothly using the Unix   */
/*                  'time' command). Does it scale varying the number of OpenMP  */
/*                  threads? Any difference in changing the scheduling policy of */
/*                  the for loop? Why?                                           */
/*********************************************************************************/

#include <stdio.h>
#include <math.h>

/* number of steps */
const unsigned long int num_steps = 1000000000;
typedef double MyFloat;

int main ()
{
  const MyFloat step = 1.0/(MyFloat) num_steps;

  /* accumulator */
  MyFloat sum = 0.0;
  for (unsigned long int i=1 ; i<=num_steps ; i++)
    {
      const MyFloat x = (i - 0.5) * step;
      sum += (1.0 / (1.0 + (x * x)));
    }

  const MyFloat my_pi = (4.0 * step * sum);

  printf("\n\t pi with %ld steps is %lf [PI: %lf]\n\n",
	 num_steps, my_pi, M_PI);

  return 0;
}	  





