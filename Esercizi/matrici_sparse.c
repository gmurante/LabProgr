#include <stdio.h>
#include <stdlib.h>

#define N_MATRIX 50

typedef double MyFloat;

struct particle_data  
{
  MyFloat x,y,z, mass;
};

struct sparse_matrix
{
  int ix, iy, iz;
  MyFloat value;
}; 

typedef struct sparse_matrix SparseMatrix;
typedef struct particle_data ParticleData;

int main(int argc, char *argv[])
{
  int N;
  int read_particles(ParticleData *);
  SparseMatrix *allocate_sparse_matrix(int, SparseMatrix *);
  void create_sparse_matrix(int , ParticleData *, SparseMatrix *);
  void print_sparse_matrix(int, SparseMatrix *);
  ParticleData *P;
  SparseMatrix *M;
  
  N=read_particles(P);
  M = allocate_sparse_matrix(N, M);

  printf("\nSparse matrix memory usage: %lu bytes\n",N*sizeof(struct sparse_matrix));
  printf("Full matrix memory requirement: %lu bytes\n\n", N_MATRIX*N_MATRIX*N_MATRIX*sizeof(MyFloat));

  create_sparse_matrix(N, P, M);
  printf("Matrix created\n\n");

  print_sparse_matrix(N, M);


}


int read_particles(ParticleData *P)
{
  /* This function will read the number of particles, their coordinate
     and their mass */
  int N=10;
  ParticleData *allocate_parts(int, ParticleData *);


  allocate_parts(N,P);

  /* Here we suppose that coordinates are in (0,1000) */
  for(int i=0; i<N; i++)
    {
      P[i].x=(float)i;
      P[i].y=i*10.;
      P[i].z=i*100.-1.;
      P[i].mass=1.0;
    }
  return N;
}


ParticleData *allocate_parts(int N, ParticleData *P)
{
   return (ParticleData *)malloc(N*sizeof(ParticleData));
}


SparseMatrix *allocate_sparse_matrix(int N, SparseMatrix *M)
{
  M = (SparseMatrix  *)malloc(N*sizeof(SparseMatrix));
  for(int i=0; i<N; i++)
    M[i].value=0.0;
  return M;
}



void create_sparse_matrix(int N, ParticleData *P, SparseMatrix *M)
{
  int ix, iy, iz;
  for(int i=0; i<N; i++)
    {
      ix = ( (int) P[i].x / 1000.0 ) * N_MATRIX;
      iy = ( (int) P[i].y / 1000.0 ) * N_MATRIX;
      iz = ( (int) P[i].z / 1000.0 ) * N_MATRIX; 
      M[i].ix = ix;
      M[i].iy = iy;
      M[i].iz = iz;
      M[i].value += P[i].mass;      
    }
  return;
}

void print_sparse_matrix(int N, SparseMatrix *M)
{
  for(int i=0; i<N; i++)
    printf("%d %d %d %f\n", M[i].ix, M[i].iy,M[i].iz, M[i].value);

  return;
}
