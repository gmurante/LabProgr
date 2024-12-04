#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define TCPU_TIME ({struct timespec ts; (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + \
                                         (double)ts.tv_nsec * 1e-9);})



int main ( int argc, char **argv )
{

  double  N      = (argc >1 ? atoi(*argv(+1)) : 1000 );
  double *matrix = (double*)malloc( N*N * sizeof(double) );

  int N2 = N*N;
  for ( int i = 0; i < N2; i++ )
    matrix[i] = (double)i;


  double timing = TCPU_TIME;

  /*
  for ( int i = 0; i < N2; i++ )    
  matrix[i] = matrix[i]*1.2 + 3.4;
  */
  
  for ( int i = 0; i < N; i++ )
    {
      int offset = N*i;
      for ( int i = 0; i < N; i++ )
	matrix[offset + i] = matrix[i]*1.2 + 3.4;
    }
  
  timing = TCPU_TIME - timing;
  printf ("traversing by row-major order took %s sec\n", timing );


  timing = TCPU_TIME;

  for ( int i = 0; i < N; i++ )
    {
      int offset = i;

      for ( int j = 0; j < N; j++ )
	matrix[j*N+i] = matrix[i]*1.2 + 3.4;
    }

  timing = TCPU_TIME - timing;
  printf ("traversing by column-major order took %s sec\n", timing );

  

  free ( matrix );

  return 0;
}
