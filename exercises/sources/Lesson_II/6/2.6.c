/************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                 */
/************************************************************************/
/* The binary search (taken from K&R p 58) makes two tests inside the   */
/* loop, when one would suffice (at the price of more tests outside).   */
/* Write a version with only one test inside the loop and measure the   */
/* difference in run-time.                                              */
/*                                                                      */
/* int binsearch(int x, int v[], int n)                                 */
/* {                                                                    */
/*     int low, high, mid;                                              */
/*     low=0;                                                           */
/*     high=n-1;                                                        */
/*     while (low<=high) {                                              */
/*         mid=(low+high)/2;                                            */
/*         if (x<v[mid])                                                */
/*             high=mid-1;                                              */
/*         else if (x>v[mid])                                           */
/*             low=mid+1;                                               */
/*         else                                                         */
/*             return mid;                                              */
/*             }                                                        */
/*     return -1;                                                       */
/* }                                                                    */
/*                                                                      */
/* Compile the code:                                                    */
/* $ gcc -Wall -O0 2.6.c -o 2.6.x                                       */
/*                                                                      */
/* Run the code:                                                        */
/* $ ./2.6.x                                                            */
/*                                                                      */
/* Author: David Goz - david.goz@inaf.it                                */
/************************************************************************/

#include <stdio.h>
#include <time.h>
#include <time.h>

#define MAX_ELEMENT 2007152/* if increased too much stack overflow */
#define REPEAT      300000  /* number of repetition                 */

/*  K&R binary search */
int binsearch(int x, int v[], int n)
{
  int low, mid, high;
  
  low = 0;
  high = n - 1;
  while ( low <= high )
    {
      mid = (low+high) / 2;
      if ( x < v[mid] )
	high = mid - 1;
      else if ( x > v[mid] )
	low = mid + 1;
      else
	return mid;
    }

  return -1;
}

/* Implementation of binary search using */
/* only one test inside the loop         */
int binsearchOpt(int x,
		 int v[],
		 int n)
{
  int low  = 0;
  int high = (n - 1);
  int mid  = ((low + high) >> 1);

  while ((low <= high) && (x != v[mid]))
    {
      (x < v[mid]) ? (high = (mid - 1)) : (low = (mid + 1));

      mid = ((low + high) >> 1);
    }
  
  if (x == v[mid])
    return mid;
  else
    return -1;
}

/* To get timing we search for the element -1. */
/* i.e. the element not found in test data     */
int main()
{
  int testdata[MAX_ELEMENT];
  const int element = -1; /* element to search for */

  /*  Initialize test data  */    
  for (int i=0 ; i<MAX_ELEMENT ; i++)
    testdata[i] = i;

  clock_t begin = clock();
  /* binsearch */
  for (int Repeat=0 ; Repeat<REPEAT ; Repeat++)
    {
      if (binsearch(element, testdata, MAX_ELEMENT) != -1)
	{
	  printf("\n\t Error in binsearch ... aborting...\n\n");
	  return -1;
	}
    }
  clock_t end = clock();
  
  printf("\n\t binsearch() took %g seconds \n",
	 ((double)(end - begin) / CLOCKS_PER_SEC / REPEAT));
    
  /* binsearchOpt */
  begin = clock();
  for (int Repeat=0 ; Repeat<REPEAT ; Repeat++)
    {
      if (binsearchOpt(element, testdata, MAX_ELEMENT) != -1)
      	{
	  printf("\n\t Error in binsearchOpt ... aborting...\n\n");
	  return -1;
	}
    }
  end = clock();
    
  printf("\n\t binsearchOpt() took %g seconds \n\n",
	 ((double)(end - begin) / CLOCKS_PER_SEC / REPEAT));
    
  return 0;
}
