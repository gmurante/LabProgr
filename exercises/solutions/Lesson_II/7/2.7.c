/*********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)              */
/*********************************************************************/
/* The program implements the bisection root-finding method that     */
/* applies to any continuous functions for which one knows two       */
/* values with opposite sign.                                        */
/* The function is f(x) = x^x - exp(x) + 1                           */
/*                                                                   */
/* Compile the code:                                                 */
/* $ gcc -Wall -O0 2.7.c -o 2.7.x -lm                                */
/*                                                                   */
/* Run the code:                                                     */
/* $ ./2.7.x <[a,b]>                                                 */
/*                                                                   */
/* Author: David Goz - david.goz@inaf.it                             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR 1.e-5

float function(const float);
float get_zero(float,
	       float);

int main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("\n\t Usage: <executable> <[a, b]> \n\n");
      return -1;
    }
  
  /* Interval [a, b] */
  float a = atof(argv[1]);
  float b = atof(argv[2]);

  printf("\n\t Find zero in [%f, %f]", a, b);
  if ((function(a) * function(b)) > 0.0f)
    {
      printf("\n\t (f(a) * f(b)) > 0 ... exit ... \n\n");
      return -1;
    }

  float zero = get_zero(a, b);

  printf("\n\t Zero in %g\n\n", zero);
  
  return 0;
}

float function(const float x)
{
  return (pow(x,x) - exp(x) + 1.0f);
}

float get_zero(float a,
	       float b)
{
  /* get the midpoint */
  float m = (a + b) * 0.5f;

  /* get f(m) */
  float fm = function(m);

  /* check if the zero has already been found */
  if (fabs(fm) < ERROR)
    return m;

  do
    {
      /* get f(a) */
      float fa = function(a);

      /* move the middle point accordingly */
      if ((fa * fm) < 0.0f)
	b = m; /* zero is in [a,m] */
      else
	a = m; /* zero is in [m,b] */

      /* get m */
      m = (a + b) * 0.5f;

      /* get f(m) */
      fm = function(m);
    } while (fabs(fm) > ERROR);

  return m;
}
