/**************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                   */
/**************************************************************************/
/* Rewrite readlines to store lines in an array supplied by main,         */
/* rather than calling 'alloc' (K&R pag. 101) to maintain storage.        */
/*                                                                        */
/* N.B. The 'getline' function is already defined in the standard header  */
/* <stdio.h>, so if you include such a header the compiler will complain  */
/* because it founds a previous declaration of the function in <stdio.h>. */
/* One possible solution is to change the name 'getline' in the source    */
/* code of the exercise, e.g 'my_getline', so no aliasing is possible.    */
/* The standard header <stdio.h> must be included because the code uses:  */
/* - strcmp;                                                              */
/* - strcpy;                                                              */
/*                                                                        */
/* Compile the code:                                                      */
/* $ gcc -Wall -O0 5.7.c -o 5.7.x                                         */
/*                                                                        */
/* Run the code:                                                          */
/* $ ./5.7.x                                                              */
/* Usage: Lines are separated pressing Enter-key and inserting lines is   */
/* usually stopped by pressing Ctrl-D on UNIX platforms (EOF).            */
/*                                                                        */
/* Author: David Goz - david.goz@inaf.it                                  */
/**************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAXLINES  10                  /* max number of lines to be sorted */
#define MAXLEN    100                 /* max length of any input line     */
#define MAXSIZE   (MAXLINES * MAXLEN) /* max size of the char buffer      */

/* function prototypes used by the main function */
int readlines(char *lineptr[], int nlines, char *allocbuf, const int max_size_buffer);
void writelines(char *lineprt[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main()
{
  char *lineptr[MAXLINES]; /* array of pointers to each line */
  char allocbuf[MAXSIZE];  /* storage for all lines          */
  
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, MAXLINES, allocbuf, MAXSIZE)) >= 0) 
    {
      printf("\n\t Sorting the lines...\n");
      qsort(lineptr, 0, nlines-1);

      printf("\n\t Writing the lines...\n");
      writelines(lineptr, nlines);
      printf("\n");
      
      return 0;
    } 
  else 
    {
      printf("error: input too big to sort\n");

      return -1;
    }
}

/* From K&R pag. 29 */
int my_getline(char *s,
	       const int lim)
{
  int c, i;
  for (i=0 ; i<lim-1 && (c=getchar())!=EOF && c!='\n' ; ++i)
    s[i]=c;

  if (c=='\n')
    {
      s[i]=c;
      ++i; 
    }

  s[i]='\0';

  return i; 
}

/* From K&R pag. 109 and modified to handle the provided char *buffer */
int readlines(char *lineptr[],           /* array of char pointers to each line                                           */
	      const int maxlines,        /* max number of lines                                                           */
	      char *buffer,              /* pointer to char array where lines are stored (allocated by the main function) */
	      const int max_size_buffer) /* max size of the char array                                                    */
{
  printf("\n\t Enter the lines >\n");
  
  char line[MAXLEN];
  int nlines = 0, len;
  char *p = buffer; /* p points at the beginning of buffer */

  while ((len = my_getline(line, MAXLEN)) > 0) /* while loop stops when Ctrl-D is typed, so len==0 */
    {
      /* check boundaries */
      if ((nlines >= maxlines) || ((buffer + max_size_buffer - p) < len)) /* the function checks if there   */
                                                                          /* is enough free space in buffer */
	return -1;
      else
	{
	  line[len-1] = '\0';    /* delete newline */
	  strcpy(p, line);       /* copy line into p */
	  lineptr[nlines++] = p; /* pointer to the string is stored in the array */
	  p += len;              /* p is moved forwards of len elements */
	}
    } /* while loop */
    
  return nlines;
}

/* From K&Rpag. 109 */
void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf ("%s\n", *lineptr++);

  return;
}

/* From K&R pag. 110 */
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* From K&R pag. 110 */
void qsort(char *v[], int left, int right)
{  
  int i, last;
    
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */

  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0) /* note the strcmp! here is where the double indirection is at work*/
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);

  return;
}
