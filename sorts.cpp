// sorts.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"


void* malloc(size_t size);

float* creating(int size)
{
	float* mas;
	mas = (float*)malloc(sizeof(float) * size);
	for (int i = 0; i < size; i++)
	{
		mas[i] = ((float)rand() / ((float)RAND_MAX));
		printf("%f ", mas[i]);
	}
	return mas;
}

int compare(const void* a, const void* b)
{
	const float* x, * y;
	x = (const float*)a;
	y = (const float*)b;
	if ((*x - *y) < 0) return -1;
	else
	{
		if ((*x - *y) > 0)
			return 1;
		else
			return 0;
	}
}

int check(float* mas_a, float* mas_b, int size)
{
	int i;
	qsort(mas_a, size, sizeof(float), compare);
	for (i = 0; i < size; i++)
		if (abs(mas_a[i] - mas_b[i]) > 0)
			return 0;
	return 1;
}

void swap(float* a, float* b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

void select(float* arr, int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		int minind = i;
		for (int j = i + 1; j < N; j++)
		{
			if (arr[minind] > arr[j])
				minind = j;
		}
		swap(&arr[minind], &arr[i]);
	}
}

void insert(float* arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
				swap(&arr[j], &arr[j - 1]);
			else
				break;
		}
	}

}

void shell(float* arr, int N)
{
	for (int i = N / 2; i > 0; i /= 2)
	{
		for (int j = i; j < N; j++)
		{
			for (int k = j; k - i >= 0; k -= i)
			{
				if (arr[k] < arr[k - i])
					swap(&arr[k], &arr[k - i]);
			}
		}
	}

}

void merge(float* in, float* out, int l1, int l2, int r)
{
	int i, j, ind;
	i = l1;
	j = l2;
	ind = l1;
	while ((i < l2) && (j < r))
	{
		if ((in[i] - in[j]) < pow(10, -7))
		{
			out[ind] = in[i];
			i++;
			ind++;
		}
		else
		{
			out[ind] = in[j];
			j++;
			ind++;
		}
	}
	while (i < l2)
	{
		out[ind] = in[i];
		i++;
		ind++;
	}
	while (j < r)
	{
		out[ind] = in[j];
		j++;
		ind++;
	}
}
void mergesort(float* in, float* out, int l, int r)
{
	int m, i;
	if (l < r - 1)
	{
		m = r - ((r - l) + ((r - l) % 2)) / 2;
		mergesort(in, out, l, m);
		mergesort(in, out, m, r);
		merge(in, out, l, m, r);
		for (i = l; i < r; i++)
		{
			in[i] = out[i];
		}
	}
}


int main()
{
	clock_t start, end;
	int n, choice;
	float* massiv;
	float* massivcheck;
	int ch;
	setlocale(LC_ALL, "Rus");

	printf("Выберете номер сортировки\n");
	printf("№1-сортировка выбором\n");
	printf("№2-сортировка вставками\n");
	printf("№3-сортировка Шелла\n");
	printf("№4-сортировка слиянием\n");
	scanf_s("%d", &choice);

	printf("Введите кол-во элементов\n");
	scanf_s("%d", &n);

	massiv = creating(n);
	massivcheck = massiv;

	if (choice == 1)
	{
		start = clock();
		select(massiv, n);
		end = clock();
		printf("\n\n ");
		for (int i = 0; i < n; i++)
		{
			printf("%f ", massiv[i]);
		}
		printf("\nВремя, которе потребовалось: ");
		printf("%f\n", (end - start) / (double)(CLOCKS_PER_SEC));

	}
	else if (choice == 2)
	{
		start = clock();
		insert(massiv, n);
		end = clock();
		printf("\n\n ");
		for (int i = 0; i < n; i++)
		{
			printf("%f ", massiv[i]);
		}
		printf("\nВремя, которе потребовалось: ");
		printf("%f\n", (end - start) / (double)(CLOCKS_PER_SEC));

	}
	else if (choice == 3)
	{
		start = clock();
		shell(massiv, n);
		end = clock();
		printf("\n\n ");
		for (int i = 0; i < n; i++)
		{
			printf("%f ", massiv[i]);
		}
		printf("\nВремя, которе потребовалось: ");
		printf("%f\n", (end - start) / (double)(CLOCKS_PER_SEC));

	}
	else if (choice == 4)
	{
		float* mass;
		start = clock();
		mergesort(massiv, (float*)malloc(sizeof(float) * n), 0, n);
		end = clock();
		printf("\n\n ");
		for (int i = 0; i < n; i++)
		{
			printf("%f ", massiv[i]);
		}
		printf("\nВремя, которе потребовалось: ");
		printf("%f\n", (end - start) / (double)(CLOCKS_PER_SEC));
	}
	ch = check(massivcheck, massiv, n);
	if (ch == 1)
		printf("Массив отсортирован успешно\n");
	else
		printf("Массив отсортирован неверно\n");

}