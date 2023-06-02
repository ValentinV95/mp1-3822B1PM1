#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "locale.h"

void swap(float* a, float* b) // функция смены позиции
{
	float temp = *a;
	*a = *b;
	*b = temp;
}
void bubble(float* arr, int size) // пузырек с остановкой
{
	int flag;
	for (int i = 0; i < size; i++)
	{
		flag = 0;
		for (int j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
			}
			flag = 1;
		}
		if (flag == 0)
			{
				return;
			}
	}
}
void Insert(float* arr, int size) // вставками
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				swap(&arr[j], &arr[j - 1]);
			}
			else
			{
				break;
			}
		}
	}
}
void comb(float* arr, int size) // расческой
{
	float factor = 1.247; // число - фактор уменьшения
	float step = size - 1;
	while (step > 1)
	{
		for (int i = 0; i + step < size; i++)
		{
			if (arr[i] > arr[i + (int)step])
			{
				swap(&arr[i], &arr[i + (int)step]);
			}
		}
		step /= factor;
	}
}
void merge(float* arr, int left, int mid, int right)
{
	int i = 0, i1 = 0, i2 = 0;
	float* b = (float*)malloc(sizeof(float) * (right - left));
	while ((left + i1 < mid) && (mid + i2 < right))
	{
		if (arr[left + i1] < arr[mid + i2])
		{
			b[i1 + i2] = arr[left + i1];
			i1++;
		}
		else
		{
			b[i1 + i2] = arr[mid + i2];
			i2++;
		}
	}
	while (left + i1 < mid)
	{
		b[i1 + i2] = arr[left + i1];
		i1++;
	}
	while (mid + i2 < right)
	{
		b[i1 + i2] = arr[mid + i2];

		i2++;
	}
	for (i = 0; i < (i1 + i2); i++)
	{
		arr[left + i] = b[i];
	}
	free(b);
}
void mergeSort(float* arr, int left, int right) // Слиянием
{
	int mid;
	if (left + 1 >= right)
		return;
	mid = (left + right) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid, right);
	merge(arr, left, mid, right);
}
float* full_mass(int size, int a, int b) //заполнение массива
{
	float* mass;
	mass = (float*)malloc(size * sizeof(float));
	for (int i = 0; i < size; i++)
	{
		mass[i] = (rand() / (float)(RAND_MAX))*(b-a)+a;
	}
	return mass;
}
float* null_mass(int size) //создание пустого массива
{
	float* mas;
	mas = (float*)malloc(size * sizeof(float));
	return mas;
}
void mass_copy(float* orig, float* copy, int size)
{
	for (int i = 0; i < size; i++)
	{
		copy[i] = orig[i];
	}
}
int compare(const void* a, const void* b)//компаратор для qsort
{
	float arg1 = *(const float*)a;
	float arg2 = *(const float*)b;
	if (arg1 < arg2)
	{
		return -1;
	}
	if (arg1 > arg2)
	{
		return 1;
	}
	return 0;
}
int main()
{
	float* mass = 0, * array1_sort = 0, * array2_sort = 0;
	int size, count = 0;
	double time;
	clock_t start, end;
	int a, b;
	int c;

	setlocale(LC_ALL, "Rus");

	printf("Размер массива:\t");
	scanf_s("%d", &size);
	printf("Левая граница:\t");
	scanf_s("%d", &a);
	printf("Правая граница:\t");
	scanf_s("%d", &b);

	mass = full_mass(size, a, b);
	array1_sort = null_mass(size);
	array2_sort = null_mass(size);
	mass_copy(mass, array1_sort, size);
	mass_copy(mass, array2_sort, size);
	
	printf("Выберите сортировку:\n1.Пузырек\n2.Вставками\n3.Расческой\n4.Слиянием\n");
	printf("Выбор:");
	scanf_s("%d", &c);
	if (c == 1)
	{
		start = clock();
		bubble(array1_sort, size);
		end = clock();
	}
	else if (c == 2)
	{
		start = clock();
		Insert(array1_sort, size);
		end = clock();
	}
	else if (c == 3)
	{
		start = clock();
		comb(array1_sort, size);
		end = clock();
	}
	else if (c == 4)
	{
		start = clock();
		mergeSort(array1_sort, 0, size);
		end = clock();
	}

	time = (end - start) / (double)(CLOCKS_PER_SEC);

	qsort(array2_sort, size, sizeof(float), compare);

	for (int i = 0; i < size; i++)
	{
		if (array1_sort[i] != array2_sort[i])
		{
			count++;//счётчик не схожих элементов
			printf("%f  -  %f\n", array1_sort[i], array2_sort[i]);
		}
	}
	printf("Не совпало - %d\n", count);
	printf("Время: %lf", time);

	return 0;
}