#include "stdio.h"
#include "math.h"
#include "locale.h"

float sum(float summa, float(*anyfunc)(float, int, float), float x, float elem)
{
	for (int i = 0; i < 100; i++)
	{
		elem = anyfunc(x, i, elem);
		summa += elem;
	}
	return summa;
}

float sumo(float summa, float(*anyfunc)(float, int, float), float x, float elem, int n)
{
	summa += elem;
	for (int i = n-1; i > -1; i--)
	{
		elem = anyfunc(x, i, elem);
		summa += elem;
	}
	return summa;
}


float sinus1(float x, int index, float elem)
{
	if (index == 0) return x;
	elem = -elem * x * x / (2 * index * (2 * index + 1));
	return elem;
}

float sinus2(float x, int index, float elem)
{
	if (index == 0) return x;
	elem = -elem * (2 * index + 3) * (2 * index + 2) / (x * x);
	return elem;
}

float cosinus1(float x, int index, float elem)
{
	if (index == 0) return 1;
	elem = -elem * x * x / (2 * index * (2 * index - 1));
	return elem;
}

float cosinus2(float x, int index, float elem)
{
	if (index == 0) return 1;
	elem = -elem * (2 * index + 2) * (2 * index + 1) / (x * x);
	return elem;
}

float log1(float x, int index, float elem)
{
	if (index == 0) return x;
	elem = -elem * x * index / (index + 1);
	return elem;
}

float log2(float x, int index, float elem)
{
	if (index == 0) return 0;
	elem = -elem * (index + 1) / (index * x);
	return elem;
}

float eshka1(float x, int index, float elem)
{
	if (index == 0) return 1;
	elem = elem * x / index;
	return elem;
}

float eshka2(float x, int index, float elem)
{
	if (index == 0) return 1;
	elem = elem * (index + 1) / x;
	return elem;
}

int main()
{
	float x;
	float sin1 = 0, sin2 = 0, ln1 = 0, ln2 = 0, e1 = 0, e2 = 0, cos1 = 0, cos2 = 0;//под сумму, инициализировать 
	float elem, tmp = 1;//для текущего элемента
	int i, n;
	float eps = powf(10,-29);
	long long int f100, f200, f201;

	setlocale(LC_ALL, "Rus");

	printf("Введите переменную для подсчета функций: ");
	scanf_s("%f", &x);

	/* Значения первых элементов:

	elcos1 = 1;
	elcos2 = pow(x, 200) / f200;

	elsin1 = x;
	elsin2 = elcos2 * x / 201;
	elln1 = x;
	elln2 = pow(x, 100) / 100;
	ele1 = 1;
	ele2 = pow(x, 100)/ f100;*/

	printf("С первого элемента:\n\n");

	elem = x;
	ln1 = sum(ln1, log1, x, elem);
	printf("Логарифм:%.16f\n", ln1);
	printf("Погрешность: %.16f\n", ln1 - log(1 + x));

	elem = 1;
	e1 = sum(e1, eshka1, x, elem);
	printf("Экспонента: %.16f\n", e1);
	printf("Погрешность: %.16f\n", e1 - exp(x));

	elem = 1;
	cos1 = sum(cos1, cosinus1, x, elem);
	printf("Косинус: %.16f\n", cos1);
	printf("Погрешность: %.16f\n", cos1 - cos(x));


	elem = x;
	sin1 = sum(sin1, sinus1, x, elem);
	printf("Синус: %.16f\n", sin1);
	printf("Погрешность: %.16f\n\n", sin1 - sin(x));


	printf("С последнего элемента:\n\n");

	//подсчет логарифма
	elem = x;
	tmp = 1;
	for (i = 1; i < 100; i++)
	{
		tmp = log1(x, i, elem);
		if (fabsf(elem) - eps < 0) break;
		elem = tmp;
	}
	ln2 = sumo(ln2, log2, x, elem, i);
	printf("Логарифм: %.16f\n", ln2);
	printf("Погрешность: %.16f\n", ln2 - log(1 + x));

	//подсчет ешки
	elem = 1;
	tmp = x;
	for (i = 1; i < 100; i++)
	{
		tmp = eshka1(x, i, elem);
		if (fabsf(elem) - eps < 0) break;
		elem = tmp;
	}
	e2 = sumo(e2, eshka2, x, elem, i-1);
	printf("Экспонента: %.16f\n", e2);
	printf("Погрешность: %.16f\n", e2 - exp(x));


	//подсчет косинуса
	elem = 1;
	tmp = 1;
	for (i = 1; i < 100;i++) 
	{
		tmp = cosinus1(x, i, elem);
		if (fabsf(elem) - eps < 0) break;
		elem = tmp;
	}
	cos2 = sumo(cos2, cosinus2, x, elem, i-1);
	printf("Косинус: %.16f\n", cos2);
	printf("Погрешность: %.16f\n", cos2 - cos(x));


	//подсчет синуса
	elem = x;
	tmp = 1;
	for (i = 1; i < 100; i++)
	{
		tmp = sinus1(x, i, elem);
		if (fabsf(elem) - eps < 0) break;
		elem = tmp;
	}
	sin2 = sumo(sin2, sinus2, x, elem, i-1);
	printf("Синус: %.16f\n", sin2);
	printf("Погрешность: %.16f\n\n", sin2 - sin(x));


	printf("Канонические:\n\n");

	printf("Логарифм: %.16f\n", logf(1 + x));
	printf("Экспонента: %.16f\n", expf(x));
	printf("Косинус: %.16f\n", cosf(x));
	printf("Синус: %.16f\n", sinf(x));

}
