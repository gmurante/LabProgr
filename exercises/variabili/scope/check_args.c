#include "myheader.h"
void check_args( int n, char **args )
{
  int i = 0;
  for (i = 1; i < n; i++ )
    printf("argument %d is: %s\n", i, *(args+i) );

  {
      int i=0;
    printf("FLAG inside block in check_args  is: %d\n", i );
  }
  printf("FLAG outside block in check_args is: %d\n", i );
  return;
}
