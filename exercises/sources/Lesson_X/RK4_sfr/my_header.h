#include "my_typedef.h"

/************************** CONSTANT ******************************/
static const MyFloat c_      = 0.02; /* star formation efficiency */
static const MyFloat rho_gas = 10;   /* M_sun / kpc^3             */
static const MyFloat t_gas   = 1.5;  /* Gyr                       */
/******************************************************************/

/*************************** function prototypes ************************************************/
/* User storage for intermediate results. Preset kmax and dxsav in the calling program. If      */
/* kmax = 0 results are stored at approximate intervals dxsav in the arrays xp[1..kount] ,      */
/* yp[1..nvar][1..kount], where kount is output by odeint. Defining declarations for these      */
/* variables, with memory allocations xp[1..kmax] and yp[1..nvar][1..kmax] for the arrays,      */
/* should be in the calling program.                                                            */
void odeint(float ystart[], int nvar, float x1, float x2, float eps, float h1,
            float hmin, int *nok, int *nbad,
            void (*derivs)(float, float [], float []),
            void (*rkqs)(float [], float [], int, float *, float, float, float [],
			 float *, float *, void (*)(float, float [], float [])));
/* Runge-Kutta driver with adaptive stepsize control. Integrate starting values ystart[1..nvar] */
/* from x1 to x2 with accuracy eps, storing intermediate results in global variables. h1 should */
/* be set as a guessed first stepsize, hmin as the minimum allowed stepsize (can be zero). On   */
/* output nok and nbad are the number of good and bad (but retried and fixed) steps taken, and  */
/* ystart is replaced by values at the end of the integration interval. derivs is the           */
/* user-supplied routine for calculating the right-hand side derivative, while rkqs is the name */
/* of the stepper routine to be used.                                                           */

/* the header of rkqs is necessary because must be passed to odeint */
void rkqs(float y[], float dydx[], int n, float *x, float htry, float eps,
	  float yscal[], float *hdid, float *hnext,
	  void (*derivs)(float, float [], float []));
/************************************************************************************************/
