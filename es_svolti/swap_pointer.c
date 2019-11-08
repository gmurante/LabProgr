/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The program aims to swap the content of two local variables using a */
/* dedicated function using pointers.                                  */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall swap_pointer.c -o swap_pointer                          */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./swap_pointer                                                    */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>

/* function prototypes */
void swap(int *, int *);

int main()
{
  int a = 5;
  int b = 10;
  
  printf("\n\t Before calling swap - a = %d, b = %d \n", a, b);

  /* call swap */
  swap(&a, &b);

  printf("\n\t After calling swap  - a = %d, b = %d \n\n", a, b);
  
  return 0;
}

void swap(int *x, int *y)
{
  /* store x in a local variable tmp */
  const int tmp = *x;

  /* store y in x */
  *x = *y;

  /* store tmp in y */
  *y = tmp;

  return;
}
