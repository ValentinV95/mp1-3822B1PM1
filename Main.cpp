#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "Prototypes.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	int action, quan;
	double dx;
	float x;
	printf("Введите аргумент функции: \n");
	scanf_s("%lf", &dx);
	x = float(dx);
	printf("Введите кол-во слагаемых для посчёта: \n");
	scanf_s("%d", &quan);
	printf("Выберите функцию: \n1) sin(x)\n2) cos(x)\n3) ln(x+1)\n4) e^x\n");
	scanf_s("%d", &action);
	switch (action)
	{
	case 1:
	{
		printf("%.10f %.10f \n", sum(slag_sin, x, quan), sin(float(x)));
		printf("%.10f %.10f \n", r_sum(r_slag_sin, x, the_last_of_us(slag_sind, dx, quan), quan), sin(float(x)));
		break;
	}
	case 2:
	{
		printf("%.10f %.10f \n", sum(slag_cos, x, quan), cos(float(x)));
		printf("%.10f %.10f \n", r_sum(r_slag_cos, x, the_last_of_us(slag_cosd, dx, quan), quan), cos(float(x)));
		break;
	}
	case 3:
	{
		printf("%.10f %.10f \n", sum(slag_ln, x, quan), log(float(x)+1));
		printf("%.10f %.10f \n", r_sum(r_slag_ln, x, the_last_of_us(slag_lnd, dx, quan), quan), log(float(x) + 1));
		break;
	}
	case 4:
	{
		printf("%.10f %.10f \n", sum(slag_exp, x, quan), pow(M_E,float(x)));
		printf("%.10f %.10f \n", r_sum(r_slag_exp, x, the_last_of_us(slag_expd, dx, quan), quan), pow(M_E, float(x)));
	}
	}
	return 0;
}