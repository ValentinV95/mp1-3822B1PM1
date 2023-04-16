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
	float x, rez1, rez2;
	printf("Введите аргумент функции: \n");
	scanf_s("%f", &x);
	printf("Введите кол-во слагаемых для посчёта: \n");
	scanf_s("%d", &quan);
	printf("Выберите функцию: \n1) sin(x)\n2) cos(x)\n3) ln(x+1)\n4) e^x\n");
	scanf_s("%d", &action);
	switch (action)
	{
	case 1:
	{
		rez1 = sum(slag_sin, x, quan);
		rez2 = r_sum(r_slag_sin, x, the_last_of_us(slag_sin, x, &quan), quan);
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez1, fabsf(rez1- sin(x)), fabsf(rez1 - sin(x))/sinf(x));
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez2, fabsf(rez2 - sin(x)), fabsf(rez2 - sin(x)) / sin(x));
		break;
	}
	case 2:
	{
		rez1 = sum(slag_cos, x, quan);
		rez2 = r_sum(r_slag_cos, x, the_last_of_us(slag_cos, x, &quan), quan);
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez1, fabsf(rez1 - cos(x)), fabsf(rez1 - cos(x)) / cosf(x));
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez2, fabsf(rez2 - cos(x)), fabsf(rez2 - cos(x)) / cos(x));
		break;
	}
	case 3:
	{
		rez1 = sum(slag_ln, x, quan);
		rez2 = r_sum(r_slag_ln, x, the_last_of_us(slag_ln, x, &quan), quan);
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez1, fabsf(rez1 - logf(x + 1.0f)), fabsf(rez1 - log(x + 1.0f)) / log(x + 1.0f));
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez2, fabsf(rez2 - log(x + 1.0f)), fabsf(rez2 - log(x + 1.0f)) / log(x + 1.0f));
		break;
	}
	case 4:
	{
		rez1 = sum(slag_exp, x, quan);
		rez2 = r_sum(r_slag_exp, x, the_last_of_us(slag_exp, x, &quan), quan);
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez1, fabsf(rez1 - powf(M_E, x)), fabsf(rez1 - pow(M_E, x)) / pow(M_E, x));
		printf("Прямое суммирование: %.8f\nАбсолютная погрешность: %.8f \nОтносительная погрешность: %.8f\n", rez2, fabsf(rez2 - pow(M_E, x)), fabsf(rez2 - pow(M_E, x)) / pow(M_E, x));
		break;
	}
	}
	return 0;
}