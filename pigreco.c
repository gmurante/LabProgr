/*
** Luca Belpietro Novembre 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



struct point
{
	float x;
	float y;
};



struct point randompoint(struct point * arrayp, float l) 
{	
	arrayp->x=-(l/2)+l*rand()/(1.0+RAND_MAX);
	arrayp->y=-(l/2)+l*rand()/(1.0+RAND_MAX);
}

int main ()
{
	int npoints;
	struct point *p, *points;
	float lato, raggio, A_quadrato, A_cerchio, pigreco;
	int countc=0;
	printf("Inserire il numero di punti:\t"); scanf("%d", &npoints); printf("\n");
	points = (struct point *) malloc(npoints*sizeof(struct point));
	printf("Inserire il lato del quadrato:\t"); scanf("%f", &lato); printf("\n");
	raggio=lato/2;
	srand(clock());


	for (p=points; p<points+npoints; p++) randompoint(p, lato);
	FILE *fquadrato, *fcerchio;
	fquadrato=fopen("puntiq.txt", "w");
	fcerchio=fopen("puntic.txt", "w");


	for (p=points; p<points+npoints; p++){
		if ((pow((p->x),2)+pow((p->y),2))<=pow(raggio,2)){
			 ++countc;
			fprintf(fcerchio, "%f\t%f\n", (p->x), (p->y));
		}
		else fprintf(fquadrato, "%f\t%f\n", (p->x), (p->y));;
	}
	A_quadrato=pow(lato,2);
	A_cerchio=countc*A_quadrato/npoints;
	pigreco=A_cerchio/pow(raggio,2);
	printf("pigreco= %7.6f\n", pigreco);
	printf("Valore di riferimento: %7.6f\n", M_PI);
	free(points);
	fclose(fcerchio);
	fclose(fquadrato);
}
