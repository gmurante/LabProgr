#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double MyData;
#define N (1 << 8)
#define FROM_BYTES_TO_KBYTES (1.0 / 1024.)

int main()
{
  MyData *array = NULL;

  /*
   The  malloc() function allocates size bytes and returns a void pointer to the allocated memory.
   The memory is not initialized (raw data).
   The calloc() function allocates memory for an array of nmemb elements of size bytes each and 
   returns a pointer to the allocated memory. The memory is set to zero.
  */
  array = (MyData *)malloc(N * sizeof(MyData));

  /* check the allocation */
  if (array == NULL)
    {
      printf("\n\t Allocation failed ... aborting ... \n");
      return EXIT_FAILURE;
    }

  /* ... do something ...*/

  /* free memory */
  free(array);
  array = NULL;

  /* array pointer can be reused ... */
  
  return EXIT_SUCCESS;
}
