#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "locale.h"

double sinslg(double a, int o, double x)
{
    double an;
    int q;
    for (int n = 1; n <= o; n++)
    {
        q = pow(-1, o);
        an = q * (x * x) * a / ((2 * n) * (2 * n + 1));
        a = an;
    }
    return an;
}

double sinslgrev(double an, int o, int pos, double x)
{
    double a;
    int q;
    for (int n = o; n >= pos; n--)
    {
        if (o % 2 == 0)
            q = pow(-1, (o + 1));
        else
            q = pow(-1, o);
        a = q * an * (2 * n) * (2 * n + 1) / (x * x);
        an = a;
    }
    return a;
}

double cosslg(double a, int o, double x)
{
    double an;
    int q;
    for (int n = 1; n <= o; n++)
    {
        q = pow(-1, o);
        an = q * (x * x) * a / (2 * n * (2 * n - 1));
        a = an;
    }
    return an;
}

double cosslgrev(double an, int o, int pos, double x)
{
    double a;
    int q;
    for (int n = o; n >= pos; n--)
    {
        if (o % 2 == 0)
            q = pow(-1, (o + 1));
        else
            q = pow(-1, o);
        a = q * an * 2 * n * (2 * n - 1) / (x * x);
        an = a;
    }
    return a;
}

double expslg(double a, int o, double x)
{
    double an;
    for (int n = 1; n <= o; n++)
    {
        an = x * a / n;
        a = an;
    }
    return an;
}

double expslgrev(double an, int o, int pos, double x)
{
    double a;
    for (int n = o; n >= pos; n--)
    {
        a = an * n / x;
        an = a;
    }
    return a;
}

double lnslg(double a, int o, double x)
{
    double an;
    int q;
    for (int n = 1; n <= o; n++)
    {
        q = pow(-1, (o));
        an = q * x * a * n / (n + 1);
        a = an;
    }
    return an;
}

double lnslgrev(double an, int o, int pos, double x)
{
    double a;
    int q;
    for (int n = o; n >= pos; n--)
    {
        if (o % 2 == 0)
            q = pow(-1, (o + 1));
        else
            q = pow(-1, o);
        a = q * an * (n + 1) / (n * x);
        an = a;
    }
    return a;
}

double smfn(double x, int posl, double ak, double(*sl)(double, int, double))
{
    double sm = ak;
    for (int i = 1; i <= posl; i++)
        sm += sl(ak, i, x);
    return sm;
}

double smfnrvs(double x, int posl, double an, double(*slrvs)(double, int, int, double))
{
    double sm = an;
    for (int i = posl; i >= 1; i--)
        sm += slrvs(an, posl, i, x);
    return sm;
}
int main()
{
    int n, o;
    double x, ak;
    setlocale(LC_ALL, "Rus");
    printf("Выберите функцию, которую хотите посчитать ");
    printf("1 - sin(x) ");
    printf("2 - cos(x) ");
    printf("3 - ln(x+1) ");
    printf("4 - e^x ");
    scanf_s("%d", &n);
    printf("Введите число, от которого хотите взять функцию ");
    scanf_s("%lf", &x);
    printf("Ввeдите номер слагаемого, до которого нужно посчитать ");
    scanf_s("%d", &o);
    if (n == 1)
    {
        ak = x;
        printf("Прямой подсчет: %lf \n", smfn(x, o, ak, sinslg));
        printf("Обратный подсчет: %lf \n", smfnrvs(x, o, sinslg(ak, o, x), sinslgrev));
        printf("Встроенная функция: %lf\n", sin(x));
    }
    if (n == 2)
    {
        ak = 1;
        printf("Прямой подсчет: %lf \n", smfn(x, o, ak, cosslg));
        printf("Обратный подсчет: %lf \n", smfnrvs(x, o, cosslg(ak, o, x), cosslgrev));
        printf("Встроенная функция: %lf\n", cos(x));
    }
    if (n == 3)
    {
        ak = x;
        printf("Прямой подсчет: %lf \n", smfn(x, o, ak, lnslg));
        printf("Обратный подсчет: %lf \n", smfnrvs(x, o, lnslg(ak, o, x), lnslgrev));
        printf("Встроенная функция: %lf\n", log(x + 1));
    }
    if (n == 4)
    {
        ak = 1;
        printf("Прямой подсчет: %lf \n", smfn(x, o, ak, expslg));
        printf("Обратный подсчет: %lf \n", smfnrvs(x, o, expslg(ak, o, x), expslgrev));
        printf("Встроенная функция: %lf\n", exp(x));
    }
    return 0;
}

