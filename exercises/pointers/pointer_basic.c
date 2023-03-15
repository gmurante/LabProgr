/***********************************************************************/
/* Course: Advanced Programming for Physics                            */
/***********************************************************************/
/* The progam aims to show basic concepts on pointers                  */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall -Wextra pointer_basic.c -o pointer_basic                */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./pointer_basic                                                   */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/* Date: 15th March 2023                                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a = 1;
  /* it's a good practice to always initialize pointers to NULL value */
  int *pa = NULL, **ppa = NULL;

  pa = &a;
  ppa = &pa;

  printf("\n\t    a = %d,   &a = %p                       ",   a,  &a);
  printf("\n\t   pa = %p,  *pa = %d,   &pa = %p           ",  pa, *pa, &pa);
  printf("\n\t  ppa = %p, *ppa = %p, **ppa = %d, &ppa = %p", ppa, *ppa, **ppa, &ppa);

  printf("\n");
  
  return EXIT_SUCCESS;
}
