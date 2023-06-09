#include "stdio.h"
#include "math.h"
#include "locale.h"


float sin_pr(float x, float fel, int ind) {
	fel *= (-1) * x * x / (2 * ind * (2 * ind + 1));
	return fel;
}

float cos_pr(float x, float fel, int ind) {
	fel *= (-1) * x * x / (2 * ind * (2 * ind - 1));
	return fel;
}

float log_pr(float x, float fel, int ind) {
	fel *= (-1) * x * ind / (ind + 1);
	return fel;
}

float exp_pr(float x, float fel, int ind) {
	fel *= x / ind;
	return fel;
}

//обратная сумма
float sin_ob(float x, float fel, int ind) {
	fel = -fel * (2 * ind) * (2 * ind + 1) / (x * x);
	return fel;
}

float cos_ob(float x, float fel, int ind) {
	fel = -fel * (2 * ind) * (2 * ind - 1) / (x * x);
	return fel;
}

float log_ob(float x, float fel, int ind) {
	if (ind == 0) return 0;
	if (ind == 1) return 0;
	fel = -fel * ind / (x * (ind - 1));
	return fel;
}

float exp_ob(float x, float fel, int ind) {
	fel = fel * ind / x;
	return fel;
}


float summ(float suma, float(*fun)(float, float, int), float x, float fel) {
	suma += fel;
	for (int i = 1; i < 100; i++) {
		fel = fun(x, fel, i);
		suma += fel; }
	return suma;
}


float summ_ob(float suma, float(*fun)(float, float, int), float x, float fel, float n) {
	suma += fel;
	for (int i = n; i > -1; i--) {
		fel = fun(x, fel, i);
		suma += fel;}
	return suma;
}

int main() {

	setlocale(LC_ALL, "Russian");
	float x;

	int a;
	int j;

	float minuss; //эпсилон
	float sinp = 0, cosp = 0, lnp = 0, expp = 0; //прямой счёт
	float sino = 0, coso = 0, lno = 0, expo = 0; //обратный счёт
	float sin_can = 0, cos_can = 0, ln_can = 0, exp_can = 0; //канон
	float fel; //первый элемент
	float lel; //последний элемент

	float eps = pow(10, -15);

	printf("Введите значение х: ");
	scanf_s("%f", &x);
	printf("\n");

	printf("Выберите функцию:\n 1. sin(x)\n 2. cos(x)\n 3. ln(1+x)\n 4. e^x\n");
	scanf_s("%i", &a);
	printf("\n");
	
	switch (a) {
	case 1: //sinx
		fel = x;
		sinp = summ(sinp, sin_pr, x, fel);
		sin_can = sin(x);
		printf("sin(x) = %.9f\n", sinp);
		//
		lel = 1;
		for (j = 1; j < 101; j++) {
			if (fabsf(fel) - eps < 0) break;
			fel = sin_pr(x, fel, j);
		}
		sino = summ_ob(sino, sin_ob, x, fel, j-1);
		printf("Обратный sin(x) = %.9f\n", sino);
		//
		printf("Канонический sin(x) = %.9lf\n\n", sin_can);
		printf("Абсолютная погрешность прямой суммы: %.9f\n", fabsf(sin_can - sinp));
		printf("Абсолютная погрешность обратной суммы: %.9f\n", fabsf(sin_can - sino));
		break;
	case 2: //cosx
		fel = 1;
		cosp = summ(cosp, cos_pr, x, fel);
		cos_can = cos(x);
		printf("cos(x) = %.9f\n", cosp);
		//
		lel = 1;
		for (j = 1; j < 100; j++) {
			if (fabsf(fel) - eps < 0) break;
			fel = cos_pr(x, fel, j);
		}
		coso = summ_ob(coso, cos_ob, x, fel, j-1);
		printf("Обратный cos(x) = %.9f\n", coso);
		//
		printf("Канонический cos(x) = %.9f\n\n", cos_can);
		printf("Абсолютная погрешность прямой суммы: %.9f\n", fabsf(cos_can - cosp));
		printf("Абсолютная погрешность обратной суммы: %.9f\n", fabsf(cos_can - coso));
		break;
	case 3: //ln(1+x)
		if ((x > -1) && (x <= 1)) {
			fel = x;
			lnp = summ(lnp, log_pr, x, fel);
			ln_can = log(1 + x);
			printf("ln(x+1) = %.9f\n", lnp);
			//
			lel = 1;
			for (j = 1; j < 101; j++) {
				if (fabsf(fel) - eps < 0) break;
				fel = log_pr(x, fel, j);
			}
			lno = summ_ob(lno, log_ob, x, fel, j);
			printf("Обратная ln(1+x): %.9f\n", lno);
			//
			printf("Канонический ln(x+1) = %.9f\n\n", ln_can);
			printf("Абсолютная погрешность прямой суммы: %.9f\n", fabsf(ln_can - lnp));
			printf("Абсолютная погрешность обратной суммы: %.9f\n", fabsf(ln_can - lno));
		}
		else
			printf("Недопустимые значения для ln(1+x)\n\n");
		break;
	case 4: //exp^x
		fel = 1;
		expp = summ(expp, exp_pr, x, fel);
		exp_can = exp(x);
		printf("exp^x = %.9f\n", expp);
		//
		for (j = 1; j < 101; j++) { 
			if (fabsf(fel) - eps < 0) break;
			fel = exp_pr(x, fel, j);;
		}
		expo = summ_ob(expo, exp_ob, x, fel, j-1);
		printf("Обратная exp^x: %.9f\n", expo);
		//
		printf("Каноническая exp^x = %.9f\n\n", exp_can);
		printf("Абсолютная погрешность прямой суммы: %.9f\n", fabsf(exp_can - expp));
		printf("Абсолютная погрешность обратной суммы: %.9f\n", fabsf(exp_can - expo));
		break;
	}
	return 0;
}
