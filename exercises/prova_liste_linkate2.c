#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

struct mylist
{
double r, phi, costheta;
struct mylist *NextElement;
};

int main(int argc, char *argv[])
{
int N_points_to_generate;
char mode[2];
struct mylist *FirstElement;

 void crea_distribuzione_c(char *mode, int N_Points_to_generate, struct mylist *FirstElement);
 void stampa_distribuzione_c(struct mylist *FirstElement);
 void crea_distribuzione_s(char *mode, int N_Points_to_generate, struct mylist *FirstElement);
 void stampa_distribuzione_s(struct mylist *FirstElement);
 float frand(void);
 void dealloc(struct mylist *);
 void dealloc2(struct mylist *);

 void (*crea)(char*, int, struct mylist *), (*stampa)(struct mylist *);

 
 
 if(argc!=3)
   {
     printf("Error, use: distrib [c|s] N'\n");
     printf(" N number of points for sampling\n");
     printf(" c produces a circle, s produces a sphere\n");
     exit(-1);
   }
 
 FirstElement= (struct mylist *) malloc(sizeof(struct mylist));
 FirstElement->NextElement=NULL;
 
 strcpy(mode,argv[1]);
 N_points_to_generate = atoi(argv[2]);
 printf("Generating %d points in mode %s\n",N_points_to_generate, mode);

 if(!strcmp(mode,"c"))
   {
     crea   = *crea_distribuzione_c;
     stampa = *stampa_distribuzione_c; 
   }
 else if(!strcmp(mode,"s"))
   {
     crea   = *crea_distribuzione_s;
     stampa = *stampa_distribuzione_s; 
   }
 else
   {
     printf("Error, mode must be either c or s!\n");
     exit(-2);
   }

 
 printf("Creating list...\n");
 crea(mode, N_points_to_generate, FirstElement);
 printf("Saving data...\n");
 stampa(FirstElement);
 printf("Data in file distribuzione.txt\n");

 dealloc(FirstElement); /* fatela ricorsiva */
 printf("Memory successfully deallocated\n");
}

float frand()
{
  return rand()/(RAND_MAX-1.);
}

void crea_distribuzione_c(char *mode, int N_Points_to_generate, struct mylist *FirstElement)
{
  int i;
  struct mylist *CurrentElement;
  CurrentElement = FirstElement;

  for(i=0; i<N_Points_to_generate; i++)
    {
      CurrentElement->phi = 2*M_PI*frand();
      CurrentElement->r = sqrt(frand());
      CurrentElement->costheta = -2;
      if(i<N_Points_to_generate-1)
	{
	  CurrentElement->NextElement = (struct mylist *) malloc(sizeof(struct mylist));
	  CurrentElement = CurrentElement-> NextElement;
	  CurrentElement->NextElement = NULL;
	}
    }
}

void crea_distribuzione_s(char *mode, int N_Points_to_generate, struct mylist *FirstElement)
{
  int i;
  struct mylist *CurrentElement;
  CurrentElement = FirstElement;

  for(i=0; i<N_Points_to_generate; i++)
    {
      CurrentElement->phi = 2*M_PI*frand();
      CurrentElement->r = pow(frand(),1./3.);
      CurrentElement->costheta = 2.*frand()-1;
      if(i<N_Points_to_generate-1)
	{
	  CurrentElement->NextElement = (struct mylist *) malloc(sizeof(struct mylist));
	  CurrentElement = CurrentElement-> NextElement;
	  CurrentElement->NextElement = NULL;
	}
    }
}

void stampa_distribuzione_c(struct mylist *FirstElement)
{
  FILE *f;
  double x,y;
  struct mylist *CurrentElement;

  CurrentElement = FirstElement;
  f=fopen("distribuzione_c.txt","w");

  while(CurrentElement!=NULL)
    {
      x=CurrentElement->r*cos(CurrentElement->phi);
      y=CurrentElement->r*sin(CurrentElement->phi);
      fprintf(f,"%f %f\n",x,y);
      CurrentElement = CurrentElement->NextElement;
    }

  fclose(f);

}

void stampa_distribuzione_s(struct mylist *FirstElement)
{
  FILE *f;
  double x,y,z, sintheta;
  struct mylist *CurrentElement;

  CurrentElement = FirstElement;
  f=fopen("distribuzione_s.txt","w");

  while(CurrentElement!=NULL)
    {
      sintheta = sqrt(1.-CurrentElement->costheta*CurrentElement->costheta);
      x=CurrentElement->r*cos(CurrentElement->phi)*sintheta;
      y=CurrentElement->r*sin(CurrentElement->phi)*sintheta;
      z=CurrentElement->r*CurrentElement->costheta;
      fprintf(f,"%f %f %f\n",x,y,z);
      CurrentElement = CurrentElement->NextElement;
    }

  fclose(f);

}

void dealloc2(struct mylist *FirstElement)
{
  struct mylist *CurrentElement, *Wrong;
  CurrentElement=FirstElement;
  while(CurrentElement->NextElement!=NULL)
    {
      Wrong = CurrentElement;
      CurrentElement = CurrentElement->NextElement;
      free(Wrong);
    }
}

 void dealloc(struct mylist *CurrentElement)
 {
   if(CurrentElement->NextElement == NULL)
     {
     free(CurrentElement);
     return;
     }
   else
     dealloc(CurrentElement->NextElement);   
	  
 }
