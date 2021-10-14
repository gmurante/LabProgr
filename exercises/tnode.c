/***********************************************************************************************/
/*                                                                                             */
/*   soluzione esercizio albero binario                                                        */
/*                                                                                             */
/*  L. Belpietro, Nov. 2020                                                                    */
/*                                                                                             */
/***********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DEBUG /* define this for tracking calls to addtree */
              /* comment this out NOT to do the tracking   */

struct tnode 
     { /* the tree node: */
        float num; 
        int count;
        struct tnode *left; /* left child */
        struct tnode *right; /* right child */
     };

#define NMAX 100000 

struct tnode *addtree(struct tnode *p, float w);

void treeprint(struct tnode *);
struct tnode *talloc();

int atlevel;
int main()
 {
    clock_t begin=clock();
    struct tnode *root;
    int n,i;
    float numb[NMAX]; /* questo vettore e' superfluo, si possono direttamente mettere i valori nell'albero */
                      /* occhio che NON si puo' dichiarare numb[n]!! per farlo cosi' occorre allocazione
			 dinamica della memoria! */

    printf("Inserire il numero di valori:\t"); scanf("%d", &n); printf("\n");
    
    srand(clock());
    for (i=1; i<=n; i++) {numb[i-1]=rand()/(1.0+RAND_MAX); printf("%f\n", numb[i-1]);}
    printf("\n ..generation phase finished\n\n");

    atlevel=0;
    root = NULL;
    for (i=0; i<=n-1; i++) root = addtree(root, numb[i]);
    clock_t end=clock();
    double ex_time =(double)(end - begin) / CLOCKS_PER_SEC;
    treeprint(root);
    printf("Il tempo di esecuzione (escluso il print) è di %f secondi per %d valori\n", ex_time, n);
 }


struct tnode *addtree(struct tnode *p, float w)
 {
   
   float cond;

#ifdef DEBUG
   fprintf(stderr," Entro in addtree level %d\n", ++atlevel);
   fprintf(stderr,"             inserisco valore: %f\n",w);
   if( p!=NULL) /* evita accessi a nodi non ancora definiti! */
     fprintf(stderr,"             nel nodo corrente il valore e': %f\n", p->num);
   else
     fprintf(stderr,"             questo nodo non esiste ancora\n");
#endif
   
   if (p == NULL) 
        { /* a new number has arrived */
            p = talloc(); /* make a new node */
	    p->num=w;
    	    p->count=1;
    	    p->left=p->right=NULL;
	    fprintf(stderr,"             installo il valore e creo il nodo\n");

        } 
    else if ((cond=(w-p->num)) == 0.0) /* the word mathes at this level */
            p->count++;                        /* repeated word */
    else if (cond < 0.0)
      {                                 /* less than into left subtree */
#ifdef DEBUG
	fprintf(stderr,"             vado a sinistra\n");
#endif
	p->left = addtree(p->left, w);     /* recalls addtree for the left branch */
      }
    else                                       /* greater than into right subtree */
      {
#ifdef DEBUG
	fprintf(stderr,"             vado a destra\n");
#endif
	p->right = addtree(p->right, w);   /* some thing for the right branch */
      }
#ifdef DEBUG
   fprintf(stderr," Esco da addtree level %d\n", atlevel--);
#endif
   return p;
}

 /* treeprint: in-order print of tree p */
    void treeprint(struct tnode *p)
     {
        if (p != NULL) 
         {
            treeprint(p->left);
            printf("%1d %f\n", p->count, p->num);
            treeprint(p->right);
         }
     }


struct tnode *talloc()
 {
    return (struct tnode *) malloc(sizeof(struct tnode));
 }


