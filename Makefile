chebyshev: main.o splines.o points.o chebyshev_approx.o gaus/libge.a
	$(CC) -o chebyshev main.o splines.o points.o chebyshev_approx.o -L gaus -l ge 

aprox: main.o splines.o points.o aproksymator_na_bazie.o gaus/libge.a
	$(CC) -o aprox  main.o splines.o points.o aproksymator_na_bazie.o -L gaus -l ge

intrp: main.o splines.o points.o interpolator.o gaus/libge.a
	$(CC) -o intrp  main.o splines.o points.o interpolator.o -L gaus -l ge

prosta: main.o splines.o points.o prosta.o
	$(CC) -o prosta  main.o splines.o points.o prosta.o	

aproksymator_na_bazie.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c aproksymator_na_bazie.c

chebyshev_approx.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c chebyshev_approx.c

interpolator.o: makespl.h points.h gaus/piv_ge_solver.h
	$(CC) -I gaus -c interpolator.c

tests: 
	./test/gen 30 5 6 test/dane.1 1
	./test/gen 80 -15 15 test/dane.2 2
	./test/gen 35 0 12 test/dane.3 3
	./test/gen 40 0 6 test/dane.4 4
	./test/gen 50 0 10 test/dane.5 5
	./test/gen 44 -1 2 test/dane.6 6
	./test/gen 60 7 8 test/dane.7 7
	./test/gen 70 10 20 test/dane.8 8
	./test/gen 50 -5 5 test/dane.9 9
	./test/gen 40 0 2 test/dane.10 10
	./chebyshev -s spl1 -p test/dane.1 -g plot1 -f 5.1 -t 5.7 -n 300
	./chebyshev -s spl2 -p test/dane.2 -g plot2 -f -10 -t 10 -n 300
	./chebyshev -s spl3 -p test/dane.3 -g plot3 -f 0 -t 5 -n 200
	./chebyshev -s spl4 -p test/dane.4 -g plot4 -f 1 -t 4 -n 300
	./chebyshev -s spl5 -p test/dane.5 -g plot5 -f 0 -t 10 -n 300
	./chebyshev -s spl6 -p test/dane.6 -g plot6 -f -1 -t 2 -n 300
	./chebyshev -s spl7 -p test/dane.7 -g plot7 -f 7.1 -t 7.5 -n 300
	./chebyshev -s spl8 -p test/dane.8 -g plot8 -f 11.3 -t 14 -n 300
	./chebyshev -s spl9 -p test/dane.9 -g plot9 -f -4.2 -t 4.2 -n 300
	./chebyshev -s spl10 -p test/dane.10 -g plot10 -f 0 -t 1 -n 300


.PHONY: clean

clean:
	-rm *.o aprox intrp prosta chebyshev
