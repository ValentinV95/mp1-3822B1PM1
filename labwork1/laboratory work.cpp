#include "stdio.h"
#include "locale.h"
#include "stdlib.h"
#include "string.h"
#include "cstdlib"
#include "time.h"


void myswap(float* a, float* b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

int compare(const void* a, const void* b)// функция сравнения элементов массива
{
	const float* ad;
	const float* bd;
	ad = (const float*)a;
	bd = (const float*)b;

	if ((*ad - *bd) < 0) return -1;
	else
	{
		if ((*ad - *bd) > 0) return 1;
		else return 0;
	}
}   


void select(float* arr, int size)
{
	int i, j;
	for (i = 0; i < size - 1; i++)
	{
		int min_ind=i;
		for (j = i + 1; j < size; j++)
			if (arr[min_ind] > arr[j])
				min_ind = j;
		myswap(&arr[i], &arr[min_ind]);
	}
}

void merge(float* in, float* out, int left, int mid, int right)
{
	int l1 = left;
	int l2 = mid+1;
	int ind=0;
	int i;
	
	while (l1 <= mid && l2 <= right)
	{
		if (in[l1] <= in[l2])
			out[ind++] = in[l1++];
		else
			out[ind++] = in[l2++];
	}	
	while (l1>mid && l2<= right) 
		out[ind++] = in[l2++];
	while (l2 > right && l1 <= mid)
		out[ind++] = in[l1++];
	for (i = 0; i < ind; i++)
		in[left + i] = out[i];
		
	
}

void merge_sort(float* arr, float* tmp, int l, int r) {
	int m = l + (r - l) / 2;
	if (l == r) {
		return;
	}
	merge_sort(arr, tmp, l, m);
	merge_sort(arr, tmp, m + 1, r);
	merge(arr, tmp, l, m, r);
}


void countbyte(unsigned int* arr, int size, int count[256], int byte) //исхоодный массив, размер массива, символьный массив, текущий разряд
{
	unsigned char* masc = (unsigned char*)malloc(sizeof(unsigned char)*size);
	int i, tmp1, tmp2, bias = sizeof(unsigned int);
	masc = (unsigned char*)arr;
	for (i = 0; i < 256; i++)
		count[i] = 0;
	for (i = 0; i < size; i++)
		count[masc[i * bias + byte]]++;
	tmp1 = count[0];
	count[0] = 0;
	for (i = 1; i <256 ; i++)
	{
		tmp2 = count[i];
		count[i] = count[i - 1] + tmp1;
		tmp1 = tmp2;
	}

}

void radix_unsigned(unsigned int* arr, int size, unsigned int* arr_tmp)
{
	unsigned char* masc = (unsigned char*)malloc(sizeof(unsigned char)*size);
	int count[256], sizetype = sizeof(unsigned int);
	int j, i;
	masc = (unsigned char*)arr;
	for (i = 0; i < sizetype; i++)
	{
		countbyte(arr, size, count, i);
		for (j = 0; j < size; j++)
			arr_tmp[count[masc[j * sizetype + i]]++] = arr[j];
		for (j = 0; j < size; j++)
			arr[j] = arr_tmp[j];
	}
}

void radix_float(float* arr, float* tmp, int size)
{
	int i=0;
	int count = 0;
	radix_unsigned((unsigned int*)arr, size, (unsigned int*)tmp);
	while (i < size)
	{
		if (arr[i] >= 0)
			count++;
		i++;
	}
	for (i = 0; i < count; i++) {
		tmp[size - count + i] = arr[i];
	}
	count = size - count;
	for (count = count--; count >= 0; count--) {
		tmp[count] = arr[i++];
	}

	for (int i = 0; i < size; i++) {
		arr[i] = tmp[i];
	}

}

int check(float* arr,float* arr_test, int size)
{
	float* q_arr=0;
	q_arr = (float*)malloc(sizeof(float) * size);
	q_arr = arr;
	qsort(q_arr, size, sizeof(float), compare);
	//for (int i = 0; i < size; i++)
		//printf("%d)%f\t%f\n", i, arr_test[i],q_arr[i]);
	for (int i = 0; i < size; i++)
	{
		//
		if (q_arr[i] != arr_test[i])
			return 0;
	}
	return 1;

}

int main()
{
	int choice=0;
	int size,i;
	float* arr=0;
	float* arr_test = 0;
	float* arr_tmp = 0;
	clock_t start, end;

	setlocale(LC_ALL, "Rus");
	
	printf("Задайте желаемый размер массива:\n");
	scanf_s("%d", &size);
	arr = (float*)malloc(sizeof(float) * size);
	arr_test = (float*)malloc(sizeof(float) * size);
	

	printf("Способы задания массива:\n1. Задать с клавиатуры\n2. Заполнить рандомными элементами\nВведите цифру, соответсвующую вашему выбору:");
	scanf_s("%d", &choice);

	srand(size);
	if (choice == 1)
	{
		printf("Укажите элементы массива:\n");
		for (i = 0; i < size; i++)
		{
			float tmp;
			scanf_s("%f", &tmp);
			arr[i] = tmp;
			arr_test[i] = arr[i];
		}
	}
	else  if (choice == 2)
	{
		for (i = 0; i < size; i++)
		{
			arr[i] = (((float)rand()) / RAND_MAX) * 1000 - (((float)rand()) / RAND_MAX) * 1000;
			arr_test[i] = arr[i];
			//printf("%d) %f\n", i, arr[i]);
		}
	}
	else printf("Невернный ввод");

	printf("\n");



	printf("Способы сортировки массива:\n1. Сортировка выбором\n2. Сортировка слиянием\n3. Поразрядная сортировка\nВведите цифру, соответсвующую вашему выбору:");
	scanf_s("%d", &choice);
	
	if (choice == 1)
	{
		start = clock();
		select(&(*arr_test), size);
		end = clock();
		
		if (check(arr, arr_test, size) == 1)
			printf_s("Итог сортировки: ok");
		else
			printf_s("Итог сортировки: error");
	}
	else  if (choice == 2)
	{
		arr_tmp = (float*)malloc(sizeof(float) * size);
		memset(arr_tmp, 0, sizeof(float) * size);
		
		start = clock();
		merge_sort(arr_test, arr_tmp,0, size-1);
		end = clock();
		
		if (check(arr, arr_test, size) == 1)
			printf_s("Итог сортировки: ok");
		else
			printf_s("Итог сортировки: error");
		
		free(arr_tmp);
	}
	else if (choice == 3)
	{
		arr_tmp = (float*)malloc(sizeof(float) * size);
		memset(arr_tmp, 0, sizeof(float) * size);
		
		start = clock();
		radix_float(arr_test, arr_tmp, size);
		end = clock();
		
		if (check(arr, arr_test, size) == 1)
			printf_s("Итог сортировки: ok");
		else
			printf_s("Итог сортировки: error");
		
		free(arr_tmp);
	}
	else printf("Невернный ввод");
	
	printf_s(" Ваше время составило: %lf секунд\n", (end-start)/(double)CLOCKS_PER_SEC);
	free(arr);
	free(arr_test);
}
