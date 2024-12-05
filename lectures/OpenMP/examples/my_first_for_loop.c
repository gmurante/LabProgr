#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define TCPU_TIME ({struct timespec ts; (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + \
                                         (double)ts.tv_nsec * 1e-9);})

#define ThCPU_TIME ({struct timespec ts; (clock_gettime( CLOCK_THREAD_CPUTIME_ID, &ts ), (double)ts.tv_sec + \
                                         (double)ts.tv_nsec * 1e-9);})


typedef unsigned int uint;


int main( int argc, char **argv)
{

  int N       = (argc > 1? atoi(*(argv+1)) : 100000 );		
  uint *array = (uint*)malloc( N*sizeof(uint) );
  unsigned long long int sum = 0;

  
  
#if defined _OPENMP

  double timing = ThCPU_TIME;
  
  int nthreads;
  #pragma omp parallel
  {
    double mytiming = ThCPU_TIME;
    
    int me = omp_get_thread_num();
    if ( me == 0 )
      nthreads = omp_get_num_threads();
    
   #pragma omp barrier

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

    mytiming = ThCPU_TIME - mytiming;

   #pragma omp barrier
    printf("\tthread %d run in %g sec\n", mytiming);
    
  }

  timing = ThCPU_TIME - timing;
 #else

  double timing = TCPU_TIME;
  for ( uint i = 0; i < N; i++ )
    array[i] = i;
  
  for ( uint i = 0; i < N; i++ )
    sum += array[i];

  timing = TCPU_TIME - timing;
 #endif

  

  
  printf("and eventually we've got %s result in %g seconds!\n",
	 ((sum == (unsigned long long)N*(N-1)/2) ? "the correct" : "a crap"), timing );

  free ( array );
  
  return 0;
}
