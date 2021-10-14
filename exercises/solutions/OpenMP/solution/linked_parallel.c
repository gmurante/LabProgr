/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Program to compute the Fibonacci numbers using a linked list.                 */
/*                                                                               */
/* Compile the code:                                                             */
/* $ gcc -Wall -Wextra -fopenmp linked_parallel.c -o linked_parallel             */
/*                                                                               */
/* Run the code:                                                                 */
/* $ time ./linked_parallel <number of OpenMP threads>                           */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*                                                                               */
/* History: Originally written by Tim Mattson, September 2011.                   */
/*          Modified for the purpose of the course by David Goz.                 */
/*                                                                               */
/* OpenMP parallelization:                                                       */
/*                    - since omp task cannot be used, first of all, it is       */
/*                      necessary to figure out how many nodes there are. The    */
/*                      while loop at line 124 accomplishes this task.           */
/*                      After that, an array of pointers to each node of the     */
/*                      linked list is created (line 140), so that different omp */
/*                      threads can carry on the calculation of the Fibonacci    */
/*                      number assigned to each node.                            */
/*                      It is worth to be noticed that the previous stages are   */
/*                      not required if omp tasks are used, since omp tasks are  */
/*                      applied to while loop straightforwardly.                 */
/*                                                                               */
/*                     - optional:                                               */
/*                                - try different schedule policies applied to   */
/*                                  the parallel for loop at line 158.           */
/*                                  Any difference in terms of time to solution? */
/*                                  Why?                                         */
/*********************************************************************************/

#include "my_omp_header.h"

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

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("\n\t USAGE: <executble> <number of OpenMP threads> \n\n");
      return -1;
    }

  const unsigned int num_threads = atoi(argv[1]);
  
  printf("\n\t Create the linked list");
  /* create the linked list */
  node *head = NULL, *p = NULL;
  head = init_list(p);

  /* count the number of nodes */
  unsigned int nnodes = 0;
  p = head;
  while(p)
    {
      nnodes++;
      p = p->next;
    }

  /* allocate buffer to store each node */
  node **pp = NULL;
  if (!(pp = (node **)malloc(nnodes * sizeof(node *))))
    {
      printf("\n\t Cannot allocate buffer to store nodes ... aborting ... \n\n");
      exit(EXIT_FAILURE);
    }
  
  /* fill pp */
  p = head;
  for (unsigned int i=0 ; i<nnodes ; i++)
    {
      pp[i] = p;
      p = p->next;
    }
  
  printf("\n\t Each node will compute %d Fibonacci numbers beginning with %d\n\n",
	 N, FS);

  /* process the linked list */
#pragma omp parallel default(none) shared(pp, nnodes) num_threads(num_threads)
  {
#  pragma omp single nowait
    {
      printf("\t Active OpenMP threads: %d \n\n",
	      omp_get_num_threads());
    } /* omp single nowait */
    
#  pragma omp for nowait
    for (unsigned int i=0 ; i<nnodes ; i++)
      processwork(pp[i]);
  } /* omp parallel region */
  
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
  free(pp);
  
  return 0;
}
