#include "piv_ge_solver.h"
#include <stdlib.h>

/* this function solves equations */
/* return zero when everything goes fine */
int piv_ge_solver(matrix_t * eqs)
{
	if (eqs != NULL) {
		pivot_ge_in_situ_matrix(eqs);
		if (bs_matrix(eqs) == 0) {
			return 0;
		} else {
			return 1;
		}
	} else
		return 1;
}
