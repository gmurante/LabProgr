/***********************************************************************/
/* Course: Advanced Programming for Physics                            */
/***********************************************************************/
/* The progam aims to show basic concepts on pointers                  */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall -Wextra pointer_type.c -o pointer_type                  */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./pointer_type                                                    */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/* Date: 15th March 2023                                               */
/***********************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main()
{
  char c, *pc;
  float a, *pa;
  double b, *pb;
  int i[10], *pi;
  
  printf("\n\t sizeof(char)      = %lu - sizeof(pointer char)   = %lu",      sizeof(c), sizeof(pc));
  printf("\n\t sizeof(float)     = %lu - sizeof(pointer float)  = %lu",      sizeof(a), sizeof(pa));
  printf("\n\t sizeof(double)    = %lu - sizeof(pointer double) = %lu",      sizeof(b), sizeof(pb));
  printf("\n\t sizeof(int array) = %lu - sizeof(pointer int)    = %lu\n\n",  sizeof(i), sizeof(pi));

  /* 
    Question:
       - Why does not the size of different type pointers change ?
  */
  
  return EXIT_SUCCESS;
}
