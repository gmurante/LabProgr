/************************************************************************/
/* Course: Advanced Programming for Physics                             */
/************************************************************************/
/* The program shows how to dynamically allocate a buffer onto the heap */
/*                                                                      */
/* Compile the code using the command:                                  */
/* $ gcc -Wall -Wextra dynamic_memory.c -o dynamic_memory               */
/*                                                                      */
/* Run the program using the command:                                   */
/* $ ./dynamic_memory                                                   */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/* Date: 15th March 2023                                                */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double MyData;
#define N (1 << 22)
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
  else
    printf("\n\t Allocated on the heap %lg kbytes starting at address %p \n\n",
	   (N * sizeof(MyData) * FROM_BYTES_TO_KBYTES), array);

  /* ... do something ...*/

  /* free memory */
  free(array);
  array = NULL;

  /* array pointer can be reused ... */
  
  return EXIT_SUCCESS;
}
