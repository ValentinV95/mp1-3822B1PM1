#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"

void swap(float* number1, float* number2);
void selectsort(float* array, int size);
float* creat_array_fulled(int size, int left_number, int right_number);
float* creat_array_empty(int size);
void examination(float* mass1, float* mass2, int size);
int compare(const void* a, const void* b);
void array_copy(float* mass_origin, float* mass_copy, int size);
void shellsort(float* mass, int size);
void radixfloat(float* mas, float* tmp, int size);
void radix(unsigned int* mass, int size, unsigned int* tmp);
void countbyte(unsigned int* arr, int size, int count[256], int byte);

int main()
{
	setlocale(LC_CTYPE, "RUS");
	clock_t start, end;
	float* array_origin = NULL, * mass1_sort = NULL, * mass2_sort = NULL, * mass3_sort = NULL;
	int size, left_number, right_number, action;

	printf("Привет пользователь!\n");
	printf("\n");
	printf("Введите количество элементов массива, который нужно отсортировать: ");
	scanf_s("%d", &size);
	printf("\n");
	printf("Введите наименьшее значение массива: ");
	scanf_s("%d", &left_number);
	printf("\n");
	printf("Введите наибольшее значение массива: ");
	scanf_s("%d", &right_number);
	printf("\n");
	printf("-----------------------------------------------------------------------\n");
	printf("\n");
	array_origin = creat_array_fulled(size, left_number, right_number);
	mass1_sort = creat_array_empty(size);
	mass2_sort = creat_array_empty(size);
	mass3_sort = creat_array_empty(size);
	array_copy(array_origin, mass1_sort, size);
	array_copy(array_origin, mass2_sort, size);

	while (1)
	{
		printf("Меню:\n");
		printf("  Сортировка Выбором: 1\n");
		printf("  Сортировка Шелла: 2\n");
		printf("  Сортировка Радикс:  3\n");
		printf("  Изменить массив: 4\n");
		printf("  Завершить работу программы: 5\n");
		printf("Выбор действия: ");
		scanf_s("%d", &action);
		switch (action)
		{
		case 1:
		{
			mass1_sort = creat_array_empty(size);
			mass2_sort = creat_array_empty(size);
			array_copy(array_origin, mass1_sort, size);
			array_copy(array_origin, mass2_sort, size);

			start = clock();
			selectsort(mass1_sort, size);
			end = clock();

			qsort(mass2_sort, size, sizeof(float), compare);
			printf("\n");
			examination(mass1_sort, mass2_sort, size);

			printf("Время в секундах - %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			printf("\n");
			printf("=============================================\n");
			printf("\n");

			free(mass1_sort);
			free(mass2_sort);
			break;
		}
		case 2:
		{
			mass1_sort = creat_array_empty(size);
			mass2_sort = creat_array_empty(size);
			array_copy(array_origin, mass1_sort, size);
			array_copy(array_origin, mass2_sort, size);

			start = clock();
			shellsort(mass1_sort, size);
			end = clock();

			qsort(mass2_sort, size, sizeof(float), compare);
			printf("\n");
			examination(mass1_sort, mass2_sort, size);
			

			printf("Время в секундах - %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			printf("\n");
			printf("=============================================\n");
			printf("\n");

			free(mass1_sort);
			free(mass2_sort);
			break;
		}
		case 3:
		{
			mass1_sort = creat_array_empty(size);
			mass2_sort = creat_array_empty(size);
			mass3_sort = creat_array_empty(size);
			array_copy(array_origin, mass1_sort, size);
			array_copy(array_origin, mass2_sort, size);

			start = clock();
			radixfloat(mass1_sort, mass3_sort, size);
			end = clock();

			qsort(mass2_sort, size, sizeof(float), compare);
			printf("\n");
			examination(mass3_sort, mass2_sort, size);
			
			printf("Время в секундах - %lf\n", (end - start) / (double)(CLOCKS_PER_SEC));
			printf("\n");
			printf("=============================================\n");
			printf("\n");

			free(mass1_sort);
			free(mass2_sort);
			free(mass3_sort);
			break;
		}
		case 4:
		{
			free(array_origin);
			printf("\n");
			printf("Введите количество элементов массива, который нужно отсортировать: ");
			scanf_s("%d", &size);
			printf("\n");
			printf("Введите наименьшее значение массива: ");
			scanf_s("%d", &left_number);
			printf("\n");
			printf("Введите наибольшее значение массива: ");
			scanf_s("%d", &right_number);
			printf("\n");
			printf("-----------------------------------------------------------------------\n");
			printf("\n");
			array_origin = creat_array_fulled(size, left_number, right_number);
			break;
		}
		case 5:
		{
			printf("\n");
			printf("\n");
			printf("Программа завершена!\n");
			return 0;
		}
		default:
		{
			printf("\n");
			printf("Неправильный выбор!\n");
			printf("\n");
			printf("=============================================\n");
			printf("\n");
			break;
		}
		}
	}
	free(array_origin);
	free(mass1_sort);
	free(mass2_sort);
	free(mass3_sort);

	return 0;
}

void swap(float* number1, float* number2)//замена значений
{
	float tmp = *number1;
	*number1 = *number2;
	*number2 = tmp;
}

void selectsort(float* array, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int minindex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (array[minindex] > array[j])
			{
				minindex = j;
			}
		}
		swap(&array[i], &array[minindex]);
	}
}

float* creat_array_fulled(int size,int left_number,int right_number)//создание динамического массива с рандомными значениями типа float
{
	int i;
	float* mas;
	mas = (float*)malloc(size * sizeof(float));//выделение памяти
	for (i = 0; i < size; i++)
	{
		mas[i] = ((float)rand() / RAND_MAX) * (right_number - left_number) + left_number;//заплнение массива
	}
	return mas;
}

float* creat_array_empty(int size)//создание пустого массива
{
	float* mas;
	mas = (float*)malloc(size * sizeof(float));
	return mas;
}

void examination(float* mass1, float* mass2, int size)//проверка двух массивов на схожесть
{
	int i,count = 0;
	for (i = 0; i < size; i++)
	{
		//printf("%f  -  %f\n", mass1[i], mass2[i]);
		if (mass1[i] != mass2[i])
		{
			count++;//счётчик не схожих элементов
		}
	}
	printf("Колличество не правильно отсортированных элементов - %d\n", count);
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

void array_copy(float* mass_origin, float* mass_copy,int size)//копирование массива
{
	int i;
	for (i = 0; i < size; i++)
	{
		mass_copy[i] = mass_origin[i];
	}
}

void shellsort(float* mass, int size)
{
	int i, j, k;
	for (i = size / 2; i > 0; i /= 2)
		for (j = i; j < size; j++)
			for (k = j; k - i>= 0 && mass[k] < mass[k - i]; k -= i)
				swap(&mass[k], &mass[k - i]);
}


void countbyte(unsigned int* arr, int size, int count[256], int byte)
{
	unsigned char* arrC;
	int k,j,i,bias;
	int tmp, temp;

	bias = sizeof(unsigned int);
	arrC = (unsigned char*)arr;

	for (k = 0; k < 256; k++)
		count[k] = 0;

	for (j = 0; j < size; j++)
		count[arrC[j * bias + byte]]++;

	tmp = count[0];
	count[0] = 0;
	for (i = 1; i < 256; i++)
	{
		temp = count[i];
		count[i] = count[i - 1] + tmp;
		tmp = temp;
	}
	
}

void radix(unsigned int* mass, int size, unsigned int* tmp)
{
	unsigned char* arrc = (unsigned char*)mass;
	int i,j,k,sizetype = sizeof(unsigned int);
	int count[256];

	for (i = 0; i < sizetype; i++)
	{
		countbyte(mass, size, count, i);

		for (j = 0; j < size; j++)
			tmp[count[arrc[j * sizetype + i]]++] = mass[j];

		for (k = 0; k < size; k++)
			mass[k] = tmp[k];

	}
}

void radixfloat(float* mas, float* tmp, int size)
{
	int count = 0, i;
	
	radix((unsigned int*)mas, size, (unsigned int*)tmp);
	while (count < size && mas[++count] >= 0);
	for (i = 0; i < count; i++)
	{
		tmp[i + size - count] = mas[i];
	}
	for (; i < size; i++)
	{
		tmp[size - (++count)] = mas[i];
	}
}