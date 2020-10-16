/************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                 */
/************************************************************************/
/* Rewrite the function lower (taken from K&R p 43), which converts     */
/* upper case letters to lowercase, with a conditional expression       */
/* instead of if-else.                                                  */
/*                                                                      */
/* int lower(int c)
   {
      if (c >= 'A' && c <= 'Z')
         return c + 'a' - 'A';
      else
         return c;
   }
*/
/*                                                                      */
/* Compile the code:                                                    */
/* $ gcc -Wall -O0 2.5.c -o 2.5.x                                       */
/*                                                                      */
/* Run the code:                                                        */
/* $ ./2.5.x                                                            */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/************************************************************************/

#include <stdio.h>

int new_lower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c -= ('A' - 'a') : c;
}

int main()
{
  const char string[] = "DdaRaxIqR978YQNCXV:!*";
  
  printf("\n\t Original string : %s", string);
  
  printf("\n\t Lowercase string: ");

  for (int i=0 ; string[i]!='\0' ; i++)
    putchar(new_lower(string[i]));

  putchar('\n');

  return 0;
}
