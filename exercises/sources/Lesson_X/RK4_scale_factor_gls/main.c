/*************************************************************************/
/* Course: Advanced Programming for Physics (2020-2021)                  */
/*************************************************************************/
/* Use the GSL library to intgrate with the RK algorithm the equation    */
/* for the evolution of the scale factor a:                              */
/*                                                                       */
/* dadt = H0 * a *sqrt(E), where                                         */
/* E = ((M * (a0 / a)^3) + (R * (a0 / a)^2) + (L * (a0 / a)^(3(1+w))))   */
/* and M = OmegaM , R = OmegaR, L = OmegaL.                              */
/*                                                                       */
/* OmegaM, OmegaL, and w must be arguments of the program, and           */
/* the constraints are:                                                  */
/* - a0 = 1;                                                             */
/* - OmegaR = (1 - OmegaM - OmegaL);                                     */
/*                                                                       */
/* To test the program:                                                  */
/* $ make test                                                           */
/*                                                                       */
/* To debug the code (gdb is invoked):                                   */
/* $ make debug                                                          */
/*                                                                       */
/* Author: David Goz - david.goz@inaf.it                                 */
/*************************************************************************/

/* Header where global constants and function are declared */
#include "my_header.h"

/* params: a0, H0, OmegaM, OmegaR, OmegaL, w                                          */
/* E = ((OmegaM * (a0 / a)^3) + (OmegaR * (a0 / a)^2) + (OmegaL * (a0 / a)^(3(1+w)))) */
/* dadt = (H0 * a) * sqrt(E)                                                          */
/* a0 = 1                                                                             */
/* a ---> y                                                                           */
/* f ---> dadt                                                                        */
int derivs(MyFloat        t,
	   const MyFloat *y,
	   MyFloat       *f,
	   void          *params)
{
  (void)(t); /* avoid unused parameter warning */

  MyFloat *coeff = (MyFloat *)params;
  const MyFloat H0     = *(coeff);
  const MyFloat OmegaM = *(coeff + 1);
  const MyFloat OmegaR = *(coeff + 2);
  const MyFloat OmegaL = *(coeff + 3);
  const int     w      = (int)(*(coeff + 4));

  const MyFloat inv_y  = (1.0 / y[0]);
  const MyFloat inv_y2 = gsl_pow_2(inv_y); /* inlined because of HAVE_INLINE macro */
  const MyFloat inv_y3 = gsl_pow_3(inv_y); /* inlined because of HAVE_INLINE macro */
  
  f[0] = H0 * y[0] * sqrt((OmegaM * inv_y3) + (OmegaR * inv_y2) +
			  (OmegaL * gsl_pow_int(inv_y, (int)(3 * (1 + w)))));

  return GSL_SUCCESS;
}

int main(int argc, char *argv[])
{
  if (argc < 4)
    {
      printf("\n\t USAGE: <executable>  <OmegaM>  <OmegaL>  <w> \n\n");
      return -1;
    }

  const MyFloat OmegaM = atof(argv[1]);
  const MyFloat OmegaL = atof(argv[2]);
  const MyFloat w      = atof(argv[3]);

  /* fix OmegaR */
  const MyFloat OmegaR = (1.0 - OmegaM - OmegaL);

  printf("\n\t Parameters:");
  printf("\n\t\t H0     = %lg [km/s/Mpc]", H0);
  printf("\n\t\t OmegaM = %lg", OmegaM);
  printf("\n\t\t OmegaR = %lg", OmegaR);
  printf("\n\t\t OmegaL = %lg",OmegaL);
  printf("\n\t\t w      = %lg \n", w);

  const char *eq = "\n\t E = ((OmegaM * (a0 / a)^3) + (OmegaR * (a0 / a)^2) + (OmegaL * (a0 / a)^(3(1+w)))) \n\t dadt = (H0 * a) * sqrt(E)\n";

  printf("%s", eq);
  
  /* Turn off the error handler by defining an error handler which does nothing. */
  /* This will cause the program to continue after any GSL error, so the return  */
  /* values from any library routines must be checked. This is the recommended   */
  /* behavior for production programs.                                           */
  gsl_set_error_handler_off();

  /* set of parameters */
  MyFloat parameters[5] = {H0, OmegaM, OmegaR, OmegaL, w};

  /* set initial time for the integration */
  const MyFloat x1 = 0.0;

  /* set final time for the integration */
  const MyFloat x2 = 20;

  /* set the number of steps */
  const unsigned int steps = 20;

  /* set the dt */
  const MyFloat dt = (x2 - x1) / (MyFloat)steps;

  /* allocation initial condition a(t0) = 1 */
  const MyFloat ystart = 1.0;

  /* define the system of equations      */
  /* rkf45 does not require the Jacobian */
  gsl_odeiv2_system sys = {&derivs, NULL, 1, parameters};
  
  /* the driver object is a wrapper that combines the evolution, control and stepper objects */
  gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys,                  /* system of equations              */
						       gsl_odeiv2_step_rkf45, /* stepper function                 */
						       dt,                    /* proposed time step               */
						       1e-5,                  /* allowed local error on each step */
						                              /* within this absolute error       */
						       0.0);                  /* allowed local error on each step */
                                                                              /* within this relative error       */
  
  /* block to store integration time */
  gsl_block *time = gsl_block_alloc(steps);
  /* block to store a(t) */
  gsl_block *a    = gsl_block_alloc(steps);

  if ((time==NULL) || (a==NULL))
    {
      printf("\n\t Cannot allocate memory ... aborting ... \n\n");
      exit(EXIT_FAILURE);
    }
  else if (time->size != a->size)
    {
      printf("\n\t Check time and a block size \n\n");
      gsl_block_free(a);
      gsl_block_free(time);
      exit(EXIT_FAILURE);
    }

  /* initial integration time */
  MyFloat t = x1;
  /* initial value for a */
  MyFloat a_start = ystart;
  /* start the integration */
  for (unsigned int step=0 ; step<steps ; step++)
    {
      /* integration [t, t + dt] */
      int status = gsl_odeiv2_driver_apply(d, &t, (t + dt), &a_start);

      if (status != GSL_SUCCESS)
	{
	  /* print error and exit */
	  printf ("\n GSL error: %s\n\n", gsl_strerror(status));
	  exit(EXIT_FAILURE);
	}

      /* store integration time */
      time->data[step] = t;

      /* store a(t) */
      a->data[step] = a_start;
    } /* integration loop */

  /* print results */
  for (unsigned int step=0 ; step<time->size ; step++)
    printf("\n\t RK45: a(%3.2lf) = %3.2lf [step: %d]",
	   time->data[step], a->data[step], step);
  
  /* deallocate gsl driver */
  gsl_odeiv2_driver_free(d);

  /* free blocks */
  gsl_block_free(a);
  gsl_block_free(time);
  
  printf("\n\n");
  
  return 0;
}
