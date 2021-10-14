/***********************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                */
/***********************************************************************/
/* On the repository you find a file "blocchi". It contains the LABEL  */
/* of Gadget's binary output blocks and its meaning. Write a code that,*/
/* using an hash table, takes in input the block name and outputs its  */
/* meaning.                                                            */
/*                                                                     */
/* Compile the code:                                                   */
/* $ gcc -Wall -O0 7.3.c -o 7.3.x                                      */
/*                                                                     */
/* Run the code:                                                       */
/* $ ./7.3.x <block name>                                              */
/*                                                                     */
/* Author: David Goz - david.goz@inaf.it                               */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist 
{
  struct nlist *next; /* next entry in chain */
  char         *name; /* defined name        */
  char         *defn; /* replacement text    */
};

/* size of the hash-table */
#define HASHSIZE   10
struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
/* hash value needs not to be unique  */
unsigned int hash(const char *s)
{
  unsigned int hashval;
  for (hashval=0 ; *s != '\0' ; s++)
    hashval = *s + (31 * hashval);
  
  return (hashval % HASHSIZE);
}

/* lookup: look for s in hashtab */
struct nlist * lookup(const char *s)
{
  struct nlist *np = NULL;
  for (np = hashtab[hash(s)] ; np != NULL ; np = np->next)
    {
      if (strcmp(s, np->name) == 0) /* found */
	return np;
    }

  return NULL;
}

char *strdup(const char *s) /* save string s somewhere */
{
  char *p = NULL;
  if (!(p = (char *)malloc(strlen(s) + 1)))
    {
      printf("\n\t Cannot allocate space for string: %s ... aborting ... \n\n",
	     s);
      exit(EXIT_FAILURE);
    }
  else
    strcpy(p,s);

  return p;
}

/* install: put (name, defn) in hashtab */
struct nlist * install(const char *name,
		       const char *defn)
{
  struct nlist *np = NULL;
  if (lookup(name) == NULL) /* not found */
    {
      np = (struct nlist *) malloc(sizeof(struct nlist));
      if ((np == NULL)                        ||
	  ((np->name = strdup(name)) == NULL) ||
	  ((np->defn = strdup(defn)) == NULL))
	return NULL;

      const unsigned int hashval = hash(name);
      /* the element becomes the first in the linked list */
      np->next = hashtab[hashval];
      hashtab[hashval] = np;
    }

  return np;
}
void make_hash_table(const char *filename)
{  
  /* init the hashtab */
  for (unsigned int i=0 ; i<HASHSIZE ; i++)
    hashtab[i] = NULL;

  /* open file */
  FILE *fp = NULL;
  if (!(fp = fopen(filename, "r")))
    {
      printf("\n\t Cannot open file: %s ... aborting ...\n\n",
  	     filename);
      exit(EXIT_FAILURE);
    }

  /* the buffer should be long enough to get an entire line */
  const unsigned int N = 512;

  char buf[N];  
  while (fgets(buf, N, fp)) /* get the current line */
    {
      /* extract the block 'name' from buffer */
      /* each is 4 char long */
      char name[5];
      sscanf(buf, "%s", name);

      /* extract the meaning of the block */
      /* we need to remove the '\t' character */
      char defn[N];
      strcpy(defn, (strrchr(buf, '\t') + 1));

      /* install in hashtab */
      struct nlist *np = install(name, defn);
      if (np == NULL)
	{
	  printf("\n\t Cannot install in the hastab ... aborting ... \n\n");
	  exit(EXIT_FAILURE);
	}
    }
  
  fclose(fp);
  
  return;
}

void free_memory()
{
  for (int i=0 ; i<HASHSIZE ; i++)
    {
      struct nlist *np = hashtab[i];
      while (np)
	{
	  struct nlist *tmp = np->next;
	  free(np->name);
	  free(np->defn);
	  free(np);
	  np = tmp;
	}
    }

  return;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("\n\t USAGE: <executable> <GADGET block name> \n\n");
      return -1;
    }

  char name[128];
  sprintf(name, "%s", argv[1]);
  
  const char filename[] = "blocchi";

  /* create the hash table */
  make_hash_table(filename);

  /* get the block name in the hash table */
  struct nlist *np = lookup(name);

  if (np)
    printf("\n\t GADGET block found: %s ---> %s \n\n",
	   np->name, np->defn);
  else
    printf("\n\t GADGET block: %s not found \n\n",
	   name);

  /* free memory */
  free_memory();
  
  return 0;
}
