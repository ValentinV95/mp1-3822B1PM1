#include <stdlib.h>
#include <stdio.h>
#include <locale>
#include <time.h>
int comp(const void* a, const void* b) //checked
{
	if (*(double*)a < *(double*)b)
		return -1;
	else if (*(double*)a > *(double*)b)
		return 1;
	else return 0;
}
void swp(double* a, double* b) //checked
{
	double * tmp = a;
	a = b;
	b = tmp;
}
bool correct(double* in, double* sort, int n) //Верная функция проверки сортировки
{
	int i;
	qsort(in, n, sizeof(double), comp);
	for (i = 0; i < n; i++)
	{
		if (in[i] != sort[i]) return false;
	}
	return true;
}
void bubble(double* in, int  n) //checked
{
	int i, j, count = 1;
	for (i = 0; i < n - 1 && count != 0; i++)
	{
		count = 0;
		for (j = 0; j < n - i - 1; j++)
		{
			if (in[j] > in[j + 1])
			{
				swp(&in[j], &in[j + 1]);
				count++;
			}
		}
	}
}
void oldcomb(double* in, int n) //Оригинальный нерабочая расчёска
{
	float factor = 1.246;
	int step = n - 1, i;
	while (step != 0) {
		for (i = 0; i + step < n; i++)
			if (in[i] > in[i + step])
				swp(&in[i], &in[i + step]);
		step /= factor;
	}
}
void comb(double* in, int n)  //Модернизированная расчёска
{
	double factor = 1.246;
	int step = n - 1, i, f = 1;
	while (step != 1 || f == 1)
	{
		step /= factor;
		if (step < 1)
			step = 1;
		f = 0;
		for (i = 0; i + step < n; i++)
			if (in[i] > in[i + step])
			{
				swp(&in[i], &in[i + step]);
				f = 1;
			}
	}
}
void countbyte(unsigned long long* mas, int n, int count[256], int byte)
{
	unsigned char* masc = (unsigned char*)mas;
	int i, tmp1, tmp2, bias = sizeof(unsigned long long);
	for (i = 0; i < 256; i++)
		count[i] = 0;
	for (i = 0; i < n; i++)
		count[masc[i * bias + byte]]++;
	tmp1 = count[0];
	count[0] = 0;
	for (i = 1; i < 256; i++)
	{
		tmp2 = count[i];
		count[i] = count[i - 1] + tmp1;
		tmp1 = tmp2;
	}
}
void radix_unsigned(unsigned long long* mas, int n, unsigned long long* mas_tmp)
{
	unsigned char* masc = (unsigned char*)mas;
	int count[256], sizetype = sizeof(unsigned long long), j, i;
	for (i = 0; i < sizetype; i++)
	{
		countbyte(mas, n, count, i);
		for (j = 0; j < n; j++)
			mas_tmp[count[masc[j * sizetype + i]]++] = mas[j];
		for (j = 0; j < n; j++)
		{
			mas[j] = mas_tmp[j];
		}
	}

}
void radix_signed(long long* mas, int n, long long* tmp)
{
	int count = 0, i = 0;
	radix_unsigned((unsigned long long*)mas, n, (unsigned long long*)tmp);
	while (count < n && mas[count++] >= 0);
	count--;
	for (; count < n; count++)
		tmp[i++] = mas[count];
	count = 0;
	for (; i < n; i++)
		tmp[i] = mas[count++];
	for(i=0;i<n;i++)
		mas[i] = tmp[i];
}
void radix_double(double* mas, int n, double* tmp)
{
	int count = 0, i = n - 1;
	radix_unsigned((unsigned long long*)mas, n, (unsigned long long*)tmp);
	while (i >= 0 && mas[i] < 0)
	{
		tmp[count++] = mas[i];
		i--;
	}
	i = 0;
	for (; count < n; count++)
		tmp[count] = mas[i++];
	/*for (i = 0; i < n; i++)
		mas[i] = tmp[i];*/
}
int main()
{
	double* a, * etalon, *t, *tmp;
	int n, i;
	int choise, action;
	clock_t start, fin;
	setlocale(LC_ALL, "Rus");
	while (1)
	{
		printf("Введите количество элементов в массиве:\n");
		scanf_s("%i", &n);
		a = (double*)malloc(n * sizeof(double));
		etalon = (double*)malloc(n * sizeof(double));
		for (i = 0; i < n; i++)
		{
			etalon[i] = a[i] = double(rand())/RAND_MAX*1000000-500000;
		}
		printf("Массив из %d элементов создан, выберите действие:\n", n);
		printf("1) Сортировка пузырьком\n2) Сортировка расчёской\n3) Поразрядная сортировка\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case  1:
		{
			start = clock();
			bubble(a, n);
			fin = clock();
			break;
		}
		case  2:
		{
			start = clock();
			comb(a, n);
			fin = clock();
			break;
		}
		case  3:
		{
			t = (double*)malloc(n * sizeof(double));
			start = clock();
			radix_double(a, n, t);
			tmp = a;
			a = t;
			t = tmp;
			fin = clock();
			free(t);
			break;
		}
		}
		if (correct(etalon, a, n))
			printf("Массив отсортирован верно\n");
		else printf("Массив отсортирован неверно\n");
		printf("Сортировка заняла: %lf с\n", (fin-start)/double(CLOCKS_PER_SEC));
		printf("Для вывода массива после сортировки введите 1, для перезапуска программы введите 2, для завершения введите 3\n");
		scanf_s("%d", &action);
		if (action == 1)
		{
			for (i = 0; i < n; i++)
				printf("%lf\n", a[i]);
			printf("Для перезапуска программы введите 2, для завершения введите 3\n");
			scanf_s("%d", &action);
		}
		if (action == 3) break;
		free(a);
		free(etalon);
		printf("\n");
	}
	return 0;
}