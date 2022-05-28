#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//коэффициент при y"
double p(double x)
{
    return 3;
}
//коэффициент при y'
double q(double x)
{
    return - 1 / x;
}
//правая часть уравнения f(x)
double f(double x)
{
    return x + 1;
}
//аналитическое решение для проверки
double correct(double x)
{
    return 0;
}

int main(void)
{
    // погрешность
    double pr = 0;
    int n;
    printf("n = ");
    scanf("%d", &n);
    double a, b;
    printf("a = ");
    scanf("%le", &a);
    printf("b = ");
    scanf("%le", &b);
    // ввод коэффициентов
    double sigma_1, sigma_2, gamma_1, gamma_2, delta_1, delta_2;
    printf("sigma_1 = ");
    scanf("%le", &sigma_1);
    printf("gamma_1 = ");
    scanf("%le", &gamma_1);
    printf("delta_1 = ");
    scanf("%le", &delta_1);
    printf("sigma_2 = ");
    scanf("%le", &sigma_2);
    printf("gamma_2 = ");
    scanf("%le", &gamma_2);
    printf("delta_2 = ");
    scanf("%le", &delta_2);

    double alpha[n], beta[n];
    double h = (b - a) / n;
    double x = a + h;

    alpha[0] = - gamma_1 / (sigma_1 * h - gamma_1);
    beta[0] = delta_1 / (sigma_1 - gamma_1 / h);
    // прогонка
    for (int i = 1; i < n; i++, x += h) {
        // вычисдение прогоночных коэфициентов
        double k_1 = 1 / (h * h) + p(x) / (2 * h);
        double k_2 = 1 / (h * h) - p(x) / (2 * h);
        double k_3 = -2 / (h * h) + q(x);
        alpha[i] = - k_1 / (k_2 * alpha[i - 1] + k_3);
        beta[i] = (f(x) - beta[i - 1] * k_2) / (k_2 * alpha[i - 1] + k_3);
    }
    printf("solution:\n");
    double y = (delta_2 * h + gamma_2 * beta[n - 1]) / (sigma_2 * h + gamma_2 - gamma_2 * alpha[n - 1]);
    printf("x = %.3lf correct = %.3lf y = %.3lf\n", x, correct(x), y);
    // подсчет погрешности
    pr += fabs(y - correct(x));
    // вывод решения системы конечно-разностных уравнений в виде y_next = a_i*y_prev + b_i
    for (int i = n - 1; i >= 0; i--) {
        x -= h;
        y = alpha[i] * y + beta[i];
        pr += fabs(y - correct(x));
        printf("x = %.3lf correct = %.3lf y = %.3lf\n", x, correct(x), y);
    }
    // вывод погрешности
    printf("%.10lf\n", pr / n);
    return 0;
}
