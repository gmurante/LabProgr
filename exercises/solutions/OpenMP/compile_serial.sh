#!/bin/bash

rm -rf *~
rm -rf *.x

# Program: pi
gcc -Wall -Wextra pi_serial.c -o pi_serial.x -lm
if [ $? -ne 0 ]; then
  echo "pi_serial compile error."
  exit
fi

# Program: Mandelbrot set
gcc -Wall -Wextra mandelbrot_serial.c -o mandelbrot_serial.x
if [ $? -ne 0 ]; then
  echo "mandelbrot_serial compile error."
  exit
fi

# Program: Linked list
gcc -Wall -Wextra linked_serial.c -o linked_serial.x
if [ $? -ne 0 ]; then
  echo "linked_serial compile error."
  exit
fi

# Program: Matrix multiplication
gcc -Wall -Wextra matmul_serial.c -o matmul_serial.x
if [ $? -ne 0 ]; then
  echo "matmul_serial compile error."
  exit
fi
