/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The program aims to count the length of a string using the          */
/* arithmetic of pointers.                                             */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall string_pointer.c -o string_pointer                      */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./string_pointer                                                  */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <string.h>

int main()
{
  /* string definition */
  char string[] = "Hello World!";

  /* pointer to string */
  char *p = &string[0];

  /* count the number of characters in string */
  int i;
  for (i=0 ; *(p + i) != '\0'; i++);

  printf("\n\t The length of \"%s\" is %d [strlen(%s) = %ld]\n\n",
	 string, i, string, strlen(string));
  
  return 0;
}
