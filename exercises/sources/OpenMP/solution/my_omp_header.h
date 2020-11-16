/*********************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                          */
/*********************************************************************************/
/* Author: David Goz - david.goz@inaf.it                                         */
/*********************************************************************************/

#if !defined(MY_OMP_HEADER)
#define MY_OMP_HEADER

#include <stdio.h>
#include <stdlib.h>

#if defined(_OPENMP)
#   include <omp.h>
#else
#   define omp_set_num_threads(ignore) ((void) 0)
#   define omp_get_thread_num()        0
#   define omp_get_num_threads()       1
#endif /* _OPENMP */

#endif /* MY_OMP_HEADER */
