#include "myheader.h"

uint mystatic( ) {
  static int increase = 0;
  printf("I am in mystatic\n");
  printf("My Value is %d\n", increase++);
  return (increase);
}
