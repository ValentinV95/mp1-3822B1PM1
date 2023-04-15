#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "locale.h"

float sinslg(float a, int o, float x)
{
    float an;
        an = (-1) * a * x * x / ((2*o+1) * (2*o));
    return an;
}

float sinslgrev(float an, int o, int pos, float x)
{
    float a;
    a =( an * (-1) * ((2*pos-2)*(2*pos-1)) )/ (x * x);
    return a;
}

float cosslg(float a, int o, float x)
{
    float an;
    an = ((-1) * (x * x) * a) / (2 * o * (2 * o - 1));
    return an;
}

float cosslgrev(float an, int o, int pos, float x)
{
    float a;
    a = ((-1) * an *(2*pos-3)* (2*pos-2) / (x * x));
    return a;
}

float expslg(float a, int o, float x)
{
    float an;
    an = a * x / o;
    return an;
}

float expslgrev(float an, int o, int pos, float x)
{
    float a;
    a = (an * (pos-1) / x); 
    return a;
}

float lnslg(float a, int o, float x)
{
    float an;
    an = ((-1) * x * a * o) / (o + 1);
    return an;
}

float lnslgrev(float an, int o, int pos, float x)
{
    float a;
    if (pos == 1)
        a = 0;
    else
        a = ((-1) * an * (pos) / ((pos-1) * x));
    return a;
}

float  smfn(float x, int posl, float ak, float(*sl)(float, int, float))
{
    float sm = ak;
    for (int i = 1; i <= posl; i++)
    {
        ak = sl(ak, i, x);
        sm += ak;
    }
    return sm;
}

float poslslog(float x, int posl, float ak, float(*sl)(float, int, float))
{
    float ai;
    int i = 1; 
    while ((ak != 0) && (i <= posl))
    {
        if (ak >= 0.0000001 || ak <= -0.000001)
            ai = ak;

        ak = sl(ak, i, x);
        i++;
    }
    return ai;
}

int poslnom(float x, int posl, float ak, float(*sl)(float, int, float))
{
    int nomer = 0;
    int i = 1;
    while ((ak != 0) && (i <= posl))
    {
        if (ak >= 0.0000001 || ak <= -0.000001)
            nomer = i;
        ak = sl(ak, i, x);
        i++;
    }
    return nomer;
}
float smfnrvs(float x, int posl, float an, float(*slrvs)(float, int, int, float))
{
    float sm = an;
    for (int i = posl; i >= 1; i--)
    {
        an = slrvs(an, posl, i, x);
        sm += an;
    }
    return sm;
}
int main()
{
    int n, o;
    float x, ak;
    setlocale(LC_ALL, "Rus");
    printf("Выберите функцию, которую хотите посчитать ");
    printf("1 - sin(x) ");
    printf("2 - cos(x) ");
    printf("3 - ln(x+1) ");
    printf("4 - e^x ");
    scanf_s("%d", &n);
    printf("Введите число, от которого хотите взять функцию ");
    scanf_s("%f", &x);
    printf("Ввeдите номер слагаемого, до которого нужно посчитать ");
    scanf_s("%d", &o);
    if (n == 1)
    {
        ak = x;
        printf("Прямой подсчет: %f \n", smfn(x, o, ak, sinslg));
        printf("Обратный подсчет: %f \n", smfnrvs(x, poslnom(x, o, ak, sinslg), poslslog(x, o, ak, sinslg), sinslgrev));
        printf("Встроенная функция: %f\n", sin(x));
    }
    if (n == 2)
    {
        ak = 1;
        printf("Прямой подсчет: %f \n", smfn(x, o, ak, cosslg));
        printf("Обратный подсчет: %f \n", smfnrvs(x, poslnom(x, o, ak, cosslg), poslslog(x, o, ak, cosslg), cosslgrev));
        printf("Встроенная функция: %f\n", cos(x));
    }
    if (n == 3)
    {
        ak = x;
        printf("Прямой подсчет: %f \n", smfn(x, o, ak, lnslg));
        printf("Обратный подсчет: %f \n", smfnrvs(x, poslnom(x, o, ak, lnslg), poslslog(x, o, ak, lnslg), lnslgrev));
        printf("Встроенная функция: %f\n", log(x + 1));
    }
    if (n == 4)
    {
        ak = 1;
        printf("Прямой подсчет: %f \n", smfn(x, o, ak, expslg));
        printf("Обратный подсчет: %f \n", smfnrvs(x, poslnom(x, o, ak, expslg), poslslog(x, o, ak, expslg), expslgrev));
        printf("Встроенная функция: %f\n", exp(x));
    }
    return 0;
}

