/********************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                         */
/********************************************************************************/
/* A point to point program where P0 sends 10 to P1, then P1 receives           */
/* 10, sums 10, and sends back to P0.                                           */
/* (the program works only with -np 2)                                          */
/*                                                                              */
/* Compile the code using the command:                                          */
/* $ mpicc -Wall mpi_point2point_comunication.c -o mpi_point2point_comunication */
/*                                                                              */
/* Run the program using the command:                                           */
/* $ mpirun -np 2 ./mpi_point2point_comunication                                */
/*                                                                              */
/* Author: David Goz - david.goz@inaf.it                                        */
/********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MasterTask   0
#define ReceiverTask 1
#define WORLD        MPI_COMM_WORLD

int ThisTask, NTasks, error;

void check_num_tasks(void)
{
  if ((NTasks <2) & (ThisTask==MasterTask))
    {
      printf("\n\t Start the program with at least 2 processes\n\n");
      fflush(stdout);
      MPI_Abort(WORLD, error);
      exit(EXIT_FAILURE);
    }

  if ((NTasks > 2) && (ThisTask==MasterTask))
    {
      printf("\n\t This program requires only 2 tasks; the other will be ignored\n\n");
      fflush(stdout);
    }

  return;
}

int main(void)
{
  MPI_Status status;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_size(WORLD, &NTasks);
  MPI_Comm_rank(WORLD, &ThisTask);

  check_num_tasks();
  
  int N0;
  
  if (ThisTask==MasterTask)
    {
      N0 = 10;
      MPI_Send(&N0, 1, MPI_INT, ReceiverTask, 0, WORLD);
      MPI_Recv(&N0, 1, MPI_INT, ReceiverTask, 1, WORLD, &status);
      printf("\n\t Integer N=%d received from task %d [message from task %d]\n",
	     N0, ReceiverTask, ThisTask);
    }

  if (ThisTask==ReceiverTask)
    {
      MPI_Recv(&N0, 1, MPI_INT, MasterTask, 0, WORLD, &status);
      printf("\n\t Integer N=%d received from task %d [message from task %d]\n",
	     N0, MasterTask, ThisTask);
      N0 += 10;
      MPI_Send(&N0, 1, MPI_INT, MasterTask, 1, WORLD);
    }
  
  MPI_Finalize();

  printf("\n");
  
  return 0;
}
