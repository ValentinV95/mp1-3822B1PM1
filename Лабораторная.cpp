// Лабораторная.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <Locale.h>
#include <time.h>
#include <stdlib.h>
void fill(double* a, int na)
{
	int i;
	for (i = 0; i < na; i++)
		a[i] = (((double)(rand()) / RAND_MAX) * (-1000 - 1000) + 1000);
	printf("Массив а:\n");
	for (int i = 0; i < na; i++)
		printf("%lf ", a[i]);
}

void copy(double* a, double* b, int na) {
	int i;
	for (i = 0; i < na; i++) 
	{
		b[i] = a[i];
	}
}


void swap(double* a, double* b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void compare(const void* a, const void* b)
{
	if (*(double*)a - *(double*)b > 0)
		return 1;
	else
	{
		if (*(double*)a - *(double*)b < 0)
			return -1;
		else
			return 0;
	}
}

void check(double* a, double* b, int na)
{
	int i;
	int k = 0;
	qsort(b, na, sizeof(double), compare);
	for (i = 0; i < na; i++)
	{
		if (a[i] != b[i])
			k += 1;
	}
	if (k >= 1)
		printf("Массив отсортирован неверно.");
	else
		printf("Массив отсортирован верно.");
}

void bubble(double* a, int na)
{
	int i,j;
	int flag = 0;
	for (i = 0; i < na; i++) 
	{
		flag = 0;
		for (j = 0; j < na - 1 - i; j++) 
		{
			if (a[j] > a[j + 1]) 
			{
				swap(&a[j], &a[j + 1]);
				flag = 1;
			}
			
		}
		if (flag == 0)
			break;
		
	}
	
}

void insert(double* a, int na)
{
	for (int i = 0; i < na; i++)
		for (int j = i; j > 0; j--)
			if (a[j] < a[j - 1])
				swap(&a[j], &a[j - 1]);
			else
				break;
}

void shell(double* a, int na)
{
	int i, j, k;
	for (i = na / 2; i > 0; i /= 2)
	{
		for (j = i; j < na; j++)
		{
			for (k = j; k - i >= 0; k -= i)
			{
				if (a[k] < a[k - i])
					swap(&a[k], &a[k - i]);
			}
		}
	}
}

void merge(double* in, double* out, int l, int m, int r)
{
	int l1 = l;
	int l2 = m + 1;
	int i;
	m = (l + r) / 2;
	for (i = l1; i <= r; i++)
	{
		if ((l1 <= m) && ((l2 > r) || (in[l1] < in[l2])))
		{
			out[i] = in[l1];
			l1++;
		}
		else
		{
			out[i] = in[l2];
			l2++;
		}
	}
	for (int j = l1; j <= r; j++)
		in[j] = out[j - l1];
}

void mergesort(double* in, double* out, int l, int r)
{
	if (l != r)
	{
		int m = (l + r) / 2;
		mergesort(in, out, l, m);
		mergesort(in, out, m + 1, r);
		merge(in, out, l, m, r);
		for (int i = l; i <= r; i++)
			in[i] = out[i];
	}
}

int main()
{
	setlocale(LC_CTYPE, "Rus");
	int na, choice;
	double* a;
	double* checka;
	printf("Введите размер массива:\n");
	scanf_s("%d", &na);
	a = (double*)malloc(sizeof(double) * na);
	checka = (double*)malloc(sizeof(double) * na);
	fill(a, na);
	copy(a, checka, na);
	printf("\nВведите номер необходимой сортировки:\n");
	printf("1.Сортировка пузырьком.\n2.Сортировка вставками.\n3.Сортировка Шелла.\n4.Сортировка слиянием.\n");
	scanf_s("%d", &choice);
    
	if (1 <= choice && choice<= 4) {
		clock_t start, end;
		switch (choice) {
		case 1:
			start = clock();
			bubble(a, na);
			end = clock();
			printf("Отсортированный массив а:\n");
			for (int i = 0; i < na; i++)
				printf("%lf ", a[i]);
			printf("Время выполнения сортировки: %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			break;
		case 2:
			start = clock();
			insert(a, na);
			end = clock();
			printf("Отсортированный массив а:\n");
			for (int i = 0; i < na; i++)
				printf("%lf ", a[i]);
			printf("Время выполнения сортировки: %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			break;

		case 3:
			start = clock();
			shell(a, na);
			end = clock();
			printf("Отсортированный массив а:\n");
			for (int i = 0; i < na; i++)
				printf("%lf ", a[i]);
			printf("Время выполнения сортировки: %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			break;

		case 4:
			start = clock();
			mergesort(a, (double*)malloc(sizeof(double) * na), 0, na - 1);
			end = clock();
			printf("Отсортированный массив а:\n");
			for (int i = 0; i < na; i++)
				printf("%lf ", a[i]);
			printf("Время выполнения сортировки: %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			break;

		}
		check(a, checka, na);
	}
	else
		printf("Введен некорректный номер.");
	return 0;
}
	
