#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a = 1, *pa = NULL, **ppa = NULL;

  pa = &a;
  ppa = &pa;

  printf("\n\t    a = %d,   &a = %p                       ",   a,  &a);
  printf("\n\t   pa = %p,  *pa = %d,   &pa = %p           ",  pa, *pa, &pa);
  printf("\n\t  ppa = %p, *ppa = %p, **ppa = %d, &ppa = %p", ppa, *ppa, **ppa, &ppa);

  printf("\n");
  
  return EXIT_SUCCESS;
}
