/*********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)              */
/*********************************************************************/
/* The program creates two linked lists with different number of     */
/* elements, filling the latest with pseudo random numbers between   */
/* [0, 1). Finally it sum up the two lists creating a new list (the  */
/* length of the new list is the shortest between the two)           */
/*                                                                   */
/* Compile the code using the command:                               */
/* $ gcc -Wall list_sum.c -o list_sum                                */
/*                                                                   */
/* Run the program using the command:                                */
/* $ ./list_sum                                                      */
/*                                                                   */
/* Author: David Goz - david.goz@inaf.it                             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _N_   3   /* number of elements of the first list  */
#define _M_   5   /* number of elements of the second list */
#define _A_   0.0
#define _B_   1.0 /* get random numbers in [a,b) */

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
element * CreateList(const int, const int);

/* print the list */
void print_list(element *, const char *);

/* create the sum of the lists */
element *CreateSumList(element *, element *);


int main()
{
  /* create the fist list */
  element *ListOne = CreateList(_N_, 1);

  /* create the second list */
  element *ListTwo = CreateList(_M_, 1);
  
  /* print the lists */
  print_list(ListOne, "First List ");
  print_list(ListTwo, "Second List");

  /* create the sum of the lists */
  element *SumList = CreateSumList(ListOne, ListTwo);

  /* print the sum of the lists */
  print_list(SumList, "Sum List   ");
  
  return 0;
}

element * CreateList(const int NumElements,
		     const int flag_fill_list)
{
  if (NumElements <= 1)
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
  if (flag_fill_list)
    PointList->value = random_number(_A_, _B_);

  /* create the other elements of the list */
  element *PointListTmp = PointList;
  for (int i=1 ; i<=NumElements ; i++)
    {
      if ((PointListTmp->pun = (element *)malloc(sizeof(element))) == NULL)
	{
	  printf("\n\t PointList allocation failure ... aborting...\n");
	  exit(EXIT_FAILURE);;
	}

      PointListTmp = PointListTmp->pun;

      /* fill wth random number */
      if (flag_fill_list)
	PointListTmp->value = random_number(_A_, _B_);
    }

  /* set the end of the list */
  PointListTmp->pun = NULL;
  
  return PointList;
}

element * CreateSumList(element *FirstList,
			element *SecondList)
{
  /* get the number of elements of the sum list */
  const int Num = ((_N_) < (_M_) ? _N_ : _M_);

  /* create the list */
  element *SumList = CreateList(Num, 0);

  /* sum up the element of the lists */
  element *SumListTmp = SumList;
  do
    {
      /* sum up the values */
      SumListTmp->value = (FirstList->value + SecondList->value);

      /* move the list pointers */
      SumListTmp = SumListTmp->pun;
      FirstList  = FirstList->pun;
      SecondList = SecondList->pun;

    } while (SumListTmp->pun);

  return SumList;
}

void print_list(element *List,
		const char *label)
{
  printf("\n %s", label);

  int i=0;
  do
    {
      printf("\t List[%d] = %f", i++, List->value);
      List = List->pun;
    } while (List->pun);

  printf("\n");
  
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
  static int t = 0;
  
  srand(time(NULL) + t++);
  
  return;
}
