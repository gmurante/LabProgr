/*************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                  */
/*************************************************************************/
/* Use the GSL library to solving the following ODE with N=0,1:          */
/*                                                                       */
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
/* To debug the code (gdb is invoked):                                   */
/* $ make debug                                                          */
/*                                                                       */
/* Author: David Goz - david.goz@inaf.it                                 */
/*************************************************************************/

/* Header where global constants and function are declared */
#include "my_header.h"

int sfr_1(MyFloat       time,
	  const MyFloat *y,
	  MyFloat       *f,
	  void          *params)
{
  (void)(time); /* avoid unused parameter warning */
  (void)(y);
  MyFloat coeff = *(MyFloat *)params;
  f[0] = coeff;

  return GSL_SUCCESS;
}

int sfr_2(MyFloat       time,
	  const MyFloat *y,
	  MyFloat       *f,
	  void          *params)
{
  (void)(time); /* avoid unused parameter warning */
  (void)(y);
  MyFloat coeff = *(MyFloat *)params;
  f[0] = (coeff * time);

  return GSL_SUCCESS;
}

/* only used by sfr_2 */
int jac(MyFloat       time,
	const MyFloat *y,
	MyFloat       *dfdy,
	MyFloat       *dfdt,
	void          *params)
{
  (void)(time); /* avoid unused parameter warning */
  (void)y;
  
  MyFloat mu = *(MyFloat *)params;

  dfdt[0] = mu;

  dfdy = NULL;
  
  return GSL_SUCCESS;
}

int main()
{
  const MyFloat coeff = (c_ * rho_gas / t_gas);

  gsl_odeiv2_system sys[2] = {{sfr_1, NULL, 1, &coeff},
			      {sfr_2, jac, 1,  &coeff}};

  /* array of strings with analytical star formation */
  char *my_print[] = {"\n\t 1] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas) * (t - t0)",
                      "\n\n\t 2] rho_star(t) = rho_star(t0) + (c_ * rho_gas / t_gas / 2) * (t^2 - t0^2)"};
  
  /* set final time for the integration */
  const MyFloat x2 = (2.0 * t_gas);

  /* number of steps */
  const int steps = 10;

  /* call odeiv2_driver passing sfr_1 and sfr_2 */
  for (int i=0 ; i<2 ; i++)
    {
      /* allocation initial condition rho_star(t0) = 0 */
      MyFloat ystart = 0.0;

      /* set initial time for the integration */
      MyFloat x1 = 0.0;

      /* the driver object is a wrapper that combines the evolution, control and stepper objects */
      gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys[i], gsl_odeiv2_step_rkf45,
							   1e-5, 1e-5, 0.0);

      /* print the result of the RK integration */
      printf("%s", my_print[i]);
      
      for (int i=1 ; i<=steps ; i++)
	{
	  MyFloat xi = (i * x2 / (MyFloat)steps);

	  int status = gsl_odeiv2_driver_apply(d, &x1, xi, &ystart);

	  if (status != GSL_SUCCESS)
	    {
	      printf ("error, return value=%d\n", status);
	      break;
	    }

	  printf("\n\t RK4: rho_star(%3.2lf) = %3.2lf [step: %d]",
		 xi, ystart, i);
	}

      /* deallocate gsl driver */
      gsl_odeiv2_driver_free(d);
    }

  printf("\n\n");
  
  return 0;
}
