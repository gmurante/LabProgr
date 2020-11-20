/*************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                  */
/*************************************************************************/
/* Use the 4th order RK routines with adaptive time step from the        */
/* Numerical Recipies and apply it to solving the following              */
/* ODE with N=0,1:                                                       */
/*     d_(rho_star(t)) / d_t = (c_ * rho_gas / t_gas) * pow(t, N),       */
/*                                                                       */
/* where:                                                                */
/* - c_      = 0.02 is the star formation efficiency;                    */
/* - rho_gas = 10 [Msun/kpc^3] is the gas density                        */
/* - t_gas   = 1.5 [Gyr] is the time consumption of gas                  */
/*                                                                       */
/* The boundary conditions are:                                          */
/* - t0 = 0;                                                             */
/* - rho_star(t0) = 0.                                                   */
/*                                                                       */
/* If N = 0, the analytical solution is:                                 */
/* - rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas) * (t - t0)      */
/*                                                                       */
/* If N = 1, the analytical solution is:                                 */
/* - rho_star(t) = rho_star(t0) + (coeff / 2) * (pow(t, 2) - pow(t0, 2)) */
/*                                                                       */
/* where coeff = (c_ * rho_gas / t_gas)                                  */
/*                                                                       */
/* Compile and run the code using the Makefile:                          */
/* $ make test                                                           */
/*                                                                       */
/* Assigned task:                                                        */
/*                - try to change the accuracy (eps) and the number of   */
/*                  the time steps (kmax). Is the expected number of     */
/*                  outputs? (kount is the actual number of time steps   */
/*                  used by the RK4 routine).                            */
/*                                                                       */
/* Author: David Goz - david.goz@inaf.it                                 */
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* header where global constants and  */
/* function prototypes are defined    */
#include "my_header.h"

/******************* GLOBAL declarations ***********************/
/* odeint.c declares:                                          */
/*   extern int kmax,kount;                                    */
/*   extern float *xp,**yp,dxsav;                              */
/*                                                             */
/* The user must allocate such a variable in the calling       */
/* program and set a value for kmax and dxsav, while kount     */
/* is output by 'odeint' function (odeint.c).                  */
/*                                                             */
/* - kmax: the number of steps where results are stored in     */
/*         xp, yp, at approximate intervals dxsav;             */ 
/* - xp[1,...,kmax] must be allocated by the user;             */
/* - yp[1,...,nvar][1,...,kmax] must be allocated by the user. */
/*                                                             */
/* In our case, nvar = 1, i.e. the time.                       */
/* N.B. Numerical Recipies routines (odeint, rk4, rkck, and    */
/* rkqs) assume Fortran-like vectors, i.e. arrays start at 1,  */
/* meaning that a[1,..,N] should be allocated as:              */
/*  type *a = (type *)malloc((N + 1)*sizeof(type));            */

int kmax, kount;
MyFloat *xp, **yp, dxsav;
/***************************************************************/

/* Time is the only independent variable (time) */
#define NVAR    1

/* coeff = (c_ * rho_gas / t_gas) */ 
/* d_(rho_star(t)) / d_t = coeff  */
void sfr_1(MyFloat time,
	   MyFloat *rho_star,
	   MyFloat *d_rho_star_dt)
{
  (void)time;     /* unused variable */
  (void)rho_star; /* unused variable */

  const MyFloat coeff = (c_ * rho_gas / t_gas);
  
  d_rho_star_dt[NVAR] = coeff;

  return;
}

/* coeff = (c_ * rho_gas / t_gas)      */ 
/* d_(rho_star(t)) / d_t = (coeff * t) */
void sfr_2(MyFloat time,
	   MyFloat *rho_star,
	   MyFloat *d_rho_star_dt)
{
  (void)rho_star;    /* unused variable */

  const MyFloat coeff = (c_ * rho_gas / t_gas);
  
  d_rho_star_dt[NVAR] = (coeff * time);

  return;
}

int main()
{
  /* set initial time for the integration */
  MyFloat x1 = 0.0;
  
  /* set final time for the integration */
  MyFloat x2 = (2.0 * t_gas);
  
  /* set the number of time steps */
  kmax = 10;

  /* set dxsav */
  dxsav = ((x2 - x1) / kmax);

  /* set the accuracy as 10^-5 */
  MyFloat eps = 1.e-5;
  
  /* set h1 (guessed first stepsize) as t_gas/10^2 */
  MyFloat h1 = (0.01 * t_gas);

  /* set hmin (minimum allowed stepsize) as zero */
  MyFloat hmin = 0.0;
  
  /* xp allocation (Fortran-like, so discard zero index) used by odeint */
  xp = (float *)malloc((kmax + 1) * sizeof(MyFloat));

  /* yp allocation (Fortran-like, so discard zero index) used by odeint */
  yp = (MyFloat **)malloc((1 + NVAR) * sizeof(MyFloat *));
  yp[NVAR] = (MyFloat *)malloc((kmax + 1) * sizeof(MyFloat));
  
  /* allocation initial condition rho_star(t0) = 0 (Fortran-like) */
  MyFloat *ystart = (MyFloat *)malloc((1 + NVAR) * sizeof(MyFloat));

  /* allocate nok, nbad used by odeint */
  int nok, nbad;

  /* array of function pointers to sfr_1 and sfr_2 */
  void (* star_formation_rate[])(MyFloat, MyFloat *, MyFloat *) = {sfr_1, sfr_2};

  /* array of strings with analytical star formation */
  char *my_print[] = {"\n\t 1] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas) * (t - t0)",
		      "\n\n\t 2] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas / 2) * (t^2 - t0^2)"};
  
  /* call odeint passing sfr_1 and sfr_2 */
  for (unsigned int i=0 ; i<2 ; i++)
    {
      /* initialize y, i.e. rho_star at t0 */
      ystart[NVAR] = 0.0;

      /* call the RK4 integrator odeint */
      odeint(ystart, NVAR, x1, x2, eps, h1, hmin, &nok, &nbad, star_formation_rate[i], &rkqs);

      /* print the result of the RK integration */
      printf("%s", my_print[i]);
      for (int i=1 ; i<=kount ; i++)
	printf("\n\t RK4: rho_star(%3.2lf) = %3.2lf [step: %d]",
	       xp[i], yp[1][i], i);

      printf("\n\t Number of good steps taken (nok)                      : %d", nok);
      printf("\n\t Number of bad (but tried and fixed) steps taken (nbad): %d", nbad);
    }
      
  printf("\n\n");
  
  /* free memory */
  free(ystart);
  free(yp[NVAR]);
  free(yp);
  free(xp);
  
  return 0;
}
