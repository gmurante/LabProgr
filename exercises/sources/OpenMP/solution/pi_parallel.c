/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* The program numerically computes the integral of the following function:      */
/*                                                                               */
/*                      f(x) = 4.0 / (1 + x*x)                                   */
/*                                                                               */
/* from 0 to 1. The value of the intergral is pi.                                */
/* This is the parallel implementation.                                          */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra -fopenmp pi_parallel.c -o pi_parallel -lm                 */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./pi_parallel <number of OpenMP threads>                               */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* Assigned tasks:                                                               */
/*                - parallelize the code targeting the for loop over the steps   */
/*                  of the integral. Check the result, and then measure the      */
/*                  time-to-solution (this can be done smoothly using the Unix   */
/*                  'time' command). Does it scale linearly with the number of   */
/*                  OpenMP threads? Any difference in changing the scheduling    */
/*                  policy of the for loop? Why?                                 */
/*********************************************************************************/

#include "my_omp_header.h"

/* number of steps */
const unsigned long int num_steps = 1000000000;
typedef double MyFloat;

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("\n\t USAGE: <executable> <number of OpenMP threads> \n\n");
      return -1;
    }

  const int num_threads = atoi(argv[1]);
  
  MyFloat step = 1.0/(MyFloat) num_steps;

  /* accumulator. OMP initiliazes it at zero since a sum reduction will be performed */
  MyFloat sum;
#pragma omp parallel default(none) shared(step,sum,num_steps) num_threads(num_threads)
  {
#  pragma omp single nowait
    {
      /* get the number of active omp threads */
      printf("\n\t Active OpenMP threads: %d \n",
	     omp_get_num_threads());
    } /* omp single nowait */
    
#  pragma omp for reduction(+:sum) schedule(static) nowait
    for (unsigned long int i=1 ; i<=num_steps ; i++)
      {
	const MyFloat x = (i - 0.5) * step;
	sum += (1.0 / (1.0 + (x * x)));
      } /* omp for nowait */
  } /* omp parallel region */

  const MyFloat my_pi = (4.0 * step * sum);

  printf("\n\t pi with %ld steps is %lf [PI: %lf]\n\n",
	 num_steps, my_pi, M_PI);

  return 0;
}	  





