#include <stdio.h>
#include <math.h>

int C = 5000000;
double EPS = 1e-100;

double mysin1(double x, double prev, int i)
{
	if (i == 0) return x;
	return -x * x * prev / (2 * i * (2 * i + 1));

};

double mysin2(double x, double prev, int i)
{
	if (i == 0) return x;
	if (x == 0) return 0.0; 
	else return -prev * (2 * i * (2 * i + 1)) / x / x;
};


double mycos1(double x, double prev, int i)
{
	if (i == 0) return 1.0;
	return -x * x * prev / (2 * i * (2 * i - 1));
};

double mycos2(double x, double prev, int i)
{
	if (i == 0) return 1.0;
	if (x == 0) return 0.0;
	else return -prev * (2 * i * (2 * i - 1)) / x / x;
};


double myexp1(double x, double prev, int i)
{
	if (i == 0) return 1.0;
	if (x == 0) return 0.0;
	else return x * prev / i;
};

double myexp2(double x, double prev, int i)
{
	if (i == 0) return 1.0;
	if (x == 0) return 0.0;
	else return i * prev / x;
};

double mylog1(double x, double prev, int i)
{
	if (i == 0) { return x; }
	return -x * prev * i / (i + 1);
};

double mylog2(double x, double prev, int i)
{
	if (i == 0) { return x; }
	if (x == 0) return 0;
	else return -prev / i * (i + 1) / x;
};

double reallog1(double z, double prev, int i)
{
	if (z <= 0) return -INFINITY;
	if (i == 0) return -2 * (1 - z) / (1 + z);
	return prev*(1 - z) / (1 + z) * (1 - z) / (1 + z) * (2 * i - 1) / (2 * i + 1);
};

double reallog2(double z, double prev, int i)
{
	if (z <= 0) return -INFINITY;
	if (i == 0) return -2 * (1 - z) / (1 + z);
	return prev / ((1 - z) / (1 + z)) / ((1 - z) / (1 + z)) / (2 * i - 1) * (2 * i + 1);
};

double sum1(double(*fun1) (double, double, int), double x)
{
	double res1 = 1, res=0;
	for (int k = 0; k < C; k++)
	{
		res1 = fun1(x, res1, k);
		if (fabs(res1) < EPS) break;
		res += res1;
	}
	return res;
};

double sum2(double(*fun1) (double, double, int), double(*fun2) (double, double, int), double x)
{
	double res1 = 1, tmp=1, res = 0;
	int k = 0;
	while (k<C)
	{
		tmp = fun1(x, res1, k);
		if (fabs(tmp) < EPS) break;
		res1 = tmp;
		k++;
	}
	res += res1;
	for(int j = k - 1; j > 0; j--)
	{
		res1 = fun2(x, res1, j);
		res += res1;
	}
	return res;
};

int main()
{
	double x = 0;
	int c = 0;
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
				printf("%.20lf %.20lf %.20lf\n", sin(x), sum1(mysin1, x), sum2(mysin1, mysin2, x));
				printf("%.20lf\n%.20lf\n", fabs(fabs(sum1(mysin1, x)) - fabs(sin(x))), fabs(fabs(sum2(mysin1, mysin2, x)) - fabs(sin(x))));
				break;
			}
			case 1:
			{
				printf("%.20lf %.20lf %.20lf\n", cos(x), sum1(mycos1, x), sum2(mycos1, mycos2, x));
				printf("%.20lf\n%.20lf\n", fabs(fabs(sum1(mycos1, x)) - fabs(cos(x))), fabs(fabs(sum2(mycos1, mycos2, x)) - fabs(cos(x))));
				break;
			}
			break;

			case 2:
			{
				printf("%.20lf %.20lf %.20lf\n", exp(x), sum1(myexp1, x), sum2(myexp1, myexp2, x));
				printf("%.20lf\n%.20lf\n", fabs(fabs(sum1(myexp1, x)) - fabs(exp(x))), fabs(fabs(sum2(myexp1, myexp2, x)) - fabs(exp(x))));
				break;
			}

			case 3:
			{
				printf("%.20lf %.20lf %.20lf\n", log(1 + x), sum1(mylog1, x), sum2(mylog1, mylog2, x));
				printf("%.20lf\n%.20lf\n", fabs(fabs(sum1(mylog1, x)) - fabs(log(1 + x))), fabs(fabs(sum2(mylog1, mylog2, x)) - fabs(log(1 + x))));
				break;
			}

			case 4:
			{
				printf("%.20lf %.20lf %.20lf\n", log(x), sum1(reallog1, x), sum2(reallog1, reallog2, x));
				printf("%.20lf\n%.20lf\n", fabs(fabs(sum1(reallog1, x)) - fabs(log(x))), fabs(fabs(sum2(reallog1, reallog2, x)) - fabs(log(x))));
				break;
			}
		}
	}

	return 1;
}