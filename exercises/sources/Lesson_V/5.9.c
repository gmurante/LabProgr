/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* Rewrite the routines 'day_of_year' and 'month_day' (pag. 111 K&R)   */
/* with pointers instead of indexing.                                  */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 5.9.c -o 5.9.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./5.9.x                                                           */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>

/* Global bi-dimensional array containing the number of days per month    */
/* separating them in two rows tracking leap and non-leap years.          */
/* Since the array is global, its scope is the entire file, i.e.          */
/* all function can use it.                                               */
/* K&R use an array of char, a legitimate way for storing small integers. */
/* We prefer to use integer arrays for sake of simplicity.                */

#define LEAP(A) ((!((A) % 4) && ((A) % 100)) || !((A) % 400))

static int daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* original version of K&R pag.111 */
int day_of_year(int year, int month, int day)
{
  int i, leap;
	
  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];

  return day;
}

/* original version of K&R pag.111 */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
	
  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];

  *pmonth = i;
  *pday = yearday;
}

/* pointer version */
int day_of_year_pointer(const int year,
			const int month,
			      int day)
{
  /* check leap year */
  const int leap = LEAP(year);

  /* set a pointer 'p' to the right row */
  int *p = &daytab[leap][1];
  
  /* move pointer 'p' to each successive month */
  for (int i=1 ; i<month ; i++)
    day += *p++;
  
  return day;
}

/* pointer version */
void month_day_pointer(const int  year,
		             int  yearday,
		             int *pmonth,
		             int *pday)
{
  /* check leap year */
  const int leap = LEAP(year);

  /* set a pointer 'p' to the right row */
  int *p = &daytab[leap][1];

  int i;
  for (i=1 ; yearday>*p ; i++)
    yearday -= *p++;

  /* set the month value through its pointer */
  *pmonth = i;

  /* set the day through its pointer */
  *pday = yearday;
  
  return;
}

int main(void)
{
  const int year  = 2001;
  int month       = 9;
  int day         = 21;

  printf("\n\t date               : %d-%02d-%02d ", year, month, day);
  printf("\n\t day_of_year        : %d", day_of_year(year, month, day));
  printf("\n\t day_of_year_pointer: %d\n", day_of_year_pointer(year, month, day));

  /* do the opposite */
  const int yearday = day_of_year_pointer(year, month, day);
  printf("\n\t yearday          : %d", yearday);
  
  month_day(year, yearday, &month, &day);
  printf("\n\t month_day        : %d %d", month, day);
  
  month_day_pointer(year, yearday, &month, &day);
  printf("\n\t month_day_pointer: %d %d\n\n", month, day);
	
  return 0;
}
