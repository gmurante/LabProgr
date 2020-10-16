/************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                 */
/************************************************************************/
/* Write a function rightrot(x,n) that returns the value of the integer */
/* x rotated to the right by n bit positions.                           */
/*                                                                      */
/* Compile the code:                                                    */
/* $ gcc -Wall -O0 2.4.c -o 2.4.x                                       */
/*                                                                      */
/* Run the code:                                                        */
/* $ ./2.4.x                                                            */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>

/* The following function (called getbits) is taken from K&R p 49 */
/* getbits: get n bits from position p. Bit position 0 is assumed */
/*          to be at the right end. So p>=0 and n>=1 with the     */
/*          constrain p > (n - 1)                                 */
unsigned getbits(const unsigned x,
		 const unsigned p,
		 const unsigned n)
{
  unsigned ret = (x >> (p - n + 1)) & ~(~0 << n);
  
  return ret;
}

/* showbits - shows integers as bit strings */
/* - usage: showbits(x, sizeof(x))          */
void showbits(const char *name,
	      const unsigned x,
	      const size_t s)
{
  const int bits = (s * 8);

  printf("\n\t %s - decimal: %u %s", name, x, " - binary: ");
  
  for (int i=bits-1 ; i>=0 ; i--)
    getbits(x, i, 1) ? putchar('1') : putchar('0');
      
  printf("\n");
  
  return;
}

unsigned rightrot(const unsigned x,
		  const unsigned n)
{
  /* get the bits of x */
  const unsigned bits = (sizeof(x) * 8);

  /* n-bits right shift of x */
  const unsigned x_rightshift = (x >> n);

  /* mask to get the rightmost n-bits */
  const unsigned mask = ~(~0 << n);

  /* n-bits rightmost of x */
  const unsigned x_rightmost = (x & mask);

  /* left shift of x_rightmost by (bits - n) */
  const unsigned leftshift_x_rightmost = (x_rightmost << (bits - n));
  
  return (x_rightshift | leftshift_x_rightmost);
}

int main()
{
  unsigned x = 185;
  showbits("x", x, sizeof(x));

  const unsigned n = 8;
  
  x = rightrot(x, n);

  printf("\n\t n=%u", n);
  
  showbits("x", x, sizeof(x));
  
  return 0;
}
