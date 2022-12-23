#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define MENU_SIZE 8

#define EPSILON 2.220446e-16


char* menu[MENU_SIZE] = { "Изменение длинны массива (0)",  "Сортировка Пузырьком (1)", "Сортировка Выбором (2)", "Сортировка Хоара (3)", "Поразрядная сортировка (4)", "Копировать массив А в массивы В и С (5)", "Проверить правильность выполненной сортировки (6)", "Выход (7)"};

void seal(char** menu)
{
	printf_s("\n\n");
	for (int i = 0; i < MENU_SIZE; i++)
	{
		printf_s("%s\n", menu[i]);
	}
}

void input(double* mas, int dlin)
{
	for (int i = 0; i < dlin; i++)
	{
		mas[i] = rand() / (rand() / 100.0) - rand() / (rand() / 100.0);
	}
}


void output(double* mas, int dlin)
{
	for (int i = 0; i < dlin; i++)
	{
		printf("%lf\n", mas[i]);
	}
	printf("\n");
}

void choice(double* mas,int dlin)
{
	for (int i = 0; i < dlin - 1; i++)
	{
		double peremen = mas[i];
		double temp = peremen;
		int nomer = i;
		for (int j = i + 1; j < dlin; j++)
		{
			if (mas[j]<peremen)
			{
				peremen = mas[j];
				nomer = j;
			}
		}
		mas[i] = peremen;
		mas[nomer] = temp;
	}
}

void bubble(double* mas, int dlin)
{
	for (int i = 0; i < dlin - 1; i++)
	{
		int flag = 1;
		for (int j = 0; j < dlin - i - 1; j++)
		{
			if (mas[j+1]<mas[j])
			{
				double temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag)
		{
			break;
		}
	}
}

void copy(double* mas1, double* mas2, int dlin)
{
	for (int i = 0; i < dlin; i++)
	{
		mas2[i] = mas1[i];
	}
}

int compare(const void* a, const void* b)
{
	if (*(double*)a - *(double*)b < 0)
		return -1;
	else if (fabs(*(double*)a - *(double*)b) < EPSILON)
		return 0;
	else
		return 1;
}

int check_mas(double* mas1, double* mas2, int dlin)
{
	qsort(mas1, dlin, sizeof(double), compare);
	for (int i = 0; i < dlin; i++)
		if (mas1[i]!=mas2[i])
			return 0;
	return 1;
}


void qs(double* mas, int st, int fn)
{
	int i = st, j = fn;
	double t, x = mas[(st + fn) / 2];

	do {
		while (mas[i] < x) i++;
		while (mas[j] > x) j--;
		if (i <= j) {
			if (i < j) {
				t = mas[i];
				mas[i] = mas[j];
				mas[j] = t;
			}
			i++;
			j--;
		}
	} while (i <= j);
	if (i < fn) qs(mas, i, fn);
	if (st < j) qs(mas, st, j);
}


void reverse_mas(double* mas, long long n, long long k)
{
	for (int i = 0; i < (n - k) / 2; ++i)
	{

		double temp = mas[i];
		mas[i] = mas[(n - k) - i - 1];
		mas[(n - k) - i - 1] = temp;
	}
}


void radix_sort(double* mas, double* out, long long byte, long long n)
{
	unsigned char* masc = (unsigned char*)mas;

	long long counter[256];
	long long tmp;
	long long i;

	for (i = 0; i < 256; ++i) counter[i] = 0;

	for (i = 0; i < n; ++i) counter[masc[8 * i + byte]]++;

	tmp = counter[0];
	counter[0] = 0;

	for (i = 1; i < 256; ++i)
	{
		long long b = counter[i];
		counter[i] = tmp;
		tmp += b;
	}

	for (i = 0; i < n; ++i)
	{
		out[counter[masc[8 * i + byte]]] = mas[i];
		counter[masc[8 * i + byte]]++;
	}
}


void LSD(double* mas, long long n, long long k)
{
	long long i;
	double* out = (double*)malloc(n * sizeof(double));
	for (i = 0; i < 8; ++i)
	{
		if (i % 2 == 0)
		{
			radix_sort(mas, out, i, n);
		}
		else
		{
			radix_sort(out, mas, i, n);
		}
	}
	reverse_mas(mas, n, k);
	reverse_mas(mas, n, 0);
}

void minus(double* mas, int dlin, int* k)
{
	for (int i = 0; i < dlin; i++)
	{
		if (mas[i] < 0)
		{
			(*k)++;
		}
	}
}


int main()
{
	setlocale(LC_CTYPE, "Rus");
	srand(time(NULL));
	int dlin, knopki, flag = 1;
	printf_s("Введите длину массива:\n");
	scanf_s("%d", &dlin);
	double* mas_a = (double*)malloc(dlin * sizeof(double));
	double* mas_b = (double*)malloc(dlin * sizeof(double));
	double* mas_c = (double*)malloc(dlin * sizeof(double));
	input(mas_a, dlin);
	copy(mas_a, mas_b, dlin); 
	copy(mas_a, mas_c, dlin);
	
	seal(menu);
	while (flag != 0)
	{
		scanf_s("%d", &knopki);
		switch (knopki)
		{
		case 0: {printf_s("Введите длину массива: \n");
			scanf_s("%d", &dlin);
			mas_a = (double*)malloc(dlin * sizeof(double));
			mas_b = (double*)malloc(dlin * sizeof(double));
			mas_c = (double*)malloc(dlin * sizeof(double));
			input(mas_a, dlin);
			copy(mas_a, mas_b, dlin); 
			copy(mas_a, mas_c, dlin); 
			seal(menu);
			break; }
		case 1: {long long start, finish; start = clock(); 
			bubble(mas_b, dlin); 
			finish = clock(); 
			printf_s("\nВремя сортировки Пузырьком:  %.40lf\n", (finish - start) * 1.0 / CLOCKS_PER_SEC); 
			seal(menu); 
			break; }
		case 2: {long long start, finish; 
			start = clock(); 
			choice(mas_b, dlin); 
			finish = clock(); 
			printf_s("\nВремя сортировки Выбором:  %.40lf\n", (finish - start) * 1.0 / CLOCKS_PER_SEC); 
			seal(menu); 
			break; }
		case 3: {long long start, finish; 
			start = clock(); 
			qs(mas_b, 0, dlin-1); 
			finish = clock(); 
			printf_s("\nВремя сортировки Хоара:  %.40lf\n", (finish - start) * 1.0 / CLOCKS_PER_SEC); 
			seal(menu); 
			break; }
		case 4: {int k = 0;
			minus(mas_a, dlin, &k);
			long long start, finish; start = clock(); 
			LSD(mas_b, dlin, k); 
			finish = clock(); 
			printf_s("\nBремя сортировки Поразрядной:  %.40lf\n", (finish - start) * 1.0 / CLOCKS_PER_SEC); 
			seal(menu); 
			break; }
		case 5: {copy(mas_a, mas_b, dlin); 
			copy(mas_a, mas_c, dlin); 
			seal(menu); 
			break; }
		case 6: {if (check_mas(mas_c, mas_b, dlin))
		{
			printf_s("Сортировка выполнена верно\n");
		}
			  else
		{
			printf_s("Сортировка выполнена не верно\n");
		}
			  seal(menu); 
			  break; }

		case 7: {flag = 0; 
			break; }
		case 8: {output(mas_b, dlin);
			seal(menu);
			break; }
		}
	}
}