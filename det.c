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

int
main (void)
{
    int N;
    printf("size = ");
    scanf("%d", &N);
    printf("matrix:\n");
    double **a;
    a = calloc(N, sizeof(double));
    for (int i = 0; i < N; i++) {
        a[i] = calloc(N, sizeof(double));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%le", &a[i][j]);
        }
    }
    double det = 1;
    double a_max;
    for (int k = 0; k < N; k++) {
        int i = k;
        a_max = fabs(a[k][k]);
        int sign;
        if (a[k][k] > 0) {
        	sign = 1;
		} else {
			sign = -1;
		}
        for (int m = k + 1; m < N; m++) {
            if(fabs(a[m][k]) > a_max)
            {
            	if (a[m][k] > 0) {
        			sign = 1;
				} else {
					sign = -1;
				}
                i = m;
                a_max = fabs(a[m][k]);
            }
        }
        if (a_max == 0) {
        	printf("det:\n");
            printf("0\n");
            return 0;
        }
        if (i != k) {
        	sign *= -1;
            for (int j = k; j < N; j++)
            {
                swap(&a[i][j], &a[k][j]);
            }
        }
        a_max = a[k][k];
        a[k][k] = 1;  
         
        for (int j = k + 1; j < N; j++) {
            a[k][j] = a[k][j] / a_max;
        }
        det *= a_max;
        det *= sign;
        
        for (int i = k + 1; i < N; i++) {
            double save_elem = a[i][k];
            a[i][k] = 0;
            if (save_elem != 0) {
                a[i][k] = 0;
                for (int j = k + 1; j < N; j++) {
                    a[i][j] = a[i][j] - save_elem * a[k][j];
                }
            }
        }
    }
	printf("det:\n");
    printf("%.10lf\n", det);
	return 0;
}
