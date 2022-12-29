#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<time.h>
#define N 50000

int prmenu() {
	printf(" 1) Ввести размер массива\n 2) Ввести диапазон для рандомных чисел\n 3) Заполнить массив\n ");
	printf("4) Выполнить сортировку пузырьком\n 5) Выполнить сортировку вставками\n 6) Выполнить сортировку Хоара\n");
	printf(" 7) Выполнить сортировку слиянием \n 8) Завершить программу\n");
}

void domas(double a[], int n, int r1, int r2) {
	for (int i = 0; i < n; i++) {
		a[i] = rand() / RAND_MAX * (r2 - r1) + r1;
	}
}
void copymas(double a[], double b[], int n) {
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

void bable(double b[], int n) {
	double k;
	int flag = 1;
	for (; flag > 0;) {
		flag = 0;
		n--;
		for (int j = 0; j < n; j++) {
			if (b[j] > b[j + 1]) {
				k = b[j];
				b[j] = b[j + 1];
				b[j + 1] = k;
				flag++;
			}
		}
	}
 }
int biplace(double b[], int r, int k) { // Вспомогательная функция для сортировки вставками
	int st = 0;                        // бинарный поиск места для эл-та r
	int fn = k - 1;
	int mid;
	int s;
	while (st < fn) {
		mid = (st + fn) / 2;
		if (r > b[mid])
			st = mid + 1;
		else
			fn = mid - 1;
	}
	if (r > b[st])
		s = st + 1;
	else
		s = st;
	return s;
}
void shift(double b[], int s, int k) { // Вспомогателная функция для сортировки вставками
	for (int i = k; i > s; i--) {
		b[i] = b[i - 1];
	}
}
void insert(double b[], int n) {
	int s, k;
	double r;
	for (k = 1; k < n; k++) {
		r = b[k];
		s = biplace(b, r, k);
		shift(b, s, k);
		b[s] = r;
	}
}
void hoar(double b[], int first, int last)
{
	double pivot;
	int p;
	int l_hold = first;
	int r_hold = last;
	pivot = b[first];
	while (first < last)
	{
		while ((b[last] >= pivot) && (first < last))
			last--;
		if (first != last)
		{
			b[first] = b[last];
			first++;
		}
		while ((b[first] <= pivot) && (first < last))
			first++;
		if (first != last)
		{
			b[last] = b[first];
			last--;
		}
	}
	b[first] = pivot;
	p = first;
	first = l_hold;
	last = r_hold;
	if (first < p)
		hoar(b, first, p - 1);
	if (last > p)
		hoar(b, p + 1, last);
}
void merge(double b[], int n)
{
	int mid = n / 2;
	if (n % 2 == 1)
		mid++;
	int h = 1; 
	double* c = (double*)malloc(n * sizeof(double));
	int step;
	while (h < n)
	{
		step = h;
		int i = 0;   
		int j = mid; 
		int k = 0;   
		while (step <= mid)
		{
			while ((i < step) && (j < n) && (j < (mid + step)))
			{ 
				if (b[i] < b[j])
				{
					c[k] = b[i];
					i++; k++;
				}
				else {
					c[k] = b[j];
					j++; k++;
				}
			}
			while (i < step)
			{ 
				c[k] = b[i];
				i++; k++;
			}
			while ((j < (mid + step)) && (j < n))
			{
				c[k] = b[j];
				j++; k++;
			}
			step = step + h; 
		}
		h = h * 2;
		for (i = 0; i < n; i++)
			b[i] = c[i];
	}
}



int main() {
	int n=1000; // вводимый размер массива
	double a[N]; // массив который задается пользавателем
	double b[N]; // массив для сортировки
	int r1=0,r2=1000; // диапазон рандомных чисел
	int m; // для выбора из меню
	int st, fn;
	setlocale(LC_CTYPE, "Rus");
	domas(a, n, r1, r2);
	prmenu();
	scanf_s("%d", &m);
	while (m<8) {
		switch (m)
		{
		case 1: scanf_s("%d", &n); break;
		case 2: scanf_s("%d %d", &r1, &r2); break;
		case 3: domas(a, n, r1, r2); break;
		case 4:st = clock(); bable(b, n); fn = clock(); printf("Сортировка была выполнена за %d \n", (fn - st)); break;
		case 5:st = clock(); insert(b, n); fn = clock(); printf("Сортировка была выполнена за %d \n", (fn - st)); break;
		case 6:st = clock(); hoar(b, 0, n - 1); fn = clock(); printf("Сортировка была выполнена за %d \n", (fn - st)); break;
		case 7:st = clock(); merge(b, n); fn = clock(); printf("Сортировка была выполнена за %d \n", (fn - st));  break;
		};
		prmenu();
		scanf_s("%d", &m);
	}
	

}