#include "Prototypes.h"
double slag_sind(double prev, double x, int n)
{
	if (n == 0) return x;
	else return (-1) * (prev * x * x) / (2 * n * (2 * n + 1));
}
double slag_cosd(double prev, double x, int n)
{
	if (n == 0) return 1;
	else return (-1) * (prev * x * x) / (2 * n * (2 * n - 1));
}
double slag_lnd(double prev, double x, int n)
{
	if (n == 0) return x;
	else return (-1) * (prev * x * n) / (n + 1);
}
double slag_expd(double prev, double x, int n)
{
	if (n == 0) return 1;
	else return (prev * x) / n;
}
float r_slag_sin(float last, float x, int n)
{
	return (-1) * (last * 2 * n * (2 * n + 1)) / (x * x);
}
float r_slag_cos(float prev, float x, int n)
{
	return (-1) * (prev * 2 * n * (2 * n - 1)) / (x * x);
}
float r_slag_ln(float prev, float x, int n)
{
	return (-1) * (prev * (n + 1)) / (x * n);
}
float r_slag_exp(float prev, float x, int n)
{
	return (prev * n) / x;
}
float slag_sin(float prev, float x, int n)
{
	if (n == 0) return x;
	else return (-1) * (prev * x * x) / (2 * n * (2 * n + 1));
}
float slag_cos(float prev, float x, int n)
{
	if (n == 0) return 1;
	else return (-1) * (prev * x * x) / (2 * n * (2 * n - 1));
}
float slag_ln(float prev, float x, int n)
{
	if (n == 0) return x;
	else return (-1) * (prev * x * n) / (n + 1);
}
float slag_exp(float prev, float x, int n)
{
	if (n == 0) return 1;
	else return (prev * x) / n;
}