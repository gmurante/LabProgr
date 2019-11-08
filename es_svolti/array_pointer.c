/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The program aims to dynamically allocate an array of a given        */
/* dimension N, checks that it has been successfully allocated,        */
/* then initializes it using random numbers uniformly ditributed in    */
/* [0, N), and evaluates the sum of arrays elements. Finally, it       */
/* frees the allocated memory.                                         */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall array_pointer.c -o array_pointer                        */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./array_pointer                                                   */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* macros */
#define _N_           10
#define _ARRAY_MIN_   0
#define _ARRAY_MAX_   10

/* function prototypes */
void array_initialization(float *, const int,
			  const float, const float);

void sum_array(const float *, const int);

int main()
{
  /* pointer to float */
  float *x=NULL;

  /* array allocation and check */
  if (!(x = (float *)malloc(_N_ * sizeof(float))))
    {
      printf("\n\t Allocation failure... aborting\n");
      return -1;
    }
  
  /* array initialization */
  array_initialization(x, _N_, _ARRAY_MIN_, _ARRAY_MAX_);

  /* sum up arrays elements */
  sum_array(x, _N_);
  
  /* free memory */
  free(x);
  
  return 0;
}

void array_initialization(float *A,
			  const int N,
			  const float min,
			  const float max)
{
  /* set random seed */
  srand(time(NULL));

  /* fill array with random numbers */
  for (int i=0 ; i<N ; i++)
    {
      /* get random number in [0, 1)*/
      float random = rand() / (RAND_MAX + 1.0);

      /* fill the array */
      A[i] = random * (max - min) + min;
    }
  
  return;
}

void sum_array(const float *array,
	       const int dim)
{
  float sum = 0.0;
  for (int i=0 ; i<dim ; i++)
    sum += array[i];

  printf("\n\t Sum of arrays elements = %f\n\n",sum);
  
  return;
}
