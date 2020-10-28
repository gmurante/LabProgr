#include "stdio.h"
#include "stdlib.h"

int main()
{
  double a=0.,b,c; /* coefficienti*/
  double x1, x2; /* soluzioni*/
  double det; /* determinante */
  
  void MyInput(double *, double *, double *);
  double Solution(double, double, double, double*, double*);

  /* &a = F4E2
     a --> 0 */

  MyInput(&a, &b, &a);

  det=Solution(a,b,c, &x1, &x2);


  if(x1!=999.999)
    {
      printf("\n Le soluzioni di %lf x^2 + %lf x + %lf =0 sono:\n",
	     a,b,c);
      printf(" x1=%lf, x2=%lf\n", x1, x2);
    }

}

void MyInput(double *A, double *B, double *C)
{

  /* &A = A010 
     A --> F4E2 */
  
  printf(" a= "); scanf("%lf", A); printf("\n");
  printf(" b= "); scanf("%lf", B); printf("\n");
  printf(" c= "); scanf("%lf", C); printf("\n");

}


double Solution(double a, double b, double c, double* x1, double *x2)
{
  double det;
  det= b*b+4*a*c;

  if (det<0.) {
    printf("Attenzione: equazione impossibile!\n");
    return -999.999;
  }
  *x1 = (-b + det)/2./a;
  *x2 = (-b - det)/2./a;

  return det;
}
