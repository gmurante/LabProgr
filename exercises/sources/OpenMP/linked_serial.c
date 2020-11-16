/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Program to compute the Fibonacci numbers using a linked list.                 */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra linked_serial.c -o linked_serial                          */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./linked_serial                                                        */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* History: Originally written by Tim Mattson, September 2011.                   */
/*          Modified for the purpose of the course by David Goz.                 */
/*                                                                               */
/* Assigned tasks:                                                               */
/*                  - OpenMP parallelization:                                    */
/*                    - parallelize the code targeting the while loop that       */
/*                      processes the linked list.                               */
/*                      DO NOT use omp task to solve the problem.                */
/*********************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define N    5   /* number of elements in the linked list */
#define FS   38  /* input payload for the linked list     */

typedef struct node
{
  int data;
  int fibdata;
  struct node* next;
} node;

/* recursive function */
int fib(const int n)
{
  if (n < 2)
    return (n);
  else
    {
      int x = fib(n - 1);
      int y = fib(n - 2);

      return (x + y);
    }
}

void processwork(node* p) 
{
  p->fibdata = fib(p->data);
}

node * init_list(node *p)
{
  /* head of the linked list */
  node *head = NULL;
  if (!(head = (node *)malloc(sizeof(node))))
    {
      printf("\n\t Cannot allocate head of the linked list ... aborting ... \n\n");
      exit(EXIT_FAILURE);
    }

  /* set p to head */
  p = head;
  p->data = FS;
  
  /* create the linked list */
  node *tmp = NULL;
  for (int i=0 ; i<N ; i++)
    {
      if ((tmp = (node *)malloc(sizeof(node))) == NULL)
	{
	  printf("\n\t Cannot allocate element of the linked list ... aborting ... \n\n");
	  exit(EXIT_FAILURE);
	}

      /* link p to the next element */
      p->next = tmp;
      /* move p to the next element */
      p = tmp;
      /* set the payload */
      p->data = (FS + i + 1);
    } /* loop over the linked list */

  /* end the linked list */
  p->next = NULL;

  /* return the head of the linked list */
  return head;
}

int main()
{
  printf("\n\t Create the linked list");
  /* create the linked list */
  node *head = NULL, *p = NULL;
  head = init_list(p);

  printf("\n\t Each node will compute %d Fibonacci numbers beginning with %d\n\n",
	 N, FS);
  /* process the linked list */
  p = head;
  while (p)
    {
      processwork(p);
      p = p->next;
    }

  /* print the result and free memory */
  p = head;
  while (p)
    {
      printf("\t %d : %d\n",p->data, p->fibdata);
      node *tmp = p->next;
      free(p);
      p = tmp;
    }  
  free (p);

  return 0;
}
