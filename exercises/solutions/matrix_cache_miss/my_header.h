#if !defined(MY_HEADER)
#define MY_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 512
typedef double MyFloat;

MyFloat wall_time(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC,&ts);
  const MyFloat ret = (MyFloat) (ts.tv_sec) + (MyFloat) ts.tv_nsec * 1.0e-9;
  
  return ret;
}

#endif /* MY_HEADER */
