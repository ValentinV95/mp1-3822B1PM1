

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int comp(const void* a, const void* b) {
	float arg1 = *(const float*)a;
	float arg2 = *(const float*)b;
	if (arg1 < arg2) return -1;
	if (arg1 > arg2) return 1;
	return 0;
}
void swap(float* a, float* b) {
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;

}
void insertSort(float* arr, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0; j--) {
			if ((arr[j] - arr[j - 1]) < pow(10, -7)) {
				swap(&arr[j], &arr[j - 1]);
			}
		}
	}
}
void selectSort(float* arr, int n) {
	int i, j, minind;
	for (i = 0; i < n - 1; i++) {
		minind = i;
		for (j = i + 1; j < n; j++) {
			if ((arr[j] - arr[minind]) < pow(10, -7)) {
				minind = j;
			}
		}
		swap(&arr[minind], &arr[i]);

	}
}
int part(float* arr, int l, int r) {
	int i, j;
	float m;
	i = l, j = r;
	m = arr[r - (r - l) / 2];
	while (i < j) {
		while (arr[i] - m < 0) {
			i++;
		}
		while (m - arr[j] < 0) {
			j--;
		}
		if (i <= j) {
			swap(&arr[i], &arr[j]);
			j--;
		}

	}
	return j;
}
void quickSort(float* arr, int l, int r) {
	if (l < r) {
		int p;
		p = part(arr, l, r);
		quickSort(arr, l, p);
		quickSort(arr, p + 1, r);
	}
}

void merge(float* in, float* ou, int start1, int start2, int end) {
	int i, j, ind;
	i = start1;
	j = start2;
	ind = start1;
	while ((i < start2) && (j < end)) {
		if ((in[i] - in[j]) < pow(10, -7)) {
			ou[ind] = in[i];
			i++;
			ind++;
		}
		else {
			ou[ind] = in[j];
			j++;
			ind++;
		}
	}
	while (i < start2) {
		ou[ind] = in[i];
		i++;
		ind++;
	}
	while (j < end) {
		ou[ind] = in[j];
		j++;
		ind++;
	}
}
void mergeSort(float* in, float* out, int start, int end) {
	int m, i;
	if (start < end - 1) {
		m = end - ((end - start) + ((end - start) % 2)) / 2; 
		mergeSort(in, out, start, m);
		mergeSort(in, out, m, end);
		merge(in, out, start, m, end);
		for (i = start; i < end; i++) {
			in[i] = out[i];
		}
	}
}
int main()
{

	int size, i;
	float a, b;
	float* arr;
	int choice;
	clock_t st, fn;
	float* arrcheck;
	char fl = 1;
	printf("Enter size of array\n");
	scanf_s("%d", &size);
	printf("Enter the boundaries of the gap\n");
	scanf_s("%f %f", &a, &b);

	arr = (float*)malloc(sizeof(float) * size);
	arrcheck = (float*)malloc(sizeof(float) * size);
	for (i = 0; i < size; i++) {
		arr[i] = (rand() / ((float)RAND_MAX)) * (b - a) + a;
	}
	for (i = 0; i < size; i++) {
		arrcheck[i] = arr[i];
	}
	printf("Array: \n");
	for (int i = 0; i < size; i++) {
		printf("%f ", arr[i]);
	}

	printf("\nSelect sorting: enter 1 for MergeSort; 2 for QuickSort; 3 for SelectSort; 4 for InsertSort \n");
	scanf_s("%d", &choice);
	if (choice == 4) {
		st = clock();
		insertSort(arr, size);
		fn = clock();
	}
	else if (choice == 3) {
		st = clock();
		selectSort(arr, size);
		fn = clock();
	}
	else if (choice == 2) {
		st = clock();
		quickSort(arr, 0, size - 1);
		fn = clock();
	}
	else if (choice == 1) {
		st = clock();
		mergeSort(arr, (float*)malloc(sizeof(float) * size), 0, size);
		fn = clock();
	}

	printf("Sorted array: \n");
	for (int i = 0; i < size; i++) {
		printf("%f ", arr[i]);
	}

	printf("\nTime: %f\n", (fn - st) / (double)(CLOCKS_PER_SEC));



	qsort(arrcheck, size, sizeof(float), comp);
	for (i = 0; i < size; i++) {
		if (arr[i] != arrcheck[i]) {
			printf("\nArray was sorted uncorrectly\n");
			fl = 0;
			break;
		}
	}
	if (fl) printf("\nArray was sorted correctly!\n");
}

