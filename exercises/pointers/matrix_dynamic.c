#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double MyData;
#define NROWS 2
#define NCOLS 4

int main()
{
  /* heap allocation */
  MyData **mat = NULL;
  
  /* rows dynamic allocation */
  mat = (MyData **)malloc(NROWS * sizeof(MyData *));
  assert(mat != NULL);

  /* columns dynamic allocation */
  for (int row=0 ; row<NROWS ; row++)
    {
      mat[row] = (MyData *)malloc(NCOLS * sizeof(MyData));
      assert(mat[row] != NULL);
    }

  /* fill the matrix */
  for (int row=0 ; row<NROWS ; row++)
    {
      printf("\n");
      for (int col=0 ; col<NCOLS ; col++)
	{
	  mat[row][col] = (MyData)(row + col);
	  printf("\t mat[%d][%d] = %g", row, col, mat[row][col]);
	}
    }
  printf("\n\n");

  /* free memory */
  for (int row=0 ; row<NROWS ; row++)
    {
      free(mat[row]);
      mat[row] = NULL;
    }
  
  free(mat);
  mat = NULL;
  
  return EXIT_SUCCESS;
}
