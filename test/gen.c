#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double fun1(double x){
	double r10 = ((double)rand() - RAND_MAX/2.0)/RAND_MAX/5; // +-10%
	return (1+r10)*(10*x*x*x*x+5*x*x*x+x*x);
}

double fun2(double x){
	double r25 = ((double)rand() - RAND_MAX/2.0)/RAND_MAX/2; // +- 25%
	return (1+r25)*(sin(x));
}

double fun3(double x){
	double r5 = ((double)rand() - RAND_MAX/2.0)/RAND_MAX/10; // +- 5%
	return (1+r5)*x;
}

double fun4(double x){
	double r10 = ((double)rand() - RAND_MAX/2.0)/RAND_MAX/5; // +-10%
	return (1+r10)*(4*x*x*x - 3*x);
}

double fun5(double x){
	double r25 = ((double)rand() - RAND_MAX/2.0)/RAND_MAX/2; // +- 25%
	return (1+r25)*cos(5*x);
}

int main( int argc, char **argv ) {
	int n = argc > 1 ? atoi( argv[1] ) : 100; //number of points
	double a = argc > 2 ? atof( argv[2] ) : -3; //range
	double b = argc > 3 ? atof( argv[3] ) : 2;
	FILE *out = argc > 4 ? fopen( argv[4], "w" ) : stdout; //file to write data
	int f = argc > 5 ? atoi( argv[5] ) : 1; //which function
	srand( argc > 6 ? atoi(argv[6]) : time(NULL) ); //seed

	int i;
	double dx = (b-a)/(n-1);
	for( i=0; i<n; i++ ){
		if (f == 1)
			fprintf( out, "%g %g\n", a+i*dx, fun1(a+i*dx) );
		else if (f == 2)
			fprintf( out, "%g %g\n", a+i*dx, fun2(a+i*dx) );
		else if (f == 3)
			fprintf( out, "%g %g\n", a+i*dx, fun3(a+i*dx) );
		else if (f == 4)
			fprintf( out, "%g %g\n", a+i*dx, fun4(a+i*dx) );
		else
			fprintf( out, "%g %g\n", a+i*dx, fun5(a+i*dx) );

	}

	fclose( out );

	return 0;
}
