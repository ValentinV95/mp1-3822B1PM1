#include "stdio.h"
#include "math.h"
#include "locale.h"

double sum(double summa, double(*anyfunc)(double, int, double), double x, double elem) 
{
	for (int i = 0; i < 100; i++)
	{
		elem = anyfunc(x, i, elem);
		summa += elem;
	}
	return summa;
}

double sumo(double summa, double(*anyfunc)(double, int, double), double x, double elem)
{
	summa += elem;
	for (int i = 99; i > -1; i--)
	{
		elem = anyfunc(x, i, elem);
		summa += elem;
	}
	return summa;
}

double sumo_sin(double summa, double(*anyfunc)(double, int, double), double x, double elem, int n)
{
	summa += elem;
	for (int i = n - 1; i > -1; i--)
	{
		elem = anyfunc(x, i, elem);
		summa += elem;
	}
	return summa;
}

double sinus1(double x, int index, double elem)
{
	if (index == 0) return x;
	elem = - elem * x * x / (2 * index * (2 * index + 1));
	return elem;
}

double sinus2(double x, int index, double elem)
{
	if (index == 0) return x;
	elem = -elem * (2 * index + 3) * (2 * index + 2) / (x * x);
	return elem;
}

double cosinus1(double x, int index, double elem)
{
	if (index == 0) return 1;
	elem = - elem * x * x / (2 * index  * (2 * index - 1));
	return elem;
}

double cosinus2(double x, int index, double elem)
{
	if (index == 0) return 1;
	elem = - elem / x / x * (2 * index +2) * (2 * index + 1) ;
	return elem;
}

double log1(double x, int index, double elem)
{
	if (index == 0) return x;
	elem = -elem * x * index / (index + 1);
	return elem;
}

double log2(double x, int index, double elem) 
{
	if (index == 0) return 0;
	elem = -elem * (index + 1) / (index * x);
	return elem;
}

double eshka1(double x, int index, double elem)
{
	if (index == 0) return 1;
	elem = elem * x / index;
	return elem;
}

double eshka2(double x, int index, double elem)
{
	if (index == 0) return 1;
	elem = elem * (index + 1) / x;
	return elem;
}

int main()
{
	double x;
	double sin1 = 0, sin2 = 0, ln1 = 0, ln2 = 0, e1 = 0, e2 = 0, cos1 = 0, cos2 = 0;//под сумму, инициализировать 
	double elem, tmp=1;//для текущего элемента
	int i,n=60;
	long long int f100, f200, f201;

	setlocale(LC_ALL, "Rus");

	printf("Введите переменную для подсчета функций: ");
	scanf_s("%lf", &x);

	/* Значения первых элементов: 
	
	elcos1 = 1;
	elcos2 = pow(x, 200) / f200;
	
	elsin1 = x;
	elsin2 = elcos2 * x / 201;

	elln1 = x;
	elln2 = pow(x, 100) / 100;

	ele1 = 1;
	ele2 = pow(x, 100)/ f100;*/
	
	printf("С первого элемента:\n");

	elem = x;
	ln1 = sum(ln1, log1, x, elem);
	printf("Логарифм: %.16lf\n", ln1);

	elem = 1;
	e1 = sum(e1, eshka1, x, elem);
	printf("Экспонента: %.16lf\n", e1);

	elem = 1;
	cos1 = sum(cos1, cosinus1, x, elem);
	printf("Косинус: %.16lf\n", cos1);

	elem = x;
	sin1 = sum(sin1, sinus1, x, elem);
	printf("Синус: %.16lf\n", sin1);

	printf("С последнего элемента:\n");

	//подсчет логарифма
	elem = - pow(x, 100) / 100;
	ln2 = sumo(ln2, log2, x, elem);
	printf("Логарифм: %.16lf\n", ln2);

	//подсчет ешки
	for (i = 1; i < 101; i++)
	{
		tmp = tmp * x / i;
	}
	elem = tmp;
	e2 = sumo(e2, eshka2, x, elem);
	printf("Экспонента: %.16lf\n", e2);	

	//подсчет косинуса
	tmp = 1;
	for (i = 1; i < 2*n+1; i++)
	{
		tmp = tmp * x / i;
	}
	elem = tmp;
	cos2 = sumo_sin(cos2, cosinus2, x, elem,n);
	printf("Косинус: %.16lf\n", cos2);

	//подсчет синуса
	elem = tmp * x / (2*n+1);
	sin2 = sumo_sin(sin2, sinus2, x, elem,n);
	printf("Синус: %.16lf\n", sin2);

	printf("Канонические:\n");

	printf("Логарифм: %.16lf\n", log(1+x));
	printf("Экспонента: %.16lf\n", exp(x));
	printf("Косинус: %.16lf\n", cos(x));
	printf("Синус: %.16lf\n", sin(x));


	


}
