#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<locale.h>
void swap(float* a, float* b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
}
void copy_(float* mas_a, float* mas_b, int size)
{
	int i;
	for (i = 0; i < size; i++) mas_b[i] = mas_a[i];
}
int compare(const void* a, const void* b)
{
	const float* x, * y;
	x = (const float*)a;
	y = (const float*)b;
	if ((*x - *y) < 0) return -1;
	else
	{
		if ((*x - *y) > 0) return 1;
		else return 0;
	}
}
int check(float* mas_a, float* mas_b, int size)
{
	int i;
	qsort(mas_a, size, sizeof(float), compare);
	for (i = 0; i < size; i++)
		if (abs(mas_a[i] - mas_b[i]) > 1e-8)
			return 0;
	return 1;
}
void sign(float* input, int size, int*k_p) {
	float* output = (float*)malloc(size * sizeof(float));
	int key, i, j;
	key = -1;
	for (i = 0; i < size; i++)
		if (input[i] < 0) {
			key = i;
			break;
		}
	if (key != -1) {
		for (j = size - 1; j >= key; j--)
			output[size - j - 1] = input[j];
		for (j = 0; j < key; j++)
			output[j + size - key] = input[j];
		for (j = 0; j < size; j++) {
			if (input[j] != output[j])++* k_p;
			input[j] = output[j];
		}
	}
}
void radix(float* input, int size, int* k_p) {
	int i, j;
	int step = 4;
	int number;
	unsigned char* mas;
	float* output;
	int count[256];
	int sum[256];
	for (number = 0; number < step; number++) {
		mas = (unsigned char*)input;
		output = (float*)malloc(size * sizeof(float));
		for (i = 0; i < 256; i++) {
			count[i] = 0;
			sum[i] = 0;
		}
		for (i = number; i < step * size; i += step)
			count[mas[i]]++;
		for (i = 0; i < 256; i++)
			for (j = 0; j < i; j++)
				if (count[i] != 0)
					sum[i] += count[j];
		for (i = number; i < step * size; i += step) {
			output[sum[mas[i]]] = input[i / step];
			sum[mas[i]]++;
		}
		for (i = 0; i < size; i++) {
			if (input[i] != output[i]) ++*k_p;
			input[i] = output[i];
		}
	}
	sign(input, size, &*k_p);
}
void shell(float* input, int size, int* k_p, int* k_s) {
	int i, j, k; 
	float tmp;
	for (i = size / 2; i > 0; i /= 2)
		for (j = i; j < size; j++)
			for (k = j - i; (k > -1) && (++*k_s && (input[k] > input[k + i])); k -= i) {
				swap(&input[k], &input[k + i]);
				++*k_p;
			}
}
void bubble(float* input, int size, int*k_p, int*k_s) {
	int i, j, swapped;
	for (i = 0; i < size - 1; i++) {
		swapped = 0;
		for (j = 0; j < size - i - 1; j++) {
			if (++*k_s && (input[j] > input[j + 1])) {
				swap(&input[j], &input[j + 1]);
				++*k_p;
				swapped = 1;
			}
		}
		if (swapped == 0) break;
	}
}
void general(float* input, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		input[i] = ((float)rand() + 0.01) /(float)(rand());
		if (rand() % 2)
			input[i] = -input[i];
	}
}
void main() {
	srand(time(0));
	setlocale(LC_CTYPE, "RUS");
	printf("Введите количество элементов в массиве\n");
	int n;
	scanf_s("%d", &n);
	float* mas_a = (float*)malloc(n * sizeof(float));
	float* mas_b = (float*)malloc(n * sizeof(float));
	float* mas_c = (float*)malloc(n * sizeof(float));
	general(mas_a, n);
	while (1)
	{
		printf("\n");
		printf("Меню:\n");
		printf("Пузырёк - 1\n");
		printf("Шелла - 2\n");
		printf("Поразрядная - 3\n");
		printf("Изменить количество элементов в массиве - 4\n");
		printf("Выход - 5\n");
		int s;
		scanf_s("%d", &s);
		switch (s)
		{
		case 1:
		{
			clock_t start, finish;
			int k_p = 0;
			int k_s = 0;
			copy_(mas_a, mas_b, n);
			copy_(mas_a, mas_c, n);
			start = clock();
			bubble(mas_b, n, &k_s, &k_p);
			finish = clock();
			int ch = check(mas_c, mas_b, n);
			if (ch)
			{
				printf("Массив успешно отсортирован\n");
				printf("Время сортировки: %d секунд\n", (finish - start) / CLOCKS_PER_SEC);
				printf("количество сравнений: %d\n", k_s);
				printf("количество перестановок: %d\n", k_p);
			}
			else printf("Ошибка, не удалось отсортировать массив\n");
			break;
		}
		case 2:
		{
			clock_t start, finish;
			int k_s = 0;
			int k_p = 0;
			copy_(mas_a, mas_b, n);
			copy_(mas_a, mas_c, n);
			start = clock();
			shell(mas_b, n, &k_s, &k_p);
			finish = clock();
			int ch = check(mas_c, mas_b, n);
			if (ch)
			{
				printf("Массив успешно отсортирован\n");
				printf("Время сортировки: %d секунд\n", (finish - start) / CLOCKS_PER_SEC);
				printf("количество сравнений: %d\n", k_s);
				printf("количество перестановок: %d\n", k_p);
			}
			else printf("Ошибка, не удалось отсортировать массив\n");
			break;
		}
		case 3:
		{
			clock_t start, finish;
			int k_p = 0;
			copy_(mas_a, mas_b, n);
			copy_(mas_a, mas_c, n);
			start = clock();
			radix(mas_b, n, &k_p);
			finish = clock();
			int ch = check(mas_c, mas_b, n);
			if (ch)
			{
				printf("Массив отсортирован успешно\n");
				printf("Время сортировки: %d секунд\n", (finish - start) / CLOCKS_PER_SEC);
				printf("количество сравнений: 0\n");
				printf("количество перестановок: %d\n", k_p);
			}
			else printf("Ошибка, не удалось отсортировать массив\n");
			break;
		}
		case 4:
		{
			printf("ввести кол-во элементов в массиве.\n");
			scanf_s("%d", &n);
			mas_a = (float*)malloc(n * sizeof(float));
			mas_b = (float*)malloc(n * sizeof(float));
			mas_c = (float*)malloc(n * sizeof(float));
			general(mas_a, n);
			break;
		}
		case 5:
		{
			printf("Работа завершена!\n");
			return 0;
		}
		default:
			break;
		}
	}
}
