/*************************************************************************/
/* Course: Advanced Programming for Physics (2019-2020)                  */
/*************************************************************************/
/* The program creates a binary tree using Particles with positions (1D) */
/* in the range [0,1). Besides position, an ID and a Mass are assigned   */
/* to every Particle.                                                    */
/* More in detail, the program goes through the following steps:         */
/* - it creates a binary tree structure where each node is a Particle    */
/*   with an ID (the root with ID 0), a position (1D) and mass, both     */
/*   random in the range [0,1); left and right children are based on     */
/*   particle's positions;                                               */
/* - it searches and displays the Particles with min and max position;   */
/* - it searches a Particle in the tree looking at its ID;               */
/* - it destroys the binary tree, freeing the memory.                    */ 
/*                                                                       */
/* Compile the code using the command:                                   */
/* $ gcc -Wall binary_tree.c -o binary_tree                              */
/*                                                                       */
/* Run the program using the command:                                    */
/* $ ./binary_tree                                                       */
/*                                                                       */
/* Author: David Goz - david.goz@inaf.it                                 */
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _N_   8
#define _A_   0.0
#define _B_   1.0

typedef float MyFloat;

/* Particle data structure */
typedef struct Part
{
  /* particle ID */
  int ID;
  
  /* position */
  MyFloat Pos;

  /* mass */
  MyFloat Mass;

  /* tree */
  struct Part *right, *left;
  
} Particle;

/* Create binary tree */
/* The algorithm is: if the tree is empty, then create a new node, otherwise, */
/* if the Pos being inserted is larger (lower) than the current node, insert  */
/* it into the right (left) subtree and move the pointer   */
Particle * BuildTree(Particle *, const MyFloat Pos,
		     const MyFloat Mass, const int ID);

Particle *SearchTree(Particle *, const int);

/* Find the particle with max Pos                                           */
/* The max value is the greatest value stored in the right side of the tree */
Particle *FindMaxTree(Particle *);

/* Find the particle with min Pos                                        */
/* The min value is the lowest value stored in the left side of the tree */
Particle *FindMinTree(Particle *);

/* destroy the tree */
void DestroyTree(Particle *);

/* get random number in [a, b] */
MyFloat random_number(const MyFloat, const MyFloat);

/* display the element of the binary tree */
void  DisplayTree(Particle *);

/* search a Particle by its ID in the binary tree */
void ParticleSearchTree(Particle *, const int);

int main()
{
  /* Particle root */
  Particle *root = NULL;

  /* Create the tree */
  for (int Part=0 ; Part<_N_ ; Part++)
    {
      MyFloat Pos  = random_number(_A_, _B_);
      MyFloat Mass = random_number(_A_, _B_);
      
      if (!(root = BuildTree(root, Pos, Mass, Part)))
	{
	  printf("\n\t Cannot create the tree ... aborting ...\n");
	  return 0;
	}
    }

  /* display the binary tree */
  printf("\n\n\t Displaying the binary tree...");
  DisplayTree(root);
  printf("\n");

  /* Find the min value in the tree */
  Particle *PMin = NULL;
  if (!(PMin = FindMinTree(root)))
    {
      printf("\n\t Cannot find PMin ... aborting ...\n");
      DestroyTree(root);
      return -1;
    }

  /* Find the max value in the tree */
  Particle *PMax = NULL;
  if (!(PMax = FindMaxTree(root)))
    {
      printf("\n\t Cannot find PMax ... aborting ...\n");
      DestroyTree(root);
      return -1;
    }    

  /* print Pmin and Pmax */
  printf("\n\n\t PMin ---> ID: %d, Pos:%f, Mass: %f",
	 PMin->ID, PMin->Pos, PMin->Mass);
  printf("\n\t PMax ---> ID: %d, Pos:%f, Mass: %f\n",
	 PMax->ID, PMax->Pos, PMax->Mass);  

  /* search a Particle in the tree     */
  /* get a random interger in [0, _N_] */
  srand(time(NULL));
  const int rID = rand() % _N_;
  ParticleSearchTree(root, rID);
  
  /* delete tree bottom up*/
  DestroyTree(root);

  printf("\n\n\t END OF GAME!!!\n");
  
  return 0;
}

Particle * BuildTree(Particle *P,
		     const MyFloat Pos,
		     const MyFloat Mass,
		     const int ID)
{
  /* If P == NULL we have reached an empty tree  */
  /* and a space for new Particles must be added */
  if (!P)
    {       
      if ((P = (Particle *)malloc(sizeof(Particle))) == NULL)
	return NULL;
      else
	{
	  P->Pos  = Pos;
	  P->Mass = Mass;
	  P->ID   = ID;
	  P->left = P->right = NULL;

	  printf("\n\t Creating Particle: %d, Pos: %f, Mass: %f",
		 ID, Pos, Mass);
	}
    }
  /* A not empty tree has been reached.               */
  /* If Pos of new Particle is lower than the Pos     */
  /* of the node then to insert into the left subtree */
  else if (Pos < P->Pos)
    P->left  = BuildTree(P->left, Pos, Mass, ID);
  /* If Pos of new Particle is larger than the Pos     */
  /* of the node then to insert into the right subtree */
  else
    P->right = BuildTree(P->right, Pos, Mass, ID);

  return P;
}

Particle * FindMaxTree(Particle *P)
{
  if (P == NULL)
    return NULL;

  if (P->right == NULL)
    return P;
  else
    return FindMaxTree(P->right);
}

Particle * FindMinTree(Particle *P)
{
  if (!P)
    return NULL;

  if (!P->left)
    return P;
  else
    return FindMinTree(P->left);
}

/* Code to search for a particular element in the tree */
void ParticleSearchTree(Particle *P,
			const int ID)
{
  if (!P)
    return;

  ParticleSearchTree(P->left, ID);

  if (P->ID == ID)
    printf("\n\t Particle found. ID: %d, Pos: %f, Mass: %f\n",
	   P->ID, P->Pos, P->Mass);

  ParticleSearchTree(P->right, ID);

  return;
}

void DisplayTree(Particle *P)
{
  if (!P)
    return;

  DisplayTree(P->left);

  printf("\t %d  ->", P->ID);

  DisplayTree(P->right);

  return;
}

void DestroyTree(Particle *P)
{
  if (P)
    {
      /* destroy left node */
      DestroyTree(P->left);

      /* destroy right node */
      DestroyTree(P->right);

      /* print particle */
      printf("\n\t Deleting Particle: %d", P->ID);

      /* free Particle structure */
      free(P);
    } /* P != NULL */
  
  return;
}

MyFloat random_number(const MyFloat a,
		      const MyFloat b)
{
  MyFloat rendfrac = rand() / (RAND_MAX + 1.0);

  return (rendfrac * (b - a) + a);
}
