/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The program aims to dynamically allocate a matrix of a given        */
/* dimension NROW x NCOL using a contiguous chunk of memory, then      */
/* initializes it as MATRIX[i, j] = i + j, and finally prints in       */
/* the sdout the matrix.                                               */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall matrix_pointer.c -o matrix_pointer                      */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./matrix_pointer                                                  */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* macros */
#define _NROW_   4
#define _NCOL_   3

/* function prototypes */
void matrix_initialization(int *, const int, const int);

void print_matrix(const int *, const int, const int);

int main()
{
  /* pointer to int */
  int *mat=NULL;

  /* array allocation and check */
  if (!(mat = (int *)malloc(_NROW_ * _NCOL_ * sizeof(int))))
    {
      printf("\n\t Allocation failure... aborting\n");
      return -1;
    }
  
  /* matrix initialization */
  matrix_initialization(mat, _NROW_, _NCOL_);

  /* print matrix */
  print_matrix(mat, _NROW_, _NCOL_);
  
  /* free memory */
  free(mat);
  
  return 0;
}

void matrix_initialization(int *A,
			   const int NROW,
			   const int NCOL)
{
  for (int row=0 ; row<NROW ; row++)
    for (int col=0 ; col<NCOL ; col++)
      A[(row * NCOL) + col] = row + col;
  
  return;
}

void print_matrix(const int *mat,
		  const int NROW,
		  const int NCOL)
{
  for (int row=0 ; row<NROW ; row++)
    {
      printf("\n");
      
      for (int col=0 ; col<NCOL ; col++)
	printf("\t MAT[%d, %d] = %d", row, col, mat[(row * NCOL) + col]);
    }

  printf("\n\n");
  
  return;
}
