#include "my_typedef.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>  /* header for GSL error handling */
#include <gsl/gsl_odeiv2.h> /* header for GSL ODE function   */

/************************** CONSTANT ******************************/
static const MyFloat c_      = 0.02; /* star formation efficiency */
static const MyFloat rho_gas = 10;   /* M_sun / kpc^3             */
static const MyFloat t_gas   = 1.5;  /* Gyr                       */
/******************************************************************/

