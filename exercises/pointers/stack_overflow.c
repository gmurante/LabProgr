/***********************************************************************/
/* Course: Advanced Programming for Physics                            */
/***********************************************************************/
/* The program statically allocates an array of integer increasing     */
/* the size in order to try to figure out which is the maximum size    */
/* (stack overflow)                                                    */
/*                                                                     */
/* Compile the code using the command:                                 */
/* $ gcc -Wall -Wextra stack_overflow.c -o stack_overflow              */
/*                                                                     */
/* Run the program using the command:                                  */
/* $ ./stack_overflow                                                  */
/*                                                                     */
/* Then, using the command 'ulimit' get and set user limits and check  */
/* the stack size:                                                     */
/* $ ulimit -a | grep -i 'stack size'                                  */
/*                                                                     */
/* Finally, give the following command and then run the program again: */
/* $ ulimit -s unlimited                                               */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef double MyData;

#define _FROM_BYTES_TO_KBYTES_  (1.0 / 1024.)
#define _FROM_BYTES_TO_MBYTES_  (_FROM_BYTES_TO_KBYTES_ / 1024.)
#define _MAX_POW_               (35)

int main()
{
  size_t pow = 15;
  
  while (pow < _MAX_POW_)
    {
      /* (1 << pow) is the number of MyData allocated */
      const size_t N = (1 << pow);
      
      /* size of the array in bytes */
      const long int size = (sizeof(MyData) * N);

      printf("\n\t Allocating %lg Kbytes [%lg Mbytes]\n",
	     (size * _FROM_BYTES_TO_KBYTES_),
	     (size * _FROM_BYTES_TO_MBYTES_));

      /* pause */
      sleep(1);

      /* static array allocation */
      MyData array[N];

      printf("\t Allocation done \n");

      /* array initialization */
      memset(array, 0, size);

      /* Increase the size of the array by a factor of 2 */
      pow++;
    }
  
  return EXIT_SUCCESS;
}
