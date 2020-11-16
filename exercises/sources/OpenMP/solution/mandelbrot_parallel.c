/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Program to compute the area of a Mandelbrot set.                              */
/* Correct answer should be around 1.510659.                                     */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra -fopenmp mandelbrot_parallel.c -o mandelbrot_parallel     */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./mandelbrot_parallel <number of OpenMP threads>                       */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* History: Originally written by Mark Bull, August 2011.                        */
/*          Changed by Tim Mattson, September 2011.                              */
/*          Modified for the purpose of the course by David Goz.                 */
/*                                                                               */
/* OpenMP parallelization:                                                       */
/*                    - the outermost for loop inside the main function is       */
/*                      parallelized. Loop counters i and j are already private  */
/*                      since they are decleared inside the parallel region      */
/*                      (OpenMP rule). The global complex number Z is promoted   */
/*                      to be private inside the parallel region.                */
/*                      The only serial code change required is in the           */
/*                      'testpoint' function argument. In the serial code, the   */
/*                      'testpoint' function has access to the global complex    */
/*                      point Z, which is shared among OpenMP threads. For this  */
/*                      reason, first Z is decleared private to each threads in  */
/*                      the parallel region, and second Z is passed as argument  */
/*                      to the 'testpoint' function (i.e. assigned to the stack  */
/*                      of each thread). This way guarantees that Z is private   */
/*                      to each thread. Lastly, the update of NumOutside counter */
/*                      must be atomic inside the 'testpoint' function.          */
/*                                                                               */
/*                    - question:                                                */
/*                                - why does the dynamic schedule guarantee the  */
/*                                  best performance in terms of time to         */
/*                                  solution?                                    */
/*********************************************************************************/

/* header required for OpenMP */
#include "my_omp_header.h"

#define NPOINTS 1000
#define MAXITER 1000
#define EPS     (1.0e-5)
/* macro for complex modulus */
#define MOD(A, B) (((A) * (A)) + ((B) * (B)))

typedef double MyFloat;

/* complex number */
typedef struct
{
  MyFloat r; /* real part      */
  MyFloat i; /* imaginary part */
} complex;

/* global structure to store a point */
complex Z;
/* global number of points outside the Mandelbrot set */
unsigned int NumOutside = 0;

/* function prototype */
void testpoint(const complex);

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("\n\t Usage: <executable> <number of OpenMP threads> \n\n");
      return -1;
    }

  const int num_threads = atoi(argv[1]);
  
  /* Loop over grid of points in the complex plane that contains */
  /* the Mandelbrot set. For each point check if it is inside or */
  /* outside the set.                                            */

#pragma omp parallel default(none) private(Z) num_threads(num_threads)
  {
#   pragma omp single nowait
    {
      /* get the number of active omp threads */
      printf("\n\t Active OpenMP threads: %d \n",
	     omp_get_num_threads());
    } /* omp single nowait */

#   pragma omp for schedule(dynamic) nowait
    for (int i=0 ; i<NPOINTS ; i++)
      {
	Z.r = -2.0 + (2.5 *(MyFloat)(i)/(MyFloat)(NPOINTS)) + EPS;
       
	for (int j=0 ; j<NPOINTS; j++)
	  {
	    Z.i = (1.125 * (MyFloat)(j)/(MyFloat)(NPOINTS)) + EPS;
	    testpoint(Z);
	  }
      }
  } /* omp parallel region */

  /* Calculate the area of the Mandelbrot set and the relative error */
  const MyFloat area = 2.0 * 2.5 * 1.125 * (MyFloat)((NPOINTS * NPOINTS) - NumOutside)/(MyFloat)(NPOINTS * NPOINTS);
  const MyFloat error = area/(MyFloat)NPOINTS;

  printf("\n\t Area of the Mandlebrot set = %12.8f +/- %12.8f", area, error);
  printf("\n\t Correct answer should be around 1.510659 \n\n");

  return 0;
}

void testpoint(const complex P)
{
  /* Perform the iteration Z = Z*Z + C, until |Z|>2 when */ 
  /* the complex point is outside the Mandelbrot set.    */
  /* However, if the loop count reaches MAXCOUNT, then   */
  /* the point is considered to be inside the set.       */

  /* local copy of complex point */
  complex C = P;
  const complex Z = P;

  /* initialize the counter */     
  unsigned int counter = 0;
  while ((counter++ < MAXITER) && (MOD(C.r, C.i) <= 4.0))
    {
      /* current real part */
      const MyFloat r = (C.r * C.r) - (C.i * C.i) + Z.r;

      /* current img part */
      const MyFloat i = ((2.0 * C.r * C.i) + Z.i);

      /* store new real part */
      C.r = r;

      /* store new img part */
      C.i = i;
    }

  if (MOD(C.r, C.i) > 4.0)
    {
#   pragma omp atomic
      NumOutside++;
    }

  return;
}
