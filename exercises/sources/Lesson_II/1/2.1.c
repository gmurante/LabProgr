/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* Write a program to determine the ranges of char, short, int,        */
/* and long variables, both signed and unsigned, by printing           */
/* appropriate values from standard headers and by direct computation. */
/* Harder if you compute them: determine the ranges of the various     */
/* floating-point types.                                               */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 2.1.c -o 2.1.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./2.1.x                                                           */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <limits.h>
#include <float.h>

float getFloat(const unsigned char sign,
	       const unsigned char exp,
	       const unsigned int  mantissa)
{
  /* 1-bit for sign (leftmost) */
  /* 8-bit for exponent        */
  /* 23-bit for mantissa       */

  /* Note:                                                                     */
  /* 0x7FFFFFFF is a number in hexadecimal (2147483647 in decimal) that        */
  /* represents the maximum positive value for a 32-bit signed binary integer, */
  /* i.e. 2^31 - 1.                                                            */
  
  unsigned f = (unsigned)(sign << 31) | (unsigned)(exp << 23) | (unsigned)(mantissa & 0x7FFFFFFF);

  return *((float *)&f);
}

int main()
{ 
  /* unsigned char */
  printf("\n\t Range of unsigned char");
  printf("\n\t min: %d - max: %d \n",
	 0, (1 << (sizeof(unsigned char)*8)) - 1);
  printf("\t UCHAR_MIN: %d - UCHAR_MAX: %d \n",
	 0, UCHAR_MAX);

  /* signed char */
  printf("\n\t Range of char");
  printf("\n\t min: %d - max: %d \n",
	 - (1 << ((sizeof(unsigned char)*8) - 1)),
	 (1 << (sizeof(char)*8 - 1)) - 1);
  printf("\t CHAR_MIN: %d - CHAR_MAX:%d \n",
	 CHAR_MIN, CHAR_MAX);
 
  /* int */
  printf("\n\t Range of int");
  printf("\n\t min: %d - max: %d \n",
	 - (1 << ((sizeof(int)*8) - 1)),
	 (1 << (sizeof(int)*8 - 1)) - 1);  
  printf("\t INT_MIN: %d - INT_MAX: %d \n",
	 INT_MIN, INT_MAX);

  /* analogous for other data types...        */
  /* another way using bitwise, e.g. long int */
  unsigned long ld;
  ld = ~0;
  ld >>= 1;
  printf("\n\t min:%ld - max:%ld \n",
	 -ld-1, ld);
  printf("\t LONG_MIN: %ld - LONG_MAX: %ld \n",
         LONG_MIN, LONG_MAX);
  
  /* float */
  /* pointer arithmetic is required! */
  printf("\n\t Range of float");
  printf("\t min: %g - max: %g \n",
	 getFloat(1, 0, 1), getFloat(0, ~0-1, ~0));
  printf("\t FLT_MIN: %lg - FLT_MAX: %lg \n\n",
	 FLT_MIN, FLT_MAX);
  
  return 0;
}
