/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* Write a pointer version of the function strcat that is showed in    */
/* Chapter 2: strcat(s ,t ) of K&R book (pag. 48). The function copies */
/* the string t to the end of s. It is defined in the standard header  */
/* <string.h>.                                                         */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 5.3.c -o 5.3.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./5.3.x                                                           */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>

#define MAXCHAR   100

/* StringCat: concatenate t to end of s; s must be big enough */
/* taken from K&R pag. 48                                     */
void StringCat(char s[], char t[])
{
  int i,j;

  i = j = 0;
  while (s[i] != '\0') /* find end of s */
    i++;

  while ((s[i++] = t[j++]) != '\0'); /* copy t */
}

/* pointer version of StringCat function */
void PstringCat(char *s,
		char *t)
{
  /* move pointer to the end of s */
  while (*s) s++;
  
  /* copy t to end of s */
  while ((*s++ = *t++));

  return;
}

int main()
{
  /* define character array with dimension MAXCHAR */
  char s[MAXCHAR] = "Hello ";
  /* define a constant string to attach to the end of s */
  char *t = "World";

  printf("\n\t StringCat(%s,%s)  = ", s, t);
  StringCat(s, t);
  printf("%s \n", s);

  char w[MAXCHAR] = "Hello ";
  printf("\n\t PstringCat(%s,%s) = ", w, t);
  PstringCat(w, t);
  printf("%s \n\n", w); 

  return 0;
}
