/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Program to evaluate the cache performance. The program allocates a 3D matrix  */
/* and initializes it using three functions that use different memory patterns.  */
/*                                                                               */
/* Valgrind tool is required.                                                    */
/* Compile the code using the Makefile                                           */
/* $ make info   ---> to get compilation options                                 */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*********************************************************************************/

#include "my_header.h"

void mat1(MyFloat *mat, const int size);

void mat2(MyFloat *mat, const int size);

void mat3(MyFloat *mat, const int size);

int main()
{
  /* 3D matrix allocation */
  MyFloat *mat = NULL;
  if (!(mat = (MyFloat *)malloc(SIZE * SIZE * SIZE * sizeof(*mat))))
    {
      printf("\n\t Cannot allocate the matrix ... aborting ... \n\n");
      return -1;
    }

  MyFloat cpu_start, cpu_stop;

  cpu_start = wall_time();
  mat1(mat, SIZE);
  cpu_stop = wall_time();
  printf("\n\t Time with fast index outer loop           : %lg [s]",
	 (cpu_stop - cpu_start));

  cpu_start = wall_time();
  mat2(mat, SIZE);
  cpu_stop = wall_time();
  printf("\n\t Time with fast index inner loop           : %lg [s]",
	 (cpu_stop - cpu_start));

  cpu_start = wall_time();
  mat3(mat, SIZE);
  cpu_stop = wall_time();
  printf("\n\t Time with fast index inner loop (reversed): %lg [s]\n\n",
	 (cpu_stop - cpu_start));
  
  free(mat);
    
  return 0;
}

/* fast index outer loop */
void mat1(MyFloat *mat, const int n)
{
  for (int k=0 ; k<n ; k++)
    for (int j=0 ; j<n ; j++)
      for (int i=0 ; i<n ; i++)
	mat[(i * n + j) * n + k] = 1.3;
  
  return;
}

/* fast index inner loop */
void mat2(MyFloat *mat, const int n)
{
  for (int i=0 ; i<n ; i++)
    for (int j=0 ; j<n ; j++)
      for (int k=0 ; k<n ; k++)
	mat[(i * n + j) * n + k] = 2.3;
  
  return;
}

/* fast index inner loop reversed */
void mat3(MyFloat *mat, const int n)
{
  for (int i=n-1 ; i>=0 ; i--)
    for (int j=n-1 ; j>=0 ; j--)
      for (int k=n-1 ; k>=0 ; k--)
	mat[(i * n + j) * n + k] = 3.3;
  
  return;
}
