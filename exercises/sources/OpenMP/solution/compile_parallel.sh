#!/bin/bash

rm -rf *~
rm -rf *.x

# Program: pi
gcc -Wall -Wextra -fopenmp pi_parallel.c -o pi_parallel.x -lm
if [ $? -ne 0 ]; then
  echo "pi_parallel compile error."
  exit
fi

# Program: Mandelbrot set
gcc -Wall -Wextra -fopenmp mandelbrot_parallel.c -o mandelbrot_parallel.x
if [ $? -ne 0 ]; then
  echo "mandelbrot_parallel compile error."
  exit
fi

# Program: Linked list
gcc -Wall -Wextra -fopenmp linked_parallel.c -o linked_parallel.x
if [ $? -ne 0 ]; then
  echo "linked_parallel compile error."
  exit
fi

# Program: Matrix multiplication
gcc -Wall -Wextra -fopenmp matmul_parallel.c -o matmul_parallel.x
if [ $? -ne 0 ]; then
  echo "matmul_parallel compile error."
  exit
fi
