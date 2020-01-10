/*********************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                          */
/*********************************************************************************/
/* Each process at time T0 sends its own ID to the next process and receives an  */
/* ID from the previous process in the ring. At time T all processes send into   */
/* the ring the value received at time T-1 and receive from the ring by the      */
/* previous process. At each step the received number is added to a local        */
/* quantity (initialized with the process ID). After n-1 comunications all tasks */
/* have the same local quantity equal to the sum of all the IDs involved.        */
/*                                                                               */
/* Compile the code using the command:                                           */
/* $ mpicc -Wall mpi_ring.c -o mpi_ring                                          */
/*                                                                               */
/* Run the program using the command:                                            */
/* $ mpirun --oversubscribe -np <# tasks> ./mpi_ring                             */
/*                                                                               */
/* Author: David Goz - david.goz@inaf.it                                         */
/*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MasterTask   0
#define WORLD        MPI_COMM_WORLD

int ThisTask, NTasks, error;

#define RECEIVER ((ThisTask == (NTasks - 1)) ? MasterTask : (ThisTask + 1))
#define SENDER   ((ThisTask == MasterTask) ? (NTasks - 1) : (ThisTask - 1))

void check_num_tasks(void)
{
  if ((NTasks < 2) & (ThisTask==MasterTask))
    {
      printf("\n\t Run the program with at least 2 processes\n\n");
      fflush(stdout);
      MPI_Abort(WORLD, error);
      exit(EXIT_FAILURE);
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

  const int tag=0;
  int i;
  int ID = ThisTask;
  int sum = ThisTask;

  for (i=0 ; i<NTasks-1 ; i++)
    {
      MPI_Send(&ID, 1, MPI_INT, RECEIVER, tag, WORLD);

      MPI_Recv(&ID, 1, MPI_INT, SENDER, tag, WORLD, &status);

      sum += ID;
    }

  if (ThisTask==MasterTask)
    {
      printf("\n\t Number of tasks %d", NTasks);
      printf("\n\t Sum %d from task %d", sum, ThisTask);
      printf("\n\t The right answer is %d\n\n", NTasks*(NTasks-1)/2);
      fflush(stdout);
    }
  
  MPI_Finalize();

  return 0;
}
