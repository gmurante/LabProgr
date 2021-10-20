#include <stdio.h>

int incrementa (int * a);

int main() {
    int j=0;
    printf("Before %d\n", j);
    incrementa (&j);
    printf("After %d\n", j);
}

int incrementa (int * a){
   *a=*a+1;
   return(0);
}
