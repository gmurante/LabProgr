/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* Write a function setbits(x,p,n,y) that returns x with the n bits    */
/* that begin at position p set to the rightmost n bits of y, leaving  */
/* the other bits unchanged                                            */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 2.2.c -o 2.2.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./2.2.x                                                           */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

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


int main()
{
  unsigned x = 305417896;
  unsigned y = 4294967295;

  showbits("x", x, sizeof(x));
  showbits("y", y, sizeof(y));

  const unsigned p = 11;
  const unsigned n = 12;
  
  x = setbits(x, p, n, y);

  printf("\n\t p=%u - n=%u", p , n);
  
  showbits("x", x, sizeof(x));
  
  return 0;
}
