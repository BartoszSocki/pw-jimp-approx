#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>

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
	return n*U(n-1, x);
}

double dU(int n, double x){
	return ((n+1)*T(n+1, x) - x*U(n, x))/(x*x - 1);

double d2T(int n, double x) {
	return n*((n*T(n,x)-x*U(n-1, x))/(x*x - 1));
}

double d3T(double a, double b, int n, int i, double x) {
	return n*(((n*dT(n,x)-x*dU(n-1, x)-U(n-1, x))*(x*x-1) - (n*T(n, x) - x*U(n-1, x))*2*x)/(x*x*x*x - 2*x*x + 1)); 
}

void make_spl(points_t * pts, spline_t * spl) {

}

