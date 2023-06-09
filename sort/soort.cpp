#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"

//функция, которая меняет элементы местами
void swap(double* a, double* b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

//сортировка выбором
void select(double* arr, int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		int minind = i;
		for (int j = i + 1; j < N; j++)
			if (arr[minind] > arr[j])
				minind = j;
		swap(&arr[minind], &arr[i]);
	}
}

//сортировка пузырьком
void bubble(double* arr, int N)
{
	int flag = 0;
	for (int i = 0; i < N; i++)
	{
		flag = 0;
		for (int j = 0; j < N - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}

//сортировка Шелла
void shell_sort(double* arr, int N)
{
	for (int i = N / 2; i > 0; i /= 2)
		for (int j = i; j < N; ++j)
			for (int k = j - i; k >= 0 && arr[k] > arr[k + i]; k -= i)
				swap(&arr[k], &arr[k + i]);
}

//сортировка слиянием
void merge(double* arr, int left, int right)
{
	int l, r, m;
	double* a;
	a = (double*)malloc((right - left) * sizeof(double));
	m = (left + right) / 2;
	l = left;
	r = m + 1;
	for (int i = left; i <= right; i++)
	{
		if ((l <= m) && ((r > right) || (arr[l] < arr[r])))
		{
			a[i - left] = arr[l];
			l++;
		}
		else
		{
			a[i - left] = arr[r];
			r++;
		}
	}
	for (int j = left; j <= right; j++)
		arr[j] = a[j - left];

}

void mergesort(double* arr, int l, int r)
{
	if (l < r)
	{
		mergesort(arr, l, (l + r) / 2);
		mergesort(arr, (l + r) / 2 + 1, r);
		merge(arr, l, r);
	}
}

//ПРОВЕРКА СОРТИРОВКИ МАССИВА
int compare(const void* a, const void* b) {
	const double* ac, * bc;
	ac = (const double*)a;
	bc = (const double*)b;

	if ((*ac - *bc) < 0) return -1;
	else
	{
		if ((*ac - *bc) > 0) return 1;
		else return 0;
	}
}

void correct_sort(double* arr, int N, double* arr1) {
	qsort(arr1, N, sizeof(double), compare);
	for (int i = 0; i < N; i++) {
		if (arr[i] == arr1[i]) printf(" Массив отсортирован верно\n");
		else printf(" Ошибка в сортировке\n ");
		break;
	}
}


//главное меню
int main()
{
	setlocale(LC_ALL, "Russian");

	double* arr;
	double* arr1;

	int N, a;
	clock_t start, finish;

	printf(" Введите количество элементов массива: ");
	scanf_s("%d", &N);

	arr = (double*)malloc(N * sizeof(double*));
	arr1 = (double*)malloc(N * sizeof(double*));

	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() + ((double)rand() / ((double)RAND_MAX));
		arr1[i] = arr[i];
		//printf("%lf ", arr[i]);

	}

	printf("\n Выберите вид сортировки:\n 1. Cортировка выбором\n 2. Cортировка пузырьком\n 3. Cортировка Шелла\n 4. Сортировка слиянием\n Введите номер сортировки: ");
	scanf_s("%d", &a);

	switch (a)
	{
	case 1: //выбор

		start = clock();
		select(arr, N);
		finish = clock();

		//for (int i = 0; i < N; i++)
		   //printf("%lf  ", arr[i]);
		//printf("\n");

		printf("\n Время работы сортировки: ");
		printf("%f ", (finish - start) / (double)(CLOCKS_PER_SEC));
		printf("сек.\n");
		printf("\n");
		correct_sort(arr, N, arr1);

		break;

	case 2: //пузырь

		start = clock();
		bubble(arr, N);
		finish = clock();

		//for (int i = 0; i < N; i++)
			//printf("%lf  ", arr[i]);
		//printf("\n");

		printf("\n Время работы сортировки: ");
		printf("%f ", (finish - start) / (double)(CLOCKS_PER_SEC));
		printf("сек.\n");
		printf("\n");
		correct_sort(arr, N, arr1);

		break;

	case 3: //Шелл

		start = clock();
		shell_sort(arr, N);
		finish = clock();

		//for (int i = 0; i < N; i++)
			//printf("%lf  ", arr[i]);
		//printf("\n");

		printf("\n Время работы сортировки: ");
		printf("%f ", (finish - start) / (double)(CLOCKS_PER_SEC));
		printf("сек.\n");
		printf("\n");
		correct_sort(arr, N, arr1);

		break;

	case 4: //слияние

		start = clock();
		mergesort(arr, 0, N - 1);
		finish = clock();

		//for (int i = 0; i < N; i++)
			//printf("%lf  ", arr[i]);
		//printf("\n");

		printf("\n Время работы сортировки: ");
		printf("%f ", (finish - start) / (double)(CLOCKS_PER_SEC));
		printf("сек.\n");
		printf("\n");
		correct_sort(arr, N, arr1);

		break;
	}
}
