#include <stdio.h>
#include <stdlib.h>

void hello(void);
void world(void);
void printall( void (*pf1)(void), void (*pf2)(void));

int main(int argc, char *argv[])
{
  void (*pf)(void);
  
  if(argc!=2)
    {
      printf(" Wrong number of arguments, one and only one needed.\n");
      exit(-1);	
    }

  switch(atoi(argv[1]))
    {
    case 1:
      pf=hello;
      break;
    case 2:
      pf=world;
      break;
    case 3:
      printall(hello, world);
      exit(01);
    default:
      printf(" Wrong argument, only \"1\",  \"2\", \"3\" allowed\n");
      exit(-1);      
    }

  (*pf)();
  exit(0);
}

void hello()
{
  printf("hello ");
  return;
}

void world()
{
  printf("world\n");
  return;
}

void printall(void (*pf1)(), void (*pf2)())
{
  (*pf1)();
  (*pf2)();
  return;
}
