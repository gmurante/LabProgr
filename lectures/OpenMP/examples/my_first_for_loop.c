#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define TCPU_TIME ({struct timespec ts; (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + \
                                         (double)ts.tv_nsec * 1e-9);})


typedef unsigned int uint;


int main( int argc, char **argv)
{

  int N       = (argc > 1? atoi(*(argv+1)) : 100000 );		
  uint *array = (uint*)malloc( N*sizeof(uint) );
  unsigned long long int sum = 0;

  double timing = TCPU_TIME;
  
#if defined _OPENMP
  
  int nthreads;
  #pragma omp parallel
  {
    int me = omp_get_thread_num();
    if ( me == 0 )
      nthreads = omp_get_num_threads();
    
   #pragma omp barrier;

    uint chunk    = N / nthreads;    
    uint reminder = N % nthreads;
    uint mystart, myend;

    // ternary operator
    // ( conditional statement ? true_branch : false_branch )
    
    mystart = chunk*me + (me<reminder ? me : reminder);
    myend   = mystart + chunk + (me < reminder);

    printf ("thread %d has been assigned with iterations from %u to %u\n",
	    me, mystart, myend );
    
    for ( uint i = mystart; i < myend; i++ )
      array[i] = i;
    
    for ( uint i = mystart; i < myend; i++ )
     #pragma omp atomic update
      sum += array[i];

  }

 #else
  
  for ( uint i = mystart; i < myend; i++ )
    array[i] = i;
  
  for ( uint i = mystart; i < myend; i++ )
    sum += array[i];
  
 #endif

  timing = TCPU_TIME - timing;

  
  printf("and eventually we've got %s result in %g seconds!\n",
	 (sum == N*(N-1)/2 ? "the correct" : "a crap") );

  free ( array );
  
  return 0;
}
