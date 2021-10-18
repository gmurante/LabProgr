#include "myheader.h"
static int flag = 1;
void check_args( int n, char **args )
{
  for ( int i = 1; i < n; i++ )
    printf("argument %d is: %s\n", i, *(args+i) );
    printf("FLAG from check_args is: %d\n", flag );
  return;
}
