#if !defined(MY_HEADER)
#define MY_HEADER

#include "my_typedef.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>      /* header for GSL error handling */
#include <gsl/gsl_odeiv2.h>     /* header for GSL ODE function   */
#include <gsl/gsl_math.h>       /* header for GSL math functions */
#include <gsl/gsl_block.h>      /* header for gsl_block type     */

/************************** CONSTANT ******************************/
static const MyFloat H0 = 0.070; /* Hubble constant [km/s/Mpc]    */
/******************************************************************/

#endif /* MY_HEADER */
