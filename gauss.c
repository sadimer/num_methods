#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
void
swap (double *a, double *b) 
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
double 
**fill_matrix(double **a, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i != j) {
				a[i][j] = (i + j + 2) / (N + M);
			} else {
				a[i][j] = N + M * M + (j + 1) / M + (i + 1) / N;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		a[i][N] = 200 + 50 * (i + 1);
	}
	return a;
}
int
main (void)
{
    int N, M;
    printf("mode = ");
    // s - стандартный, g - с выбором главного элемента
    char c;
    scanf("%c", &c);
    printf("mode matrix = ");
    // 1 - ввод матрицы с калвиатуры, 2 - матрица заданная функционально
    int mc;
    scanf("%d", &mc);
    double **a;
    if (mc == 1) {
    	printf("size = ");
    	scanf("%d", &N);
    	a = calloc(N, sizeof(double));
    	for (int i = 0; i < N; i++) {
        	a[i] = calloc(N + 1, sizeof(double));
    	}
    	printf("matrix:\n");
    	for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N + 1; j++) {
            	scanf("%le", &a[i][j]);
        	}
    	}
    } else if (mc == 2) {
    	N = 20;
    	M = 8;
    	a = calloc(N, sizeof(double));
    	for (int i = 0; i < N; i++) {
        	a[i] = calloc(N + 1, sizeof(double));
    	}
    	a = fill_matrix(a, N, M);
	}
    if (c == 'g') {
    	double a_max = 0;
    	// поиск максимального "ведущего" элемента
    	for (int k = 0; k < N; k++) {
        	int i = k;
        	a_max = fabs(a[k][k]);
        	for (int m = k + 1; m < N; m++) {
            	if(fabs(a[m][k]) > a_max) {
                	i = m;
                	a_max = fabs(a[m][k]);
            	}
        	}
        	// проверка на вырожденность матрицы
        	if (a_max == 0) {
            	printf("No solutions!\n");
            	return 0;
        	}
        	// перестановка строк
        	if (i != k) {
            	for (int j = k; j < N + 1; j++) {
                	swap(&a[i][j], &a[k][j]);
            	}
        	}
        	// преобразования коэфициентов (деление на ведущий)
        	a_max = a[k][k];
        	a[k][k] = 1;  
         
        	for (int j = k + 1; j < N + 1; j++) {
            	a[k][j] = a[k][j] / a_max;
        	}
        	// дальнейшее вычитание строки
        	for (int i = k + 1; i < N; i++) {
            	double save_elem = a[i][k];
            	a[i][k] = 0;
            	if (save_elem != 0) {
                	for (int j = k + 1; j < N + 1; j++) {
                 	   a[i][j] = a[i][j] - save_elem * a[k][j];
                	}
            	}
        	}
    	}
    } else if (c == 's') {
    	double a_base = 0;
    	// поиск первого ненулевого элемента
    	for (int k = 0; k < N; k++) {
        	int i = k;
        	a_base = fabs(a[k][k]);
        	for (int m = k + 1; a_base == 0 && m < N; m++) {
            	a_base = fabs(a[m][k]);
        	}
        	// далее все аналогично...
        	if (a_base == 0) {
            	printf("No solutions!\n");
            	return 0;
        	}
        	if (i != k) {
            	for (int j = k; j < N + 1; j++) {
                	swap(&a[i][j], &a[k][j]);
            	}
        	}
        	a_base = a[k][k];
        	a[k][k] = 1;  
         
        	for (int j = k + 1; j < N + 1; j++) {
            	a[k][j] = a[k][j] / a_base;
        	}
        
        	for (int i = k + 1; i < N; i++) {
            	double save_elem = a[i][k];
            	a[i][k] = 0;
            	if (save_elem != 0) {
                	for (int j = k + 1; j < N + 1; j++) {
                 	   a[i][j] = a[i][j] - save_elem * a[k][j];
                	}
            	}
        	}
    	}
	}
	// обратный ход
    double *x = calloc(N + 1, sizeof(double));
    for (int i = N - 1; i >= 0; i--) {
        x[i] = 0;
        double a_tmp = a[i][N];
        for (int j = N; j > i; j--) {
            a_tmp = a_tmp - a[i][j] * x[j];
        }
        x[i] = a_tmp;
    }
 
    
    printf("solution:\n");
    for (int i = 0; i < N ; i++) {
        printf("x[%d] = %.10lf\n", i + 1, x[i]);
    }
    return 0;
}
