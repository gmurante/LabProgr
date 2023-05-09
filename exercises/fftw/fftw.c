//
//  compile:
//  gcc -Wall -Wextra -I${FFTW3_INSTALL_PATH}/include -L${FFTW3_INSTALL_PATH}/lib fftw.c -o FFTW -lfftw3 -lm
//
//  fftw_esercizio.c
//
//  Created by Giuliano Taffoni on 04/05/23.
//

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fftw3.h>
int main ( void )
{
  ptrdiff_t i;
  const ptrdiff_t n = 1024;
  fftw_complex *in;
  fftw_complex *out;
  fftw_plan plan_forward;
  /* Create arrays. */
  in = fftw_malloc ( sizeof ( fftw_complex ) * n ); out = fftw_malloc ( sizeof ( fftw_complex ) * n );
  /* Initialize data */
  for(i=0;i<n;i++) {
    if (i <= (n/2-1)) {
      in[i][0] = 1.;
      in[i][1] = 0.;
    }
    else{
      in[i][0] = 0.;
      in[i][1] = 0.;
    }
  }
  /* Create plans. */
  plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
  /* Compute transform (as many times as desired) */
  fftw_execute ( plan_forward ); /* deallocate and destroy plans */
  fftw_destroy_plan ( plan_forward );
  fftw_free ( in );
  fftw_free ( out );

  return 0;
}
