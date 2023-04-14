// lll.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "locale.h"

float sinslg(float prev, int n, float x)
{
	float next;
	if (n == 0) return x;
	else 
	next = ((-1) * x * x * prev) / ((2 * n) * (2 * n + 1));
	return next;
}

float sinslgrev(float next, int n, float x)
{
	float prev;
		prev = (-1)* next * (2 * n) * (2 * n + 1) / (x * x);
	return prev;
}

float cosslg(float prev, int n, float x)
{
	float next;
	if (n == 0) return 1;
	else
		next = ((-1) * (x * x) * prev) / (2 * n * (2 * n - 1));
	return next;
}

float cosslgrev(float next, int n, float x)
{
	float prev;
	prev = ((-1) * next * 2 * n * (2 * n - 1) / (x * x));
	return prev;
}

float lnslg(float prev, int n, float x)
{
	float next;
	if (n == 0) return x;
	else
		next = ((-1) * x * prev * n) / (n + 1);
	return next;
}

float lnslgrev(float next, int n, float x)
{
	float prev;
	prev = ((-1) * next * (n + 1) / (n * x));
	return prev;
}

float expslg(float prev, int n, float x)
{
	float next;
	if (n == 0) return 1;
	else
		next = prev * x / n;
	return next;
}

float expslgrev(float next, int n, float x)
{
	float prev;
	prev = ( next * n / x);
	return prev;
}

float smfn(float x, int n, float(*slg)(float, int, float)) 
{
	float next = 0;
	float sm = 0;
	for (int i = 1; i <= n; i++)
	{
		next = slg(next, i-1, x);
		sm += next;
	}
	return sm;
}

float lastslg(float x, int n, float(*slg)(float, int, float)) 
{
	float last=0;
	float k = 0;
	for (int i = 1; i <= n; i++)
	{
		last = slg(last, i-1, x);
		k = last;
	}
	return k;
}

float smfnrev(float x, int n, float(*slgrev)(float, int, float), float prev)
{
	float sm = 0;
	for (int i = n; i > 0; i--)
	{
		sm += prev;
		prev = slgrev(prev,i-1,x);
	}
	return sm;
}


int main()
{
	int k, o;
	float x;
	float last;
	setlocale(LC_ALL, "Rus");
	printf("Выберите функцию, которую хотите посчитать\n ");
	printf("1 - sin(x)\n ");
	printf("2 - cos(x)\n ");
	printf("3 - ln(x+1)\n ");
	printf("4 - e^x\n ");
	scanf_s("%d", &k);
	printf("Введите число, от которого хотите взять функцию\n ");
	scanf_s("%lf", &x);
	printf("Ввeдите номер слагаемого, до которого будете считать\n ");
	scanf_s("%d", &o);
	if (k == 1)
	{
		printf("%lf ", smfn(x, o, sinslg));
		last = lastslg(x, o, sinslg);
		printf("%lf ", smfnrev(x, o, sinslgrev, last));
		printf("%lf ", sin(x));
	}
	if (k == 2)
	{
		printf("%lf ", smfn(x, o, cosslg));
		last = lastslg(x, o, cosslg);
		printf("%lf ", smfnrev(x, o, cosslgrev, last));
		printf("%lf ", cos(x));
	}
	if (k == 3)
	{
		printf("%lf ", smfn(x, o, lnslg));
		last = lastslg(x, o, lnslg);
		printf("%lf ", smfnrev(x, o, lnslgrev, last));
		printf("%lf ", log(x + 1));
	}
	if (k == 4)
	{
		printf("%lf ", smfn(x, o, expslg));
		last = lastslg(x, o, expslg);
		printf("%lf ", smfnrev(x, o, expslgrev, last));
		printf("%lf ", exp(x));
	}
	
}