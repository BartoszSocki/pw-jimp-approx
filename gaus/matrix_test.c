#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main() {
	matrix_t* m1 = make_matrix(2, 3);
	put_entry_matrix(m1, 0, 0, 1.0);
	put_entry_matrix(m1, 0, 1, 2.0);
	put_entry_matrix(m1, 0, 2, 3.0);
	put_entry_matrix(m1, 1, 0, 4.0);
	put_entry_matrix(m1, 1, 1, 5.0);
	put_entry_matrix(m1, 1, 2, 6.0);

	puts("macierz:");
	write_matrix(m1, stdout);

	puts("macierz transponowana:");
	matrix_t* m2 = transpose_matrix(m1);
	write_matrix(m2, stdout);

	puts("macierz przekopiowana:");
	matrix_t* m3 = copy_matrix(m2);
	write_matrix(m3, stdout);
	printf("%p != %p\n", m2, m3);

	puts("dodanie wartości 4.0 do [0,0]:");
	add_to_entry_matrix(m3, 0, 0, 4.0);
	write_matrix(m3, stdout);

	puts("dodanie wartości poza dobrym indexem:");
	add_to_entry_matrix(m3, 0, m3->cn, 4.0);
	write_matrix(m3, stdout);

	puts("dodanie wartości poza dobrym indexem:");
	add_to_entry_matrix(m3, m3->rn, 0, 4.0);
	write_matrix(m3, stdout);

	puts("czytani macierzy z pliku:");
	matrix_t* m4 = read_matrix(fopen("macierz1.txt", "r"));
	write_matrix(m4, stdout);

	puts("zamiana wierszy:");
	puts("przed:");
	write_matrix(m2, stdout);
	xchg_rows(m2, 1, 2);
	puts("po:");
	write_matrix(m2, stdout);

	puts("zamiana kolumn:");
	puts("przed:");
	write_matrix(m2, stdout);
	xchg_cols(m2, 1, 0);
	puts("po:");
	write_matrix(m2, stdout);

	puts("mnożenie macierzy:");
	write_matrix(m1, stdout);
	write_matrix(m2, stdout);
	matrix_t* m5 = mull_matrix(m2, m1);
	write_matrix(m5, stdout);

	puts("ge_matrix:");
	write_matrix(m2, stdout);
	matrix_t* m6 = ge_matrix(m2);
	write_matrix(m6, stdout);
	write_matrix(m2, stdout);

	puts("bs_matrix:");
	matrix_t* m7 = make_matrix(2, 3);
	put_entry_matrix(m7, 0, 0, 2);
	put_entry_matrix(m7, 0, 1, 3);
	put_entry_matrix(m7, 0, 2, 10);
	put_entry_matrix(m7, 1, 0, 0);
	put_entry_matrix(m7, 1, 1, 2);
	put_entry_matrix(m7, 1, 2, 3);
	
	write_matrix(m7, stdout);
	bs_matrix(m7);
	write_matrix(m7, stdout);

	puts("pivot_ge_matrix:");
	int* row_iter = malloc(sizeof(*row_iter) * 2);
	row_iter[0] = 0;
	row_iter[1] = 1;
	matrix_t* m8 = make_matrix(2, 3);
	put_entry_matrix(m8, 0, 0, 2);
	put_entry_matrix(m8, 0, 1, 3);
	put_entry_matrix(m8, 0, 2, 10);
	put_entry_matrix(m8, 1, 0, 0);
	put_entry_matrix(m8, 1, 1, 2);
	put_entry_matrix(m8, 1, 2, 3);

	write_matrix(m8, stdout);
	pivot_ge_matrix(m8, row_iter);
	write_matrix(m8, stdout);
}

