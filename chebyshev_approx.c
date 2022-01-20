#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>

/* x - point to calculate function */
/* n - number of function */
double fi(int n, double x) {
	if(n == 0) return 1;
	if(n == 1) return x;
	return 2 * x * fi(n - 1, x) - fi(n - 2, x);
}

/* first derivative */
double d1fi(int n, double x) {
	if(n == 0) return 1;
	if(n == 1) return x;
	return 2 * x * fi(n - 1, x) + 2 * x * d1fi(n - 1, x) - d1fi(n - 2, x);
}

/* second derivative */
double d2fi(int n, double x) {
	if(n == 0) return 1;
	if(n == 1) return x;
	return 2 * x * d1fi(n - 1, x) + 2 * x * d2fi(n - 1, x) - d2fi(n - 2, x);
}

/* third derivative */
double d3fi(int n, double x) {
	if(n == 0) return 1;
	if(n == 1) return x;
	return 2 * x * d2fi(n - 1, x) + 2 * x * d3fi(n - 1, x) - d3fi(n - 2, x);
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
				add_to_entry_matrix(eqs, j, i, fi(a, b, nb, i, x[k]) * fi(a, b, nb, j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(a, b, nb, j, x[k]));
	}

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i * (b - a) / (spl->n - 1);
			xx += 10.0 * DBL_EPSILON;
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double ck = get_entry_matrix(eqs, k, nb);
				spl->f[i] += ck * fi(a, b, nb, k, xx);
				spl->f1[i] += ck * d1fi(a, b, nb, k, xx);
				spl->f2[i] += ck * d2fi(a, b, nb, k, xx);
				spl->f3[i] += ck * d3fi(a, b, nb, k, xx);
			}
		}
	}
}
