
#include "myheader.h"

uint welcome( int n )
{
  printf("Welcome in your make+Makefile test\n");
    
  if ( n == 0 )
    printf("You have entered %d argument%c\n", n, (n>1?'s':' '));
  else
    printf("You did not enter any argument\n");

  return n;
}
