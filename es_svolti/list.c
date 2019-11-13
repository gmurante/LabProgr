/*********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)              */
/*********************************************************************/
/* The program creates a linked list filling the elements with       */
/* pseudo random numbers between [0, 1). Finally it gets the min and */
/* max values of the linked list.                                    */
/*                                                                   */
/* Compile the code using the command:                               */
/* $ gcc -Wall list.c -o list                                        */
/*                                                                   */
/* Run the program using the command:                                */
/* $ ./list                                                          */
/*                                                                   */
/* Author: David Goz - david.goz@inaf.it                             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _N_   5   /* number of elements of the list */
#define _A_   0.0
#define _B_   1.0 /* get random numbers in [a,b) */

/* macros for max and min values */
#define MAX(A, B)   ((A) > (B) ? (A) : (B))
#define MIN(A, B)   ((A) < (B) ? (A) : (B))

/* struct list */
typedef struct list_element
{
  float value;
  struct list_element *pun;
} element;

/* initialize the seed */
void set_seed(void);

/* get random number in [a, b) */
float random_number(const float, const float);

/* create list */
element * CreateList(void);

/* print the list */
void print_list(element *);

/* get max e min */
void list_max_min(element *);

int main()
{
  /* create the list */
  element *List = CreateList();
  
  /* print the list */
  print_list(List);

  /* get min and max within the list */
  list_max_min(List);
  
  return 0;
}

element * CreateList(void)
{
  if (_N_ <= 1)
    {
      printf("\n\t The number of elements is less or equal one \n");
      exit(EXIT_FAILURE);
    }

  /* allocate space for the first element of the list */
  element *PointList = NULL;
  if ((PointList = (element *)malloc(sizeof(element))) == NULL)
    {
      printf("\n\t PointList allocation failure ... aborting...\n");
      exit(EXIT_FAILURE);
    }

  /* seed initialization */
  set_seed();
  
  /* fill with random number the first element */
  PointList->value = random_number(_A_, _B_);

  /* create the other elements of the list */
  element *PointListTmp = PointList;
  for (int i=1 ; i<=_N_ ; i++)
    {
      if ((PointListTmp->pun = (element *)malloc(sizeof(element))) == NULL)
	{
	  printf("\n\t PointList allocation failure ... aborting...\n");
	  exit(EXIT_FAILURE);;
	}

      PointListTmp = PointListTmp->pun;

      /* fill wth random number */
      PointListTmp->value = random_number(_A_, _B_);
    }

  /* set the end of the list */
  PointListTmp->pun = NULL;
  
  return PointList;
}

void print_list(element *List)
{
  printf("\n");

  int i=0;
  do
    {
      printf("\t List[%d] = %f", i++, List->value);
      List = List->pun;
    } while (List->pun);

  printf("\n");
  
  return;
}

void list_max_min(element *list)
{
  float min = _B_;
  float max = _A_;

  do
    {
      min = MIN(min, list->value);
      max = MAX(max, list->value);

      list = list->pun;
    } while (list->pun);

  printf("\n\t MIN: %f, MAX: %f\n\n", min, max);
  
  return;
}

float random_number(const float a,
		    const float b)
{
  float rendfrac = rand() / (RAND_MAX + 1.0);

  return (rendfrac * (b - a) + a);
}

void set_seed()
{
  srand(time(NULL));
  
  return;
}
