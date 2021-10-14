#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TYPE double

/*
    C = alpha * A + B
*/
int main(int argc, char *argv[])
{

	int	M = 5000;
  TYPE val = 2.;
  TYPE	alpha = 1.0;

	TYPE startTime, stopTime, wtime;
	struct timespec	ts;
	clockid_t	id = CLOCK_PROCESS_CPUTIME_ID;
	/*
	       CLOCK_REALTIME
	              System-wide clock that measures real (i.e., wall-clock) time.  Setting this clock requires appropriate privileges.  This clock is affected by discontinuous jumps in the sys‐
	              tem time (e.g., if the system administrator manually changes the clock), and by the incremental adjustments performed by adjtime(3) and NTP.
	       CLOCK_REALTIME_COARSE (since Linux 2.6.32; Linux-specific)
	              A faster but less precise version of CLOCK_REALTIME.  Use when you need very fast, but not fine-grained timestamps.
	       CLOCK_MONOTONIC
	              Clock that cannot be set and represents monotonic time since some unspecified starting point.  This clock is not affected by discontinuous jumps in the system time (e.g., if
	              the system administrator manually changes the clock), but is affected by the incremental adjustments performed by adjtime(3) and NTP.
	       CLOCK_MONOTONIC_COARSE (since Linux 2.6.32; Linux-specific)
	              A faster but less precise version of CLOCK_MONOTONIC.  Use when you need very fast, but not fine-grained timestamps.
	       CLOCK_MONOTONIC
	              Clock that cannot be set and represents monotonic time since some unspecified starting point.  This clock is not affected by discontinuous jumps in the system time (e.g., if
	              the system administrator manually changes the clock), but is affected by the incremental adjustments performed by adjtime(3) and NTP.
	       CLOCK_MONOTONIC_COARSE (since Linux 2.6.32; Linux-specific)
	              A faster but less precise version of CLOCK_MONOTONIC.  Use when you need very fast, but not fine-grained timestamps.
	       CLOCK_MONOTONIC_RAW (since Linux 2.6.28; Linux-specific)
	              Similar to CLOCK_MONOTONIC, but provides access to a raw hardware-based time that is not subject to NTP adjustments or the incremental adjustments performed by adjtime(3).
	       CLOCK_BOOTTIME (since Linux 2.6.39; Linux-specific)
	              Identical  to CLOCK_MONOTONIC, except it also includes any time that the system is suspended.  This allows applications to get a suspend-aware monotonic clock without having
	              to deal with the complications of CLOCK_REALTIME, which may have discontinuities if the time is changed using settimeofday(2).
	       CLOCK_PROCESS_CPUTIME_ID (since Linux 2.6.12)
	              Per-process CPU-time clock (measures CPU time consumed by all threads in the process).
	       CLOCK_THREAD_CPUTIME_ID (since Linux 2.6.12)
	              Thread-specific CPU-time clock.
    */

    // Initializations
    TYPE A[M],B[M],C[M];

    for (int i = 0; i < M; i++){
          A[i] = val;
          B[i] = i * M;
        }

      printf("----------------------------------------\n");
      printf("Begin SAXPY.\n");
      clock_gettime( id, &ts );
      startTime = (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9 ;
      // execution
      for (int j = 0; j < M; j++) {
            C[j] =   alpha * A[j] * B[j] ;
          }
      clock_gettime( id, &ts );
      stopTime = (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9 ;
      wtime = stopTime - startTime;
	     printf("Execution Time on CPU =  %e [sec]\n", wtime);
	      printf("----------------------------------------\n");
   return(0);

  }
