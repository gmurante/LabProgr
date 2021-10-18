//ciao


#include "myheader.h"

int flag = 0;
int main ( int argc, char **argv )
{


  int ret = welcome( argc );


  check_args( ret, argv );

  printf("In any case, the sq root of 2 is %g\n", sqrt(2.0) );

  printf("Verify externals from main: %f %d\n", 2.*x, j);

  return 0;
}
