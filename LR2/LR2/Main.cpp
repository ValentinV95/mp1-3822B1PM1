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
	float x;
	printf("Ââåäèòå àðãóìåíò ôóíêöèè: \n");
	scanf_s("%f", &x);
	printf("Ââåäèòå êîë-âî ñëàãàåìûõ äëÿ ïîñ÷¸òà: \n");
	scanf_s("%d", &quan);
	printf("Âûáåðèòå ôóíêöèþ: \n1) sin(x)\n2) cos(x)\n3) ln(x+1)\n4) e^x\n");
	scanf_s("%d", &action);
	switch (action)
	{
	case 1:
	{
		printf("%.10f %.10f \n", sum(slag_sin, x, quan), sin(x));
		printf("%.10f %.10f \n", r_sum(r_slag_sin, x, the_last_of_us(slag_sin, x, &quan), quan), sinf(x));
		break;
	}
	case 2:
	{
		printf("%.10f %.10f \n", sum(slag_cos, x, quan), cos(x));
		printf("%.10f %.10f \n", r_sum(r_slag_cos, x, the_last_of_us(slag_cos, x, &quan), quan), cosf(x));
		break;
	}
	case 3:
	{
		printf("%.10f %.10f \n", sum(slag_ln, x, quan), log(x + 1.0f));
		printf("%.10f %.10f \n", r_sum(r_slag_ln, x, the_last_of_us(slag_ln, x, &quan), quan), logf(x + 1.0f));
		break;
	}
	case 4:
	{
		printf("%.10f %.10f \n", sum(slag_exp, x, quan), pow(M_E,x));
		printf("%.10f %.10f \n", r_sum(r_slag_exp, x, the_last_of_us(slag_exp, x, &quan), quan), powf(M_E, x));
	}
	}
	return 0;
}
