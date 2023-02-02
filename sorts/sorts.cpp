#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <locale.h>

void fill(double* a, int n) {
	int i = 0;
	for (i = 0; i < n; i++)
		a[i] = (((double)(rand()) / RAND_MAX) * (-100 - 100) + 100);

}

void print(double* a, int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%lf\n", a[i]);
}

int comp(const void* a, const void* b) {
	if (*(double*)a > *(double*)b)
		return 1;
	else if (*(double*)a < *(double*)b)
		return -1;
	else
		return 0;
}

void copy(double* a, double* b, int n) {
	int i;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

void check(double* a, double* b, int n) {
	int i;
	int k = 0;
	qsort(b, n, sizeof(double), comp);
	//print(b, 10);
	for (i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			k += 1;
			//printf("%lf\n", a[i - 1]);
			//printf("%lf\n", a[i]);
			//printf("%lf\n", a[i +1 ]);	
		}
	}
	//printf("%d", k);
	if (k >= 1) printf("массив отсортитрован неверно\n");
	else printf("сортировка прошла успешно\n");
}

int bplace(double* a, double r, int k) {//r-искомый элемент,k-количество элементов
	int mid, st = 0, fn = k - 1;
	while (st <= fn) {
		mid = (st + fn) / 2;
		if (r < a[mid])
			fn = mid - 1;
		else if (r > a[mid])
			st = mid + 1;
		else
			return mid;
	}
	return st;//в конце поиска st=fn=индекс элемента r

}

void shift(double* a, int s, int k) {//s - индекс который должен быть у r, k-количество элементов
	int i;
	for (i = k; i > s; --i)
		a[i] = a[i - 1];
}

void insert(double* a, int n) {
	int k;
	double r;
	int s;
	for (k = 1; k < n; k++) {
		r = a[k];
		s = bplace(a, r, k);
		shift(a, s, k);
		a[s] = r;
	}
}

void select(double* a, int n) {
	int i;
	int j;
	int mini;
	double tmp;
	for (i = 0; i < n - 1; i++) {
		mini = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[mini])
				mini = j;
		tmp = a[mini];
		a[mini] = a[i];
		a[i] = tmp;
	}
}

void comb(double* a, int n) {
	double factor = 1.246;
	double step = n - 1;
	double tmp;
	while (step > 1)
	{
		for (int i = 0; i + step < n; i++) {
			if (a[i] > a[i + (int)step]) {
				tmp = a[i];
				a[i] = a[i + (int)step];
				a[i + (int)step] = tmp;
			}
		}
		step /= factor;
	}
}

int partition(double* a, int l, int r) {

	double tmp;
	double mid = a[l + (r - l) / 2];
	while (l < r) {
		while (a[r] > mid && (r != l))
			r--;
		while (a[l] < mid && (l != r))
			l++;
		if (l < r) {
			if (a[l] > a[r]) {
				tmp = a[l];
				a[l] = a[r];
				a[r] = tmp;
			}
			else if (a[l] == a[r])
				l++;
		}
	}
	return l;
}

void quicksort(double* a, int l, int r) {
	int p;
	if (l <= r) {
		p = partition(a, l, r);
		quicksort(a, l, p - 1);
		quicksort(a, p + 1, r);
	}
}

int main() {
	int n;
	double* a;
	double* check_a;
	int menu;
	clock_t st;
	clock_t fn;
	setlocale(LC_ALL, "rus");
	printf("Введите количество элементов в массиве ");
	scanf_s("%d", &n);
	a = (double*)malloc(sizeof(double) * n);
	check_a = (double*)malloc(sizeof(double) * n);
	fill(a, n);
	copy(a, check_a, n);
	printf("Выберите алгоритм сортировки\nВставкой(0)\nВыбором(1)\nРасческой(2)\nCортировка Хоара(3)\n");
	scanf_s("%d", &menu);
	printf("Время сортировки:\n");
	if (menu < 4 && menu>-1) {
		switch (menu) {
		case(0):
			st = clock();
			insert(a, n);
			fn = clock();
			printf("%lf\n", (fn - st) / (double)CLOCKS_PER_SEC);
			break;
		case(1):
			st = clock();
			select(a, n);
			fn = clock();
			printf("%lf\n", (fn - st) / (double)CLOCKS_PER_SEC);
			break;
		case(2):
			st = clock();
			comb(a, n);
			fn = clock();
			printf("%lf\n", (fn - st) / (double)CLOCKS_PER_SEC);
			break;
		case(3):
			st = clock();
			quicksort(a, 0, n - 1);
			fn = clock();
			printf("%lf\n", (fn - st) / (double)CLOCKS_PER_SEC);
			break;
		}
		check(a, check_a, n);
	}
	else
		printf("Введено неправильное значение");
	return 0;
}

