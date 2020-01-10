/***********************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                */
/***********************************************************************/
/* The "Hello World" MPI program                                       */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ mpicc -Wall mpi_hello.c -o mpi_hello                              */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ mpirun --oversubscribe -np <# tasks> ./mpi_hello                  */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <mpi.h>

int main(void)
{
  int ThisTask, NTasks;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &NTasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &ThisTask);

  printf("\n\t Hello from task %d of %d tasks",
	 ThisTask, NTasks);

  MPI_Finalize();

  printf("\n\n");

  return 0;
}

