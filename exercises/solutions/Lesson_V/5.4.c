/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* Write the function strend (s ,t), which returns 1 if the string t   */
/* occurs at the end of the string s, and zero otherwise.              */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 5.4.c -o 5.4.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./5.4.x                                                           */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>

int strend(char* s,
	   char* t)
{
  /* get the length of s */
  /* the same result can be achieved using the strlen function defined in <string.h> */
  char *tmp_s = s;
  while (*tmp_s) tmp_s++;
  const size_t s_length = (tmp_s - s);

  /* get the length of t */
  char *tmp_t = t;
  while (*tmp_t) tmp_t++;
  const size_t t_length = (tmp_t - t);

  /* if s_length < t_length then s cannot contain t */
  if (s_length < t_length)
    return 0;
  
  /* move s to (strlen(s) - strlen(t)) */
  s += (s_length - t_length);
  
  /* move s checking if string t occurs at its end */
  /* while loop stops when *s == '\0'              */
  while ((*s) && (*s++ == *t++));

  /* if *s=='\0' then return 1, otherwise return 0 */
  return !(*s);
}

int main()
{
  char *s = "Hello World";
  char *t = "World";
  
  printf("\n\t strend(%s, %s) = %d \n\n",
	 s, t, strend(s, t));
  
  return 0;
}

