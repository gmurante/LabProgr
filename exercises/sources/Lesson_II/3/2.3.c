/************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                 */
/************************************************************************/
/* Write a function invert(x,p,n) that returns x with the n bits that   */
/* begin at position p inverted (i.e., 1 changed into 0 and vice versa) */
/* leaving the others unchanged.                                        */
/*                                                                      */
/* Compile the code:                                                    */
/* $ gcc -Wall -O0 2.3.c -o 2.3.x                                       */
/*                                                                      */
/* Run the code:                                                        */
/* $ ./2.3.x                                                            */
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

unsigned setbits(unsigned       x,
                 const unsigned p,
                 const unsigned n,
                 const unsigned y)
{
  /* mask to get the rightmost n bits */
  unsigned mask = ~(~0 << n);

  /* get the rightmost n bits of y */
  unsigned y_mask = (y & mask);

  /* shift y_mask by (p-n+1) bits */
  y_mask <<= (p - n + 1);

  /* shift the mask by (p-n+1) bits */
  mask <<= (p - n + 1);

  /* set to zero n bits of x from position p */
  x &= ~mask;

  return (x | y_mask);
}

unsigned invertbits(unsigned       x,
		    const unsigned p,
		    const unsigned n)
{
  /* extract from x the inverted bits */
  unsigned inv = getbits(~x, p, n);

  /* copy the inverted bits on x */
  x = setbits(x, p, n, inv);

  return x;
}

int main()
{
  unsigned x = 305417896;
  showbits("x", x, sizeof(x));

  const unsigned p = 10;
  const unsigned n = 5;
  
  x = invertbits(x, p, n);

  printf("\n\t p=%u - n=%u", p , n);
  
  showbits("x", x, sizeof(x));
  
  return 0;
}
