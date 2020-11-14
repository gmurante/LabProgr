/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Program to compute the area of a Mandelbrot set.                              */
/* Correct answer should be around 1.510659.                                     */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra mandelbrot_serial.c -o mandelbrot_serial                  */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./mandelbrot_serial                                                    */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* History: Originally written by Mark Bull, August 2011.                        */
/*          Changed by Tim Mattson, September 2011.                              */
/*          Modified for the purpose of the course by David Goz.                 */
/*                                                                               */
/* Assigned tasks:                                                               */
/*                 - turning on compiler optimizations:                          */
/*                    - compile the code using the flag -O0 (no optimization),   */
/*                      run the executable, check the result, and get the time   */
/*                      execution using the 'time' command;                      */
/*                    - compile the code using the flag -O3 (with optimization), */
/*                      run the executable, check the result, and get the time   */
/*                      execution using the 'time' command;                      */
/*                                                                               */
/*                  - OpenMP parallelization:                                    */
/*                    - parallelize the code targeting the for loop inside the   */
/*                      main function. Try to change as little as possible the   */
/*                      serial code, verifying result correctness.               */
/*                    - get time measurements using a different number of        */
/*                      OpenMP threads, different number of complex points       */
/*                      (NPOINTS macro), and different compiler optimizations.   */
/*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

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
void testpoint(void);

int main()
{
  /* Loop over grid of points in the complex plane that contains */
  /* the Mandelbrot set. For each point check if it is inside or */
  /* outside the set.                                            */

  for (int i=0 ; i<NPOINTS ; i++)
    {
      Z.r = -2.0 + (2.5 *(MyFloat)(i)/(MyFloat)(NPOINTS)) + EPS;
       
      for (int j=0 ; j<NPOINTS; j++)
	{
	  Z.i = (1.125 * (MyFloat)(j)/(MyFloat)(NPOINTS)) + EPS;
	  testpoint();
	}
    }

  /* Calculate the area of the Mandelbrot set and the relative error */
  const MyFloat area = 2.0 * 2.5 * 1.125 * (MyFloat)((NPOINTS * NPOINTS) - NumOutside)/(MyFloat)(NPOINTS * NPOINTS);
  const MyFloat error = area/(MyFloat)NPOINTS;

  printf("\n\t Area of the Mandlebrot set = %12.8f +/- %12.8f", area, error);
  printf("\n\t Correct answer should be around 1.510659 \n\n");

  return 0;
}

void testpoint(void)
{
  /* Perform the iteratiob Z = Z*Z + C, until |z|>2 when */ 
  /* the complex point is outside the Mandelbrot set.    */
  /* However, if the loop count reaches MAXCOUNT, then   */
  /* the point is considered to be inside the set.       */

  /* local copy of Z */
  complex C = Z;

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
    NumOutside++;

  return;
}
