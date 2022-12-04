#include "stdio.h"
#include "stdlib.h"
#include "search.h"
#include "string.h"
#include "time.h"
#include "locale.h"
#include "math.h"

#define EPSILON 2.220446e-16

// Операция меньше или равно для двух чисел с плавающей запятой
#define less_eq(a, b) ((a - b < 0) || (fabs(a - b) < EPSILON))

// Проверка на равенство двух чисел с плавающей запятой
int equals(double a, double b) { return (fabs(a - b) < EPSILON); }

// Функция compare для корректной работы с функцией qsort из "stdlib.h"
// Возвращает:
// -1, если a < b
//0, если a == b
//1, если a > b 
int compare(const void* a, const void* b)
{
	if (*(double*)a - *(double*)b < 0)
		return -1;
	else if (fabs(*(double*)a - *(double*)b) < EPSILON)
		return 0;
	else
		return 1;
}

// Функция перестановки двух переменных типа double
void swap(double* a, double* b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

// Создание массива double размерности size и заполнение случайными элементами
double* create_array(size_t size)
{
	double* arr = (double*)malloc(sizeof(double) * size);
	srand(time(NULL));
	for (size_t i = 0; i < size; i++)
		arr[i] = (double)rand() / (double)RAND_MAX;
	return arr;
}

// Вспомогательная функция partition
size_t partition(double* arr, size_t left, size_t right)
{
	double mid = arr[left + (right - left) / 2];
	left--;
	right++;
	
	while (1)
	{
		do { left++; } while (arr[left] < mid);
		do { right--; } while (arr[right] > mid);
		if (left >= right) return right;
		swap(&arr[left], &arr[right]);
	}
}

// Собственно алгоритм сортировки Хоара
// Используется внутри функции quicksort
void __quicksort(double* arr, size_t left, size_t right)
{
	if (left < right)
	{
		size_t pivot = partition(arr, left, right);
		__quicksort(arr, left, pivot);
		__quicksort(arr, pivot+1, right);
	}
}

// Алгоритм сортировки Хоара
void quicksort(double* arr, size_t size)
{
	__quicksort(arr, 0, size-1);
}

// Вспомогательная функция merge для слияния массивов
void merge(double* in, double* out, size_t left, size_t mid, size_t right)
{
	size_t l_curr = left;
	size_t r_curr = mid;

	for(size_t i = left; i < right; i++)
	{
		if ((l_curr != mid) && (r_curr != right))
		{
			if (less_eq(in[l_curr], in[r_curr]))
				out[i] = in[l_curr++];
			else
				out[i] = in[r_curr++];
		}

		else if (l_curr != mid)
			out[i] = in[l_curr++];
		else
			out[i] = in[r_curr++];
	}
}

// Собственно сортировка слиянием
// Используется внутри функции mergesort
void __mergesort(double* in, double* out, size_t size)
{
	size_t step = 1;
	while (step < size)
	{
		for (size_t i = 0; i < size; i += 2 * step)
			merge(in, out, i, min(i + step, size), min(i + 2 * step, size));
		memcpy(in, out, sizeof(double) * size);
		step *= 2;
	}
}

// Алгоритм сортировки слиянием
void mergesort(double* arr, size_t size)
{
	double* tmp = (double*)malloc(sizeof(double) * size);
	memcpy(tmp, arr, sizeof(double) * size);
	__mergesort(arr, tmp, size);
	free(tmp);
}

// Алгоритм сортировки пузырьком
void bubblesort(double* arr, size_t size)
{
	int flag = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size - 1 - i; j++)
			if (less_eq(arr[j + 1], arr[j]))
			{
				swap(&arr[j], &arr[j + 1]);
				flag = 1;
			}
		if (!flag) return;
	}
}

// Алгоритм сортировки выбором
void selectionsort(double* arr, size_t size)
{
	size_t current_min_ind = 0;
	for (size_t i = 0; i < size - 1; i++)
	{
		current_min_ind = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (less_eq(arr[j], arr[current_min_ind]))
				current_min_ind = j;
		}
		swap(&arr[i], &arr[current_min_ind]);
	}
}

// Проверка правильности работы выбранного алгоритма
int check_array(double* arr, double* cpy, size_t size)
{
	qsort((void*)cpy, size, sizeof(double), compare);
	for (size_t i = 0; i < size; i++)
		if (!equals(arr[i], cpy[i]))
			return 0;
	return 1;
}

int main()
{
	double* arr;
	double* copy;
	double approx_time = 0, average_time = 0, best_time = 0, worst_time = 0;
	size_t array_size;
	size_t iteration_count;
	int choice;
	int flag = 1;
	clock_t start, end;
	void (*sort) (double*, size_t) = NULL;

	setlocale(LC_ALL, "ru_RU.utf8");
	// Пользователь вводит размер массива,
	printf("Введите размер массива: ");
	scanf_s("%Iu", &array_size);
	// ...количество повторений работы программы
	printf("Введите количество итераций: ");
	scanf_s("%Iu", &iteration_count);
	// ...выбирает алгоритм сортировки из четырёх предложенных
	printf("Введите используемую сортировку:\n1. Сортировка выбором\n2. Пузырьковая сортировка\n3. Сортировка Хоара\n4. Сортировка слиянием\n");
	scanf_s("%d", &choice);

	//Обработка выбора
	switch (choice)
	{
	case 1:
		sort = selectionsort;
		break;
	case 2:
		sort = bubblesort;
		break;
	case 3:
		sort = quicksort;
		break;
	case 4:
		sort = mergesort;
		break;
	default:
		flag = 0;
		break;
	}

	if (flag)
	{
		for (size_t iteration = 0; iteration < iteration_count; iteration++)
		{
			// На каждой итерации создаётся новый массив и его копия
			if (!flag) break;
			printf("Итераиця #%Iu: Создание массива размера %Iu...\n", iteration + 1, array_size);
			arr = create_array(array_size);
			copy = (double*)malloc(sizeof(double) * array_size);
			memcpy(copy, arr, sizeof(double) * array_size);

			printf("Сортировка...\n");
			start = clock();
			sort(arr, array_size);
			end = clock();
			printf("Проверка...\n");

			if (check_array(arr, copy, array_size))
			{
				printf("Массив отсортирован правильно.\n");
				approx_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Приблизительное затраченное время: %lf\n", approx_time);
				worst_time = max(approx_time, worst_time);
				best_time = min(approx_time, best_time);
				average_time = (average_time * iteration + approx_time) / (iteration + 1);
			}
			else
			{
				printf("Массив не был отсортирован.\n");
				flag = 0;
			}

			free(arr);
			free(copy);
		}

		printf("Выполнение программы завершено. Полученные результаты:\nЛучшее время: %lf\nСреднее время: %lf\nХудшее время: %lf\n", best_time, average_time, worst_time);
	}

	else
		printf("Произошла ошибка.\n");

	return 0;
}