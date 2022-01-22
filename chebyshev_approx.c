#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>


double T (int n, double x){ //chebyshev polynomial of first kind
	if (n==0)
		return 1;
	else if (n==1)
		return x;
	else
		return 2*x*T(n-1, x)-T(n-2,x);
}

double U (int n, double x){ //chebyshev polynomial of second kind
	if (n==0)
		return 1;
	else if (n==1)
		return 2*x;
	else 
		return 2*x*U(n-1, x)-U(n-2, x);
}

double dT(int n, double x){
	if (n==0)
		return 0;
	else if (n==1)
		return 1;
	return n*U(n-1, x);
}

double dU(int n, double x){
	if (n==0)
		return 0;
	else if (n==1)
		return 2;
	return ((n+1)*T(n+1, x) - x*U(n, x))/(x*x - 1);
}
double d2T(int n, double x) {
	if (n==0)
		return 0;
	else if (n==1)
		return 0;
	return n*((n*T(n,x)-x*U(n-1, x))/(x*x - 1));
}

double d3T(int n,  double x) {
	if (n==0)
		return 0;
	else if (n==1)
		return 0;
	return n*(((n*dT(n,x)-x*dU(n-1, x)-U(n-1, x))*(x*x-1) - (n*T(n, x) - x*U(n-1, x))*2*x)/(x*x*x*x - 2*x*x + 1)); 
}

void make_spl(points_t * pts, spline_t * spl) {
  matrix_t *eqs = NULL;
  double *x = pts->x;
  double *y = pts->y;
  double a = x[0];
  double b = x[pts->n - 1];
  int i, j, k;
  int nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
  char *nbEnv = getenv("APPROX_BASE_SIZE");

  if (nbEnv != NULL && atoi(nbEnv) > 0)
    nb = atoi(nbEnv);

  eqs = make_matrix(nb, nb + 1);
  for (j = 0; j < nb; j++) {
    for (i = 0; i < nb; i++)
      for (k = 0; k < pts->n; k++)
        add_to_entry_matrix(eqs, j, i, T(i, x[k]) * T(j, x[k]));

    for (k = 0; k < pts->n; k++)
      add_to_entry_matrix(eqs, j, nb, y[k] * T(j, x[k]));
  }

  if (piv_ge_solver(eqs)) {
    spl->n = 0;
    return;
  }

  if (alloc_spl(spl, nb) == 0) {
    for (i = 0; i < spl->n; i++) {
      double xx = spl->x[i] = a + i * (b - a) / (spl->n - 1);
      xx += 10.0 * DBL_EPSILON;  //by nie ulokować punktu w poprz. przedziale
      spl->f[i] = 0;
      spl->f1[i] = 0;
      spl->f2[i] = 0;
      spl->f3[i] = 0;
      for (k = 0; k < nb; k++) {
        double ck = get_entry_matrix(eqs, k, nb);
        spl->f[i] += ck * T (k, xx);
        spl->f1[i] += ck * dT (k, xx);
        spl->f2[i] += ck * d2T(k, xx);
        spl->f3[i] += ck * d3T(k, xx);
      }
    }
  }
}

