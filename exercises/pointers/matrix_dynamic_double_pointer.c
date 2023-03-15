/************************************************************************/
/* Course: Advanced Programming for Physics                             */
/************************************************************************/
/* The program shows how to dynamically allocate a 2D matrix using the  */
/* technique of a double pointer.                                       */
/* However, such an allocation, is not 'cache-friendly' (i.e. the CPU   */
/* fetches data from DRAM in chunks and store them into a fast and      */
/* relatively small memory close to the CPU's ALU). This because each   */
/* row of the matrix requires a 'malloc' system call, and so rows       */
/* might be mapped into non contiguous chuncks in memory.               */
/*                                                                      */
/* Compile the code using the command:                                  */
/* $ gcc -Wall -Wextra matrix_dynamic_double_pointer.c -o \             */
/*     matrix_dynamic_double_pointer                                    */
/*                                                                      */
/* Run the program using the command:                                   */
/* $ ./matrix_dynamic_double_pointer                                    */
/*                                                                      */
/* Suggestion:                                                          */
/* after the development of an algorithm that relies on dynamic memory  */
/* allocation, it is a good practice to find memory leaks in the        */
/* program. A memory leak happens when dynamically allocated memory is  */
/* either not freed when it ìs not longer needed or when the            */
/* allocated memory is unreachable (i.e. the program no longer has any  */
/* reacheable pointer refers to it).                                    */
/* The check can be done using the 'valgrind' tool.                     */
/* $ sudo apt install valgrind  # Ubuntu, Debian, etc.                  */
/* $ sudo yum install valgrind  # RHEL, CentOS, Fedora, etc.            */
/* $ sudo pacman -Syu valgrind  # Arch, Manjaro, Garuda, etc            */
/*                                                                      */
/* In order to run the program using the 'valgrind' tool compile the    */
/* code using the command:                                              */
/* $ gcc -Wall -Wextra -g -O0 matrix_dynamic_double_pointer.c -o \      */
/*     matrix_dynamic_double_pointer_valgrind                           */
/*                                                                      */
/* Run the program using the command:                                   */
/* $ valgrind --leak-check=full --show-leak-kinds=all           \       */
/*   --track-origins=yes --verbose --log-file=valgrind-out.txt  \       */
/*   ./matrix_dynamic_double_pointer_valgrind                           */
/*                                                                      */
/* Finally, you would like to see a Valgrind report (valgrind-out.txt)  */
/* that looks like this:                                                */
/*                                                                      */
/* HEAP SUMMARY:                                                        */
/*     in use at exit: 0 bytes in 0 blocks                              */
/*     total heap usage: 4 allocs, 4 frees, 1,104 bytes allocated       */
/*                                                                      */
/*   All heap blocks were freed -- no leaks are possible                */
/*                                                                      */
/*   ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)     */
/*                                                                      */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/* Date: 15th March 2023                                                */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double MyData;
#define NROWS 2 /* number of rows    */
#define NCOLS 4 /* number of columns */

/* the function allocates into the heap the 2D matrix */
/* and returns a double pointer, which points to the  */
/* beginning of the first row of the matrix           */
MyData **matrix_allocation(const unsigned int nrows,
			   const unsigned int ncols)
{
  /* heap allocation */
  MyData **mat = NULL;
  
  /* allocate dynamically a buffer of size 'nrows' of */
  /* MyData pointers, one for each row of the matrix  */
  mat = (MyData **)malloc(nrows * sizeof(MyData *));
  assert(mat != NULL);

  /* columns dynamic allocation */
  for (unsigned int row=0 ; row<nrows ; row++)
    {
      /* allocate a MyData chunck of size 'ncols', */
      /* one for each row of the matrix            */
      mat[row] = (MyData *)malloc(ncols * sizeof(MyData));
      assert(mat[row] != NULL);
    }  

  return mat;
}

/* the function initializes the matrix */
void matrix_init(MyData **const     mat,
		 const unsigned int nrows,
		 const unsigned int ncols)
{
  /* fill the matrix */
  for (unsigned int row=0 ; row<nrows ; row++)
    for (unsigned int col=0 ; col<ncols ; col++)
      mat[row][col] = (MyData)(row + col);
    
  return;
}

/* the function prints on the stdout the matrix */
void matrix_print(const MyData **const mat,
		  const unsigned int   nrows,
		  const unsigned int   ncols)
{
  for (unsigned int row=0 ; row<nrows ; row++)
    {
      printf("\n");
      for (unsigned int col=0 ; col<ncols ; col++)
	printf("\t matrix[%u][%u] = %lg", row, col, mat[row][col]);
    }

  printf("\n");
  
  return;
}
void matrix_free(MyData **const     mat,
		 const unsigned int nrows)
{
  /* free each row */
  for (unsigned int row=0 ; row<nrows ; row++)
    free(mat[row]);

  /* free the buffer of 'nrows' pointers */
  free(mat);

  return;
}

int main()
{
  /* matrix allocation */
  MyData **mat = matrix_allocation(NROWS, NCOLS);
  
  /* fill the matrix */
  matrix_init(mat, NROWS, NCOLS);

  /* print the matrix */
  matrix_print(mat, NROWS, NCOLS);
  
  /* free memory */
  matrix_free(mat, NROWS);
  mat = NULL;

  /* ... eventually do somethgn else ... */
  /* N.B. mat can be re-used */
  
  return EXIT_SUCCESS;
}
