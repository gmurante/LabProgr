/*************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                  */
/*************************************************************************/
/* Write a 2nd order RK integrator and apply it to solving the following */
/* ODE:                                                                  */
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
/* Assigned tasks:                                                       */
/* - integrate the equation for (2 * t_gas)￼and write output each        */
/*   (t_gas / 5);                                                        */
/* -  how do you chose the integration interval h?                       */
/*  - how do the accuracy of solution and the computing time vary with   */
/*    the integration interval?                                          */
/*                                                                       */
/* Compile the code:                                                     */
/* $ gcc -Wall -Wextra sfr.c -o sfr -lm                                  */
/*                                                                       */
/* Run the code:                                                         */
/* $ ./sfr                                                               */
/*                                                                       */
/* Author: David Goz - david.goz@inaf.it                                 */
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************** CONSTANT ******************************/
typedef double MyFloat;
static const MyFloat c_      = 0.02; /* star formation efficiency */
static const MyFloat rho_gas = 10;   /* M_sun / kpc^3             */
static const MyFloat t_gas   = 1.5;  /* Gyr                       */
/******************************************************************/

/* evaluate pow(x, N) using the right type */
MyFloat my_pow(const MyFloat x,
	       const MyFloat N)
{
  const size_t mysize = sizeof(MyFloat);
  
  if (mysize == sizeof(double))
    return pow(x, N);
  else if (mysize == sizeof(float))
    return powf(x, N);
  else if (mysize == sizeof(long double))
    return powl(x, N);
  else
    {
      printf("\n\t Error in my_pow function - type not recognized ... aborting ... \n\n");
      exit(EXIT_FAILURE);
    }
}

/* expected analytical solution */
MyFloat rho_gas_check(const MyFloat x,
		      const MyFloat N)
{
  const MyFloat coeff = (c_ * rho_gas / t_gas);

  return (coeff * my_pow(x, (N + 1)) / (N + 1));
}

/* Star formation rate function of the form: */
/* - d rho / dt = coeff * pow(t, N), where   */
/*   coeff = (c_ * rho_gas / t_gas);         */
MyFloat star_formation_rate(const MyFloat time,
			    const MyFloat N)
{
  const MyFloat coeff = (c_ * rho_gas / t_gas);
  
  return ((coeff) * my_pow(time, N));
}

/* Runge-Kutta second order finds the value of y for a given */
/* x using step size h and initial values y0 and x0;         */
/* The integrand is passed as a pointer to function          */
MyFloat RK2(const MyFloat x0,                               /* starting x */
	    const MyFloat y0,                               /* starting y */
	    const MyFloat xf,                               /* final    x */
	    const MyFloat h,                                /* step size  */
	    const MyFloat N,                                /* sfr power  */
	    MyFloat (*dydx)(const MyFloat, const MyFloat))  /* derivative */
{
  if ((x0 + h) > xf)
    {
      printf("\n\t RK2 fails: decrease the step size for the integration \n\n");
      exit(EXIT_FAILURE);
    }

  MyFloat x = x0; /* set initial x */
  MyFloat y = y0; /* set initial y */

  /* driver for the integration */
  while (x < xf)
    {
      /****** Ruge-Kutta 2-nd order formulas *********/
      /* k1     = h * f(x(n), y(n))                  */
      /* k2     = h * f(x(n) + (h/2), y(n) + (k1/2)) */
      /* y(n+1) = y(n) + k2 + O(h^3)                 */
      /***********************************************/
      /***********************************************/
      /* In our case f = f(x(n)), so only k2 is      */
      /* needed.                                     */
      /* - k2 = h * f(x(n) + (h/2))                  */
      /* - y(n+1) = y(n) + k2                        */
      /***********************************************/
      
      const MyFloat x_ = (x + (0.5 * h));      
      const MyFloat k2 = h * (*dydx)(x_, N);

      /* update y */
      y += k2;

      /* update next value of x */
      x += h;
    } /* iterations */
  
  return y;
}

int main()
{  
  const MyFloat t0 = 0.0;
  const MyFloat tf = 2.0 * t_gas;
  const MyFloat rho_star_t0 = 0.0;
  const MyFloat h = (t_gas / 5.0);

  printf("\n\t Initial conditions:");
  printf("\n\t\t - t0 = 0.0");
  printf("\n\t\t - rho_star(t0) = 0.0");
  printf("\n\t\t - (c_ * rho_gas / t_gas) = 0.133 [Msun/(kpc^3 * Gyr)]\n");
  
  printf("\n\t *******************************************************************************");
  printf("\n\t 1] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas) * (t - t0) \n");

  MyFloat t_start  = t0;
  MyFloat rho_star = rho_star_t0;
  while ((t_start + h) <= tf)
    {
      rho_star = RK2(t_start, rho_star, t_start+h, h, 0.0, star_formation_rate);
     
      printf("\n\t\t RK2: rho_star(%3.2lf) = %3.2lf   -   Expected: rho_star(%3.2lf) = %3.2lf",
	     t_start+h, rho_star, t_start+h, rho_gas_check(t_start+h, 0.0));

      t_start += h;
    }

  printf("\n\t *******************************************************************************");
  printf("\n\n\t 2] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas / 2) * (t^2 - t0^2) \n");

  t_start  = t0;
  rho_star = rho_star_t0;
  while ((t_start + h) <= tf)
    {
      rho_star = RK2(t_start, rho_star, t_start+h, h, 1.0, star_formation_rate);
     
      printf("\n\t\t RK2: rho_star(%3.2lf) = %3.2lf   -   Expected: rho_star(%3.2lf) = %3.2lf",
	     t_start+h, rho_star, t_start+h, rho_gas_check(t_start+h, 1.0));

      t_start += h;
    }

  printf("\n\n");
  
  return 0;
}
