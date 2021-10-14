/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* The program computes the matrix multiplication:                               */
/*                                                                               */
/*                              C = A * B                                        */
/*                                                                               */
/* A and B are constant, so a quick test of the multiplication can be performed. */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra -fopenmp matmul_parallel.c -o matmul_parallel             */
/*                                                                               */
/* Run the code:                                                                 */
/* $ ./matmul_parallel <number of OpenMP threads>                                */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* History: Originally written by Tim Mattson, November 1999.                    */
/*          Modified for the purpose of the course by David Goz.                 */
/*                                                                               */
/* Assigned tasks:                                                               */
/*                - try to parallelize the code targeting the matmul function    */
/*                  using the simplest approach.                                 */
/*                  Check the result, and then measure the time-to-solution      */
/*                  using the 'omp_get_wtime' library function. Does it scale    */
/*                  varying the number of OpenMP threads? Any difference in      */
/*                  changing the scheduling policy of the for loop? Why?         */
/*********************************************************************************/

#include "my_omp_header.h"

#define ORDER   1000
#define AVAL    3.0
#define BVAL    5.0
#define TOL     0.001

typedef double MyFloat;

void init_matrices(MyFloat *restrict  A,
		   MyFloat *restrict  B,
		   MyFloat *restrict  C,
		   const unsigned int size)
{
  for (unsigned int i=0 ; i<(size * size) ; i++)
      {
	A[i] = AVAL;
	B[i] = BVAL;
	C[i] = 0.0;
      }
  
  return;
}

void matmul(MyFloat *restrict  A,
	    MyFloat *restrict  B,
	    MyFloat *restrict  C,
	    const unsigned int size)
{
#pragma omp for nowait /* trivial way to parallelize over i */
  for (unsigned int i=0 ; i<size ; i++)
    {
      for (unsigned int j=0 ; j<size ; j++)
	{
	  MyFloat sum = 0.0;
	  for (unsigned int k=0 ; k<size ; k++)
	    {
	      /* C[i][j] = sum (over k) (A[i][k] * B[k][j]) */
	      sum += (A[(i * size) + k] * B[(k * size) + j]);
	    } /* sum over elements */

	  /* store the value C[i][j] */
	  C[(i * size) + j] = sum;
	} /* loop over cols */
    } /* loop over rows */

  return;
}

void check(const MyFloat     *matrix,
	   const unsigned int size)
{
  const MyFloat cval = (size * AVAL * BVAL);

  MyFloat errsq = 0.0;
  for (unsigned int i=0 ; i<(size * size) ; i++)
    {
      MyFloat err = (matrix[i] - cval);
      errsq += (err * err);
    }

  if (errsq > TOL)
    printf("\n\t Check failed! \n\n");
  else
    printf("\n\t Check OK! \n\n");
  
  return;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("\n\t USAGE: <executable> <number of OpenMP threads> \n\n");
      return -1;
    }

  const int num_threads = atoi(argv[1]);
  
  /* matrix's dimension */
  const unsigned int s2ize = (ORDER * ORDER);
  
  /* The program works with square matrices */
  /* Allocate buffer to store all matrices  */
  MyFloat *buffer = NULL;
  if (!(buffer = (MyFloat *)malloc(3 * s2ize * sizeof(MyFloat))))
    {
      printf("\n\t Cannot allocate matrices ... aborting ... \n\n");
      return -1;
    }

  /* set pointer for matrix A */
  MyFloat *A = buffer;

  /* set pointer for matrix B */
  MyFloat *B = A + s2ize;

  /* set pointer for matrix C */
  MyFloat *C = B + s2ize;

  /* Initialize matrices */
  init_matrices(A, B, C, ORDER);

  /* perform the matrix multiplication */
  double start = omp_get_wtime();

#pragma omp parallel default(none) shared(A, B, C) num_threads(num_threads)
  {
#  pragma omp single nowait
    {
      /* get the number of active omp threads */
      printf("\n\t Active OpenMP threads: %d \n",
	     omp_get_num_threads());
    } /* omp single nowait */
    
    matmul(A, B, C, ORDER);
  } /* omp parallel region */

  double end = omp_get_wtime();
  
  /* check the result */
  check(C, ORDER);

  /* free memory */
  free(buffer);

  printf("\n\t Time-to-solution: %lg ",
	 (end - start));
  
  const double mflops = 2.0 * (ORDER * ORDER * ORDER) / (1.e6 * (end - start));
  printf("\n\t Order %d multiplication at %lg mflops \n\n",
	 ORDER, mflops);
  
  return 0;
}
