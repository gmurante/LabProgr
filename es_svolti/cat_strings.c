/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The program aims to concatenate two strings using pointers          */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall cat_strings.c -o cat_strings                            */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./cat_strings                                                     */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
void cat_string(char *, const char *, const char *);

int main()
{
  const char first_string[]  = "First string ";
  const char second_string[] = "Second string";

  /* alloc memory to store concateneted string */
  char string[strlen(first_string) + strlen(second_string) + 1];

  /* concatenate the strings */
  cat_string(string, first_string, second_string);

  printf("\n\t %s [len(string) = %ld]\n\n",
	 string, strlen(string));
  
  return 0;
}

void cat_string(char *string,
		const char *string_1,
		const char *string_2)
{
  int i, j;
  
  /* store string_1 in string */
  for (i=0 ; *(string_1 + i) != '\0' ; *(string + i) = *(string_1 + i) , i++);
  
  /* store string_2 in string */
  for (j=0 ; *(string_2 + j) != '\0' ; *(string + i + j) = *(string_2 + j) , j++);

  /* terminate the string */
  *(string + i + j) = '\0';
  
  return;
}
