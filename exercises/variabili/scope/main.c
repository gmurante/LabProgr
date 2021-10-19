//ciao


#include "myheader.h"

static int flag = 0;
int main ( int argc, char **argv )
{


  int ret = welcome( argc );


  check_args( ret, argv );

  printf("In any case, the sq root of 2 is %g\n", sqrt(2.0) );

  printf("Verify externals from main: %f %d\n", 2.*x, j);
  printf("FLAG from main is: %d\n", flag+4 );

  printf("--------------------------------------\n");
  printf("+ Stitic variable\n");
  for(int i=0; i<10; i++) mystatic();
  return 0;
}
