#include "myheader.h"
void check_args( int n, char **args )
{
  for ( int i = 1; i < n; i++ )
    printf("argument %d is: %s\n", i, *(args+i) );

  return;
}
