typedef unsigned int uint;
typedef unsigned char uchar;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>
int qfloat(const void* pa, const void* pb) {
	float a = *(float*)pa, b = *(float*)pb;
	if (a > b) return 1;
	if (a < b) return -1;
	return 0;
}

void swap(float* a, float* b) {
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}
void Insert(float* arr, int n) {
	float tmp;
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0; j--)
			if (arr[j] < arr[j - 1])
			{
				tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
			}
			else break;
}
void merge(float* inp, float* out, int l, int m, int r) {
	int l1 = l, l2 = m;
	int ind = l;
	while ((l1 < m) && (l2 < r))
		if (inp[l1] <= inp[l2])
			out[ind++] = inp[l1++];
		else
		{
			out[ind++] = inp[l2++];
		}
	for (; l1 < m; l1++)
		out[ind++] = inp[l1];
	for (; l2 < r; l2++)
		out[ind++] = inp[l2];
}
void Mergesort(float* inp, float* out, int l, int r) {
	if (l != r)
	{
		int m = (r - l) / 2 + l;
		Mergesort(inp, out, l, m);
		Mergesort(inp, out, m + 1, r);
		merge(inp, out, l, m + 1, r + 1);
		for (int i = l; i <= r; i++) inp[i] = out[i];
	}
}
void countByte(uint* mas, int size, int count[256], int byte) {
	uchar* masc;
	int tmp, bias;
	bias = sizeof(float);
	masc = (uchar*)mas;
	for (int i = 0; i < 256; i++) count[i] = 0;
	for (int i = 0; i < size; i++) count[masc[i * bias + byte]]++;
	tmp = count[0];
	count[0] = 0;
	for (int i = 1; i < 256; i++) {
		swap((float*)&tmp, (float*)&count[i]);
		count[i] += count[i - 1];
	}
}
void LSD(uint* mas, int size, uint* mas_tmp) {
	int count[256];
	uchar* masc = (uchar*)mas;
	int sizetype = sizeof(float);
	for (int i = 0; i < sizetype; i++)
	{
		countByte(mas, size, count, i);
		for (int j = 0; j < size; j++) mas_tmp[count[masc[j * sizetype + i]]++] = mas[j];
		for (int j = 0; j < size; j++) mas[j] = mas_tmp[j];
	}
}
void radix(float* mas, int n) {
	float* tmp;
	tmp = (float*)malloc(n * sizeof(float));
	int count = 0, i;
	LSD((uint*)mas, n, (uint*)tmp);
	while ((count < n) && (mas[count++] >= 0));
	count--;
	for (i = 0; i < count; i++) tmp[i + n - count] = mas[i];
	for (; i < n; i++) tmp[n - (++count)] = mas[i];
	memcpy(mas, tmp, n * sizeof(float));
}
void check(float* mas, float* copy, int n) {
	int fl = 0;
	qsort(copy, n, sizeof(float), (int(*) (const void*, const void*)) qfloat);
	for (int i = 0; i < n; i++)
	{
		if (copy[i] != mas[i]) {
			fl++;
			break;
		}
	}
	if (fl == 0) printf("Массив был успешно отсортирован\n");
	else printf("Массив отсортирован неудачно");
}
int main()
{
	setlocale(LC_ALL, "Rus");
	float* arr, * out, * copy;
	int n, choose;
	clock_t start, end;
	printf("Введите размер массива, который хотите отсортировать: ");
	scanf_s("%i", &n);
	arr = (float*)malloc(n * sizeof(float));
	copy = (float*)malloc(n * sizeof(float));
	for (int i = 0; i < n; i++)
		copy[i] = arr[i] = (float)(rand()) / RAND_MAX * 100 * pow(-1, i) + 1;
	printf("Выберите сортировку, с помощью которой вы хотите отсторировать массив:\n Сортировка вставками - 1\n Сортировка слиянием - 2\n Поразрядная соритровка - 3\n");
	scanf_s("%i", &choose);
	start = clock();
	switch (choose)
	{
	case 1:
		Insert(arr, n);
		break;
	case 2:
		out = (float*)malloc(n * sizeof(float));
		Mergesort(arr, out, 0, n - 1);
		break;
	case 3:
		radix(arr, n);
		break;
	}
	end = clock();
	//check(arr, copy, n);
	printf("Время соритровки: %f", (end - start) / (double)(CLOCKS_PER_SEC));
	return 0;
}