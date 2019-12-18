/* this only reads the blocks and prints out the labels */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* compile with gcc -o Read_What_Blocks.x Read_What_Blocks.c 
   if -DSWAP, overrides self-id and swaps
   if -DRSNAP[1,2] overrides self-id and uses given format
   WARNING: self-id is BASED upon the fact that the fist block is 
   HEAD. If this is not true, it will give unpredictable results. */


int rsnap2=2; /* this is obviously mandatory */
int swap=0;

struct io_header_1
{
  int      npart[6];
  double   mass[6];
  double   time;
  double   redshift;
  int      flag_sfr;
  int      flag_feedback;
  int      npartTotal[6];
  int      flag_cooling;
  int      num_files;
  double   BoxSize;
  double   Omega0;
  double   OmegaLambda;
  double   HubbleParam; 
  int flag_stellarage;
  int flag_metals;
  int NptotHW[6];
  int flag_metalcooling;
  int flag_stellarevolution;
  char fill[56];                /* fills to 256 Bytes */ 
} header1;

int     NumPart, Ngas;



double  Time, Redshift;


int main()
{
  int nfl;
  char flnm[256];

  void FindBlocks(char *, int );
  void IdentifyFormat(char *flnm);


  printf("Input file (BASE)?\n");
  scanf("%s",flnm);

  printf("N. files?\n");
  scanf("%d",&nfl);

  IdentifyFormat(flnm); 
#ifdef SWAP
  printf(" OVERRIDING SELF-IDENTIFICATION: ENDIANISM WILL BE SWAPPED\N");
  swap=1;
#endif
#ifdef RSNAP1
  printf(" OVERRIDING SELF-IDENTIFICATION: SNAPSHOT-1 FORMAT WILL BE USED\N");
  rsnap2=1;
#endif
#ifdef RSNAP2
  printf(" OVERRIDING SELF-IDENTIFICATION: SNAPSHOT-2 FORMAT WILL BE USED\N");
  rsnap1=1;
#endif
  
  FindBlocks(flnm,nfl);



  printf(" Header characteristics:\n");
  printf(" npart [1...6] : %d %d %d %d %d %d\n",header1.npart[0],header1.npart[1],
	 header1.npart[2],header1.npart[3],header1.npart[4],header1.npart[5]);
  printf(" mass [1...6] : %lf %lf %lf %lf %lf %lf\n",header1.mass[0],
	 header1.mass[1],header1.mass[2],header1.mass[3],
	 header1.mass[4],header1.mass[5]);
  printf(" TIME: %lf\n",header1.time);
  printf(" Redshift: %lf\n",header1.redshift);
  printf(" Flags sfr, feedback, cooling: %d %d %d\n",header1.flag_sfr,
	 header1.flag_feedback, header1.flag_cooling);
  printf(" npartTotal [1...6]: %d %d %d %d %d %d\n",header1.npartTotal[0],
	 header1.npartTotal[1],header1.npartTotal[2],header1.npartTotal[3],
	 header1.npartTotal[4],header1.npartTotal[5]);
  printf(" NumFiles: %d\n",header1.num_files);
  printf(" BOXSIZE: %lf\n",header1.BoxSize);
  printf(" OMEGA0: %lf\n",header1.Omega0);
  printf(" OMEGA_LAMBDA: %lf\n",header1.OmegaLambda);
  printf(" HUBBLE PARAM.: %lf\n",header1.HubbleParam);


  exit(swap);

}

void IdentifyFormat(char *name)
{
    char buf[256];
    char LABEL[5];
    FILE *fd;
    int dummy2;
#define SKIPI fread(&dummy2,sizeof(dummy2),1,fd);
    void swap_Nbyte(char *, int ,int );

    sprintf(buf,"%s",name);
    if(!(fd=fopen(buf,"r")))
    {
	sprintf(buf,"%s.%d",name,0);
	if(!(fd=fopen(buf,"r")))	  
	{
	    printf("can`t open file %s\n",buf);
	    exit(0);
	}
    }

    printf("<file: %s>\n",buf);
 

    SKIPI;
    if(dummy2<0 || dummy2>=257) {
	printf(" MUST SWAP ENDIANISM\n");
	swap=1;
	swap_Nbyte((char*)&dummy2,1,4);
    }
    if(dummy2==8) {
	printf(" snapshot-2 format.\n");
	rsnap2=2;
    } else {
	printf(" snapshot-1 format\n");
	rsnap2=1;
    }

    fclose(fd);

}


/*---------------------- Routine to swap ENDIAN -------------------------------*/
/*-------- char *data:    Pointer to the data ---------------------------------*/
/*-------- int n:         Number of elements to swap --------------------------*/
/*-------- int m:         Size of single element to swap ----------------------*/
/*--------                int,float = 4 ---------------------------------------*/
/*--------                double    = 8 ---------------------------------------*/
/*-----------------------------------------------------------------------------*/
void swap_Nbyte(char *data,int n,int m)
{
  int i,j;
  char old_data[16];

  if(swap==1) {
      for(j=0;j<n;j++)
        {
          memcpy(&old_data[0],&data[j*m],m);
          for(i=0;i<m;i++)
            {
              data[j*m+i]=old_data[m-i-1];
            }
        }
  }

}





void FindBlocks(char *name, int files)
{
  FILE  *fd;
  char   buf[200];
  int    i,j,k,dummy,ntot_withmasses;


#define SKIP fread(&dummy, sizeof(dummy), 1, fd);

  void BlockHead(FILE*);
  

  for(i=0; i<files; i++)
    {


      sprintf(buf,"%s",name);
      if(!(fd=fopen(buf,"r")))
	{
	sprintf(buf,"%s.%d",name,i);
	if(!(fd=fopen(buf,"r")))	  
	  {
	    printf("can`t open file %s\n",buf);
	    exit(0);
	  }
	}

      printf("<file: %s>\n",buf);

      if(rsnap2==2) BlockHead(fd);
      fread(&dummy, sizeof(dummy), 1, fd);
      fread(&header1, sizeof(header1), 1, fd);
      fread(&dummy, sizeof(dummy), 1, fd);
      if(swap==1) {
	  swap_Nbyte((char*)header1.npart,6,4);
	  swap_Nbyte((char*)header1.npartTotal,6,4);
	  swap_Nbyte((char*)header1.mass,6,8);
	  swap_Nbyte((char*)&header1.time,1,8);
	  swap_Nbyte((char*)&header1.redshift,1,8);
	  swap_Nbyte((char*)&header1.flag_sfr,1,4);
	  swap_Nbyte((char*)&header1.flag_cooling,1,4);
	  swap_Nbyte((char*)&header1.flag_feedback,1,4);
	  swap_Nbyte((char*)&header1.flag_stellarage,1,4);
	  swap_Nbyte((char*)&header1.flag_metals,1,4);
	  swap_Nbyte((char*)&header1.num_files,1,4);
	  swap_Nbyte((char*)&header1.BoxSize,1,8);
	  swap_Nbyte((char*)&header1.Omega0,1,8);
	  swap_Nbyte((char*)&header1.OmegaLambda,1,8);
	  swap_Nbyte((char*)&header1.HubbleParam,1,8);
	  swap_Nbyte((char*)header1.NptotHW,6,4);
	  swap_Nbyte((char*)&header1.flag_metalcooling,1,4);
	  swap_Nbyte((char*)&header1.flag_stellarevolution,1,4);
      }
      


      if(files==1)
	{
	  for(k=0, NumPart=0, ntot_withmasses=0; k<6; k++)
	    NumPart+= header1.npart[k];
	  Ngas= header1.npart[0];
	}
      else
	{
	  for(k=0, NumPart=0, ntot_withmasses=0; k<6; k++)
	    NumPart+= header1.npartTotal[k];
	  Ngas= header1.npartTotal[0];
	}

      for(k=0, ntot_withmasses=0; k<6; k++)
	{
	  if(header1.mass[k]==0)
	    ntot_withmasses+= header1.npart[k];
	}
	printf("N: %d\n",ntot_withmasses);

          for(j = 0; j < 6; j++)
            printf("npart[%d]= %d/%d\n", j, header1.npart[j],
                    header1.npartTotal[j]);


	  j=0;	  
	  do {
	      j++;
	      if(rsnap2==2) BlockHead(fd);
	      SKIP;
	      if(rsnap2==1)
		  printf("Block %d length: %d     int: %d   float: %d   double: %d\n",
			 j,dummy,
			 (dummy)/sizeof(int), (dummy)/sizeof(float),
			 (dummy)/sizeof(double));
	      

	if(swap==1)
	    swap_Nbyte((char*)&dummy,1,4);
	fseek(fd, dummy, SEEK_CUR); 
	SKIP;
      }while(!feof(fd));
      

      fclose(fd);
    }




}



void BlockHead(FILE *fd)
{
char LABEL[5];
int dummy2;
 
#define SKIP2 fread(&dummy2,sizeof(dummy2),1,fd);

SKIP2;
printf("dummy: %d\n",dummy2);
fread(LABEL,4,1,fd);
LABEL[4]='\0';
SKIP2;
 if(feof(fd)) return; 
 if(swap==1)
     swap_Nbyte((char*)&dummy2,1,4);
printf("%s length: %d     int: %d   float: %d   double: %d\n",LABEL,dummy2,
       (dummy2-8)/sizeof(int), (dummy2-8)/sizeof(float),
       (dummy2-8)/sizeof(double));
SKIP2;
} 



















