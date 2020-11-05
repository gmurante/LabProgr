/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* The code shows how to use a linked list to create a matrix.         */
/* This technique is widely adopted for sparse matrix.                 */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall matrix_linked_list.c -o matrix_linked_list              */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./matrix_linked_list                                              */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Number of nodes N^2 */
/* Matrix N X N        */
#define N  3

/* Node definition */
typedef struct List_node
{
  int key;
  int i,j;
  struct List_node *next;
} List_node;

/* Head of the list */
typedef struct List
{
  List_node *head;
} List;

/* Function to create the head of the list */
List * create_list()
{
  List *list = NULL;
  if (!(list = (List *)malloc(sizeof(List))))
    {
      printf("\n\t Cannot allocate the head of the list ... aborting ... \n\n");
      exit(EXIT_FAILURE);
    }

  /* paranoid setting */
  list->head = NULL;

  return list;
}

/* Function to make a single node */
List_node * make_node(const int data,
		      const int row,
		      const int col)
{
  List_node *node = NULL;
  if (!(node = (List_node *)malloc(sizeof(List_node))))
    {
      printf("\n\t Cannot allocate node ... aborting .... \n\n");
      exit(EXIT_FAILURE);
    }

  node->key  = data;
  node->i    = row;
  node->j    = col;
  node->next = NULL;

  return node;
}

/* Function to free memory associated with a linked list */
void delete_list(List *list) 
{
  List_node *node = list->head, *tmp=NULL;
  while (node) 
    {
      tmp = node->next;
      free(node);
      node = tmp;
    }
  free(list);
}

/* Function to print the matrix */
void print_list(List *list)
{
  List_node *p = list->head;
  printf("\n\t The linked list consists of: ");
  while (p)
    {
      printf("\t M[%d,%d] = %d", p->i, p->j, p->key);
      p = p->next;
    }
  printf("\n\n");
}

int main()
{
  /* create the head of the list */
  List *list = create_list();

  /* make nodes */
  List_node *prev_node=NULL;
  for (int i=0 ; i<N ; i++)
    {
      for (int j=0 ; j<N ; j++)
	{
	  /* M[i,j] = (i + j); */	
	  List_node *current_node = make_node((i + j), i, j);

	  if ((i == 0) && (j == 0)) /* do it only at the first iteration */
	    {
	      /* set the head of the list */
	      list->head = current_node;
	      /* save the current node for the next iteration */
	      prev_node = current_node;
	    }
	  else
	    {
	      /* link the previous node with the current */
	      prev_node->next = current_node;
	      /* the current node becomes the previous node */
	      prev_node = current_node;
	    }
	} /* loop over cols */
    } /* loop over rows */

  /* print matrix */
  print_list(list);

  /* free memory */
  delete_list(list);

  return 0;
}
