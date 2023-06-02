#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float pr_sin(int n, float x, float ai) //вычисляет синус (прямая сумма)
{
	float sum;
	if (n == 0)
	{
		return x;
	}
	sum = ((-1) * (x * x) / (2 * n * (2 * n + 1))) * ai;
	return sum;
}
float ob_sin(int n, float x, float ai) //вычисляет синус (обратная сумма)
{
	float sum;
	sum = (2 * n * (2 * n + 1)) / ((-1) * (x * x)) * ai;
	return sum;
}
float pr_cos(int n, float x, float ai) //вычисляет косинус (прямая сумма)
{
	float sum;
	if (n == 0)
	{
		return 1;
	}
	sum = ((-1) * (x * x) / (2 * n * (2 * n - 1))) * ai;
	return sum;
}
float ob_cos(int n, float x, float ai) //вычисляет косинус (обратная сумма)
{
	float sum;
	sum = (2 * n * (2 * n - 1)) / ((-1) * (x * x)) * ai;
	return sum;
}
float pr_ln(int n, float x, float ai) //вычисляет ln(1+x) (прямая сумма)
{
	float sum;
	if (n == 0)
	{
		return x;
	}
	sum = ((-1) * (x * n) / (n + 1)) * ai;
	return sum;
}
float ob_ln(int n, float x, float ai) //вычисляет ln(1+x) (обратная сумма)
{
	float sum;
	if (n == 0)
	{
		return 0;
	}
	sum = ((-1) * (n + 1) / (x * n)) * ai;
	return sum;
}
float pr_ex(int n, float x, float ai)//вычисляет e^x(прямая сумма)
{
	float sum;
	if (n == 0)
	{
		return 1;
	}
	sum = (x / n) * ai;
	return sum;
}
float ob_ex(int n, float x, float ai) //вычисляет e^x(обратная сумма)
{
	float sum;
	sum = (n / x) * ai;
	return sum;
}
float sum(float(*fun)(int, float, float), int n, float x)
{
	float sum = 0, ai = 0;
	for (int i = 0; i < n; i++)
	{
		sum += fun(i, x, ai);
		ai = fun(i, x, ai);
	}
	return sum;
}
float reversesum(float(*fun1)(int, float, float), float(*fun2)(int, float, float), int n, float x)
{
	float sum = 0.0, ai = 0.0, aj = 0.0;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		ai = fun2(i, x, ai);
		if ((fabs(ai) - (3.4e-34)) < 0)
		{
			ai = aj;
			k = i;
			break;
		}
		aj = ai;
		k = i+1;
	}
	sum += ai;
	for (int i = k-1; i >= 0; i--)
	{
		sum += fun1(i, x, ai);
		ai = fun1(i, x, ai);
	}
	return sum;
}