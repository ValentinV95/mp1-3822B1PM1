#include <stdio.h>
#include <math.h>

int C = 30000;

double mysin(double x, int i)
{
	double a = x, b = x;
	int j=1;
		a = b = x;
		while (j <= i)
		{
			b = x * x * a / (2 * j * (2 * j + 1));
			a = b;
			j++;
		}
		return pow(-1, j+1) * b;

};

double mycos(double x, int i)
{
	double a = x, b = x;
	int j = 1;
	a = b = 1;
	while (j <= i)
	{
		b = x * x * a / ((2 * j) * (2 * j - 1));
		a = b;
		j++;
	}
	return pow(-1, j+1) * b;

};

double myexp(double x, int i)
{
	double a = x, b = x;
	int j = 1;
	a = b = 1;
	while (j <= i)
	{
		b = x * a / j;
		a = b;
		j++;
	}
	return b;

};

double mylog(double x, int i)
{
	double a = fabs(x), b = fabs(x);
	int j = 1;
	if (i == 0) return x;
	else 
	{
		while (j <= i)
		{
			b = fabs(x) * a * j / (j + 1);
			a = b;
			j++;
		}
		if (x >= 0) return b * pow(-1, j+1);
		else return -b;
	}
};

double mylog2(double z, int i)
{
	double a = (1-z)/(1+z), b = (1 - z) / (1 + z);
	int j = 1;
	if (i == 0) return -2*b;
	{
		while (j <= i)
		{
			b = ((1 - z) / (1 + z)) * ((1 - z) / (1 + z)) * a * (2*j-1) / (2*j + 1);
			a = b;
			j++;
		}
		return -2 * b;
	}
};

double sum1(double(*tmp) (double, int), double x)
{
	double res1=0;
	for (int k = 0; k < C; k++)
	{
		//printf("%.10lf\n", tmp(x, k));
		res1 += tmp (x, k) ;
	}
	return res1;
};

double sum2(double(*tmp) (double, int), double x)
{
	double res1 = 0;
	for (int k = C-1; k > - 1; k--)
	{
		//printf("%.10lf\n", tmp(x, k));
		res1 += tmp(x, k);
	}
	return res1;
};

int main()
{
	double x = 0;
	int c=0;
	while (1) 
	{
		printf("0 - sin(x); 1 - cos(x); 2 - exp(x); 3 - log(1+x), -1<x<=1; 4 - log(z), z>0 { z = (1-x) / (1+x) }\n");
		scanf_s("%d", &c);
		printf("argument\n");
		scanf_s("%lf", &x);
		printf("count of summands\n");
		scanf_s("%d", &C);
		switch (c)
		{
			case 0:
			{
			printf("%.20lf %.20lf %.20lf\n", sin(x), sum1(mysin, x), sum2(mysin, x));
			printf("%.20lf\n%.20lf\n", fabs(sum1(mysin, x) - sin(x)), fabs(sum2(mysin, x) - sin(x)));
			break;
			}
		case 1:
			{
			printf("%.20lf %.20lf %.20lf\n", cos(x), sum1(mycos, x), sum2(mycos, x));
			printf("%.20lf\n%.20lf\n", fabs(sum1(mycos, x) - cos(x)), fabs(sum2(mycos, x) - cos(x)));
			break;
			}
		break;

		case 2:
			{
			printf("%.20lf %.20lf %.20lf\n", exp(x), sum1(myexp, x), sum2(myexp, x));
			printf("%.20lf\n%.20lf\n", fabs(sum1(myexp, x) - exp(x)), fabs(sum2(myexp, x) - exp(x)));
			break;
			}
		case 3:
			{
			printf("%.20lf %.20lf %.20lf\n", log(1 + x), sum1(mylog, x), sum2(mylog, x));
			printf("%.20lf\n%.20lf\n", fabs(sum1(mylog, x) - log(1 + x)), fabs(sum2(mylog, x) - log(1 + x)));
			break;
			}
		
		case 4:
			{
			printf("%.20lf %.20lf %.20lf\n", log(x), sum1(mylog2, x), sum2(mylog2, x));
			printf("%.20lf\n%.20lf\n", fabs(sum1(mylog2, x) - log(x)), fabs(sum2(mylog2, x) - log(x)));
			break;
			}
		}
	}
	
	return 1;
}

