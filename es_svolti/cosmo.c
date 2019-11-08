#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L       *pf
#define OmegaDM *(pf+1)
#define OmegaB  *(pf+2)
#define h       *(pf+3)
#define N       *(pf+4)
#define MDM     *(pf+5)
#define MB      *(pf+6)

#define rhocrit  1.e-26
#define Msun     2.e30
#define Mpc      3.08e22


int main(int argc, char* argv[])
{
double *pf;
int i;

void masse(double* pf);

if(argc!=6)
	{
		printf("This programs need 5 arguments, namely L, OmegaDM, OmegaB, h, N\n");
		exit(-1);
	}

pf=(double*) malloc(7*sizeof(double));

for(i=1; i<=5; i++)
	*(pf+i-1) = atof(argv[i]);

masse(pf);

printf("%e %e\n", MDM, MB);

free(pf);
}

void masse(double*pf)
{
double Mtot;

Mtot=pow(L*Mpc/h,3)*rhocrit*(OmegaDM+OmegaB);

MDM = Mtot*(OmegaDM/(OmegaDM+OmegaB))/N; MDM /=  Msun;
MB  = Mtot*(OmegaB/(OmegaDM+OmegaB))/N;  MB  /=  Msun;

return;

}
