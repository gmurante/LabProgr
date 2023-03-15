#include <stdio.h>
#include <stdlib.h>

typedef double MyData;
#define N (1 << 8)
#define FROM_BYTES_TO_KBYTES (1.0 / 1024.)

int main()
{
  /* stack allocation */
  MyData matrix[N][N];

  printf("\n\t Datatype size: %lu [Bytes]", sizeof(MyData));
  printf("\n\t Matrix number of elements: %d [%d x %d]", N * N, N, N);
  printf("\n\t Matrix size: %g [KBytes]\n",
	 (sizeof(matrix) * FROM_BYTES_TO_KBYTES));

  for (size_t i=0 ; i<N ; i++)
    for (size_t j=0 ; j<N ; j++)
      matrix[i][j] = (MyData)(i - j);

  /* ... do something ... */

  return EXIT_SUCCESS;
}
