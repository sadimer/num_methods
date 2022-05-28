#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
double*
next_iteration(double *x_prev, double *x_cur, double w, double *b, int N, double **a) 
{
    for (int i = 1; i <= N; i++){
        double s1 = 0;
        double s2 = 0;
        for (int j = 1; j <= i - 1;  j++){
            s1 += a[i][j] / a[i][i] * x_cur[j] * w;
        }
        for (int j = i; j <= N; j++){
            s2 += a[i][j] / a[i][i] * x_prev[j] * w;
        }
        x_cur[i] = b[i] / a[i][i] * w - s1 - s2 + x_prev[i];
    }
    return x_cur;   
}
long long iter = 0;
int 
main(void)
{
    int N, M;
    double w;
    double eps;
    printf("size = ");
    scanf("%d", &N);
    //N = 20;
    //M = 10;
    printf("eps = ");
    scanf("%le", &eps);
    printf("w = ");
    scanf("%le", &w);
    printf("matrix:\n");
    double **a;
    a = calloc(N, sizeof(double));
    for (int i = 0; i < N + 1; i++) {
        a[i] = calloc(N + 1, sizeof(double));
    }
    double *b;
    b = calloc(N + 1, sizeof(double));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
        	scanf("%le", &a[i][j]);
            /*if (i != j) {
				a[i][j] = (i + j) / (N + M);
			} else {
				a[i][j] = N + M * M + j / M + i / N;
			}*/
        }
        scanf("%le", &b[i]);
        //b[i] = 200 + 50 * i;
    }
    double *x_cur, *x_prev;
    x_cur = calloc(N + 1, sizeof(double));
    x_prev = calloc(N + 1, sizeof(double));
    int stop = 0;
    while (1) {
    	// x(i) = x(i+1)
        for (int i = 1; i <= N; i++) {
            x_prev[i] = x_cur[i];
        }
        // вызов функции следующей итерации
        x_cur = next_iteration(x_prev, x_cur, w, b, N, a);
        iter++;
        // условие остановки
        for (int i = 1; i <= N; i++) {
            if (fabs(x_prev[i] - x_cur[i]) >= eps) {
                stop = 0;
                break;
            } else {
                stop = 1;
            }
        }
        if (stop == 1) {
            break;
        }
    }
    printf("solution:\n");
    for (int i = 1; i < N + 1; i++) {
        printf("x[%d] = %.10lf\n", i, x_cur[i]);
    }
    printf("iterations:\n");
    printf("%d\n", iter);
}
