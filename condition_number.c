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
    double **b;
    double **res;
    a = calloc(N, sizeof(double));
    b = calloc(N, sizeof(double));
    res = calloc(N, sizeof(double));
    for (int i = 0; i < N; i++) {
        a[i] = calloc(N, sizeof(double));
        b[i] = calloc(N, sizeof(double));
        res[i] = calloc(N, sizeof(double));
    }
    for (int i = 0; i < N; i++) {
    	res[i][i] = 1;
        for (int j = 0; j < N; j++) {
            scanf("%le", &a[i][j]);
            b[i][j] = a[i][j]; 
        }
    }
    double a_max;
    for (int k = 0; k < N; k++) {
        int i = k;
        a_max = fabs(a[k][k]);
        for (int m = k + 1; m < N; m++) {
            if(fabs(a[m][k]) > a_max)
            {
                i = m;
                a_max = fabs(a[m][k]);
            }
        }
        if (a_max == 0) {
            return 0;
        }
        if (i != k) {
            for (int j = k; j < N; j++) {
                swap(&a[i][j], &a[k][j]);
            }
            for (int j = 0; j < N; j++) {
                swap(&res[i][j], &res[k][j]);
            }
        }
		a_max = a[k][k];
        a[k][k] = 1;  
		 
        for (int j = k + 1; j < N; j++) {
            a[k][j] = a[k][j] / a_max;
        }
        
        for (int j = 0; j < N; j++) {
        	res[k][j] = res[k][j] / a_max;
		}
        
        for (int i = k + 1; i < N; i++) {
            double save_elem = a[i][k];
            a[i][k] = 0;
            if (save_elem != 0) {
                for (int j = k + 1; j < N; j++) {
                    a[i][j] = a[i][j] - save_elem * a[k][j];
                }
            }
            for (int j = 0; j < N; j++) {
                res[i][j] = res[i][j] - save_elem * res[k][j];
			}
        }
    }
    for (int i = N - 1; i > 0; i--) {  
        for (int j = i - 1; j >= 0; j--) {  
            double save_elem = a[j][i] / a[i][i];  
	        for (int k = N - 1; k >= 0; k--) {  
	            a[j][k] = a[j][k] - save_elem * a[i][k];  
	            res[j][k] = res[j][k] - save_elem * res[i][k];  
	        }  
	    }  
	}
    printf("solution:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3lf ", res[i][j]);
        }
        printf("\n");
    }
    
    double norm_1 = 0;
	double cur_1 = 0;  
	for (int i = 0; i < N; i++) {
		cur_1 = 0;
	    for (int j = 0; j < N; j++) {  
            cur_1 += fabs(res[i][j]);
        } 
	    if (cur_1 > norm_1) {
            norm_1 = cur_1;
        }  
    }  
    double norm_2 = 0;
	double cur_2 = 0;  
    for (int i = 0; i < N; i++) {
		cur_2 = 0;
        for (int j = 0; j < N; j++) {  
            cur_2 += fabs(b[i][j]);
        }
	    if (cur_2 > norm_2) {
	        norm_2 = cur_2;
	    }
	}
	printf("condition number:\n");
	printf("%.3lf\n", norm_1 * norm_2); 
	return 0;
}
