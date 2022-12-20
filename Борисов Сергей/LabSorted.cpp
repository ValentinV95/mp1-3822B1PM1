#include "stdio.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"


void swaps(double* a, double* b) {
	double tmp;
	tmp = (double)*a;
	*a = *b;
	*b = tmp;
}

void printArray(double b[], double nb) { // функция печати массива
	for (long long int i = 0; i < nb; i++) {
		printf("%lf ", b[i]);
	}
	printf("\n");
}

int compare(const void* a, const void* b)
{
	const double* ad, * bd;
	ad = (const double*)a;
	bd = (const double*)b;

	if ((*ad - *bd) < 0) return -1;
	else
	{
		if ((*ad - *bd) > 0) return 1;
		else return 0;
	}
}

int check(double a[], double b[], long long int len) { // отсортированный, исходный, длина 
	double* c = (double*)malloc(sizeof(double) * len);
	for (long long int i = 0; i < len; i++) {
		c[i] = b[i];
	}

	qsort(c, len, sizeof(double), compare);
	for (long long int i = 0; i < len; i++) {
		if (c[i] != a[i]) {
			//printf("%lf %lf %d", c[i], a[i], i);
			return 0;
		}
	}
	return 1;
}


// Hoare
long long int partition(double* mas, long long int l, long long int r) {
	double mid = mas[l + (r - l) / 2];
	while (l < r) {
		while (mas[l] < mid && (l != r)) 
			l++;
		while (mas[r] > mid && (r != l))
			r--;

		if (l < r) { 
			if (mas[l] > mas[r]) { 
				swaps(&mas[l], &mas[r]);
			}
			else if (mas[l] == mas[r]) { // без этого возможно зацикливание
				r--;
			}
		}

	}


	return r;
}


void quick_sort(double* mas, long long int l, long long int r) {
	if (l <= r) {
		long long int p = partition(mas, l, r);
		quick_sort(mas, l, p - 1);
		quick_sort(mas, p + 1, r);
	}
}


// Bubble
void bubble(double* mas, long long int n) {
	int t = 0;
	for (long long int i = 0; i < n - 1; i++) {
		for (long long int j = 0; j < n - 1 - i; j++) {
			if (mas[j] > mas[j + 1]) {
				swaps(&mas[j], &mas[j + 1]);
				t = 1;
			}
		}
		if (!t) {
			break;
		}
	}
}

// Radix sort

void countByte(unsigned long long* mas, long long int size, int count[256], int byte) {
	unsigned char* masc;
	int bias;
	int tmp1, tmp2;
	bias = sizeof(unsigned long long);
	masc = (unsigned char*)mas;
	for (int i = 0; i < 256; i++) {
		count[i] = 0;
	}
	for (long long int i = 0; i < size; i++) {
		count[masc[i * bias + byte]]++;
	}
	tmp1 = count[0];
	count[0] = 0;
	for (long long int i = 1; i < 256; i++) {
		tmp2 = count[i];
		count[i] = count[i - 1] + tmp1;
		tmp1 = tmp2;
	}

}

void radix_sort(unsigned long long* mas, long long int size, unsigned long long* mas_tmp) {
	unsigned char* masc = (unsigned char*)mas;
	int count[256];
	int sizetype = sizeof(unsigned long long);
	for (int i = 0; i < sizetype; i++) {
		countByte(mas, size, count, i);
		for (long long int j = 0; j < size; j++) {
			mas_tmp[count[masc[j * sizetype + i]]++] = mas[j];
		}
		for (long long int j = 0; j < size; j++) {
			mas[j] = mas_tmp[j];
		}
	}
}

void radixDouble(double* mas, long long int n, double* mas_tmp) {
	int count = 0;
	long long int i = 0;
	radix_sort((unsigned long long int*) mas, n, (unsigned long long int*) mas_tmp);

	while (i < n) {
		if (mas[i] >= 0) {
			count++;
		}
		i++;
	}

	//printf("%d ", count);

	for (i = 0; i < count; i++)
		mas_tmp[i + (n - count)] = mas[i];

	for (; i < n; i++)
		mas_tmp[n - (++count)] = mas[i];

	for (long long int i = 0; i < n; i++)
		mas[i] = mas_tmp[i];

}

void input(double* a, double* b, long long int len) { // заполнение псевдослучаынйми числами
	double lz = 1;
	double rz = 100;
	for (long long int i = 0; i < len; i++) {
		double k = ((double)rand() / RAND_MAX) * (rz - lz) + lz;
		a[i] = k;
		b[i] = k;
	}
}

int output(double a[], double b[], int len, double time) { 
	printf("Кол-во элементов: %d \n", len);
	printf("Неупорядоченный массив (первые элементы): ");
	if(len<=20) printArray(b, len);
	else printArray(b, 20);
	printf("Упорядоченный массив (первые элементы): ");
	if (len <= 20) printArray(a, len);
	else printArray(a, 20);
	printf("Время выполнения: %lf \n", time);

}

int MenuChoice(char* menu[], int ns) { // меню
	for (int i = 0; i < ns; i++) {
		printf("%s \n", menu[i]);
	}
	printf("Введите номер: ");
	int n;
	scanf_s("%d", &n);
	return n;
}

void main() {
	setlocale(LC_CTYPE, "RUS");
	long long int na = 0;
	long long int nb = 0;
	double* a = 0;
	double* b = 0;
	double* tmp;
	long long int l = 0;
	clock_t start, end;
	long long int n = -1;
	int fs = 0; // флаг заполнения
	char* menu[5] = { "Ввод (0)", "Пузырёк (1)", "Сортировка Хоара (2)", "Линейная Сортировка (3)", "Выход (4)" };

	while (n!=4) {
		n = MenuChoice(menu, 5);
		switch (n)
		{
		case 0:
			printf("Введите длину массива: ");
			scanf_s("%d", &l);
			a = (double*)malloc(sizeof(double) * l);
			b = (double*)malloc(sizeof(double) * l);
			input(a, b, l);
			fs = 1;
			break;
		case 1:
			if (fs) {
				start = clock();
				bubble(a, l);
				end = clock();
				
				if (!check(a, b, l))  printf("Не удалось отсортировать массив");
				else output(a, b, l, (end - start) / ((double)(CLOCKS_PER_SEC)));
				
				for (int i = 0; i < l; i++) {
					a[i] = b[i];
				}
			}
			else {
				printf("Сначала используйте ввод \n");
			}
			break;
		case 2:
			if (fs) {
				start = clock();
				quick_sort(a, 0, l - 1);
				end = clock();
				if (!check(a, b, l))  printf("Не удалось отсортировать массив");
				else output(a, b, l, (end - start) / ((double)(CLOCKS_PER_SEC)));
				
				for (int i = 0; i < l; i++) {
					a[i] = b[i];
				}
			}
			else {
				printf("Сначала используйте ввод \n");
			}
			break;
		case 3:
			if (fs) {
				tmp = (double*)malloc(sizeof(double) * l);
				start = clock();
				radixDouble(a, l, tmp);
				end = clock();

				if (!check(a, b, l))  printf("Не удалось отсортировать массив \n");
				else output(a, b, l, (end - start) / ((double)(CLOCKS_PER_SEC)));

				for (int i = 0; i < l; i++) {
					a[i] = b[i];
				}
			}
			else {
				printf("Сначала используйте ввод \n");
			}
			break;
		case 4:
			break;

		default:
			printf("Ошибка: Выберите цифру из предложенных! \n");
		}


	}
}
