

#include "myheader.h"


int main ( int argc, char **argv )
{

  int ret = welcome( argc );

  check_args( ret, argv );

  printf("In any case, the sq root of 2 is %g\n", sqrt(2.0) );
  
  return 0;
}
