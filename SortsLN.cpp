#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void swap(double *p1, double *p2);
void fillarr(double *ptr, int len, int ranMax);
void showarr(double *ptr, int len);
void selectionSort(double *ptr, int len);
void insertionSort(double *ptr, int len);
void merge(double *arr, double *tmp, int l, int m, int r);
void mergeSorting(double *arr, double *tmp, int l, int r);
void mergeSort(double *ptr, int len);
void combSort(double *ptr, int len);
void bubbleSort(double *ptr, int len);

void StartSort(void (*func) (double *, int), const char* name, double *arr, int arrSize, clock_t *clock1, int check);

int test(double *arr, int len, int isMerge);
void interface1(int *arrSize, int *ranMax, int *choice);

long long int countDo = 0;
long long int countCmpr = 0;

int main() {
	int arrSize;
	int ranMax = 10000;
	int choice = 0;
	double *arr;
	clock_t clock1;
	void(*sorts[4])(double*, int) = { selectionSort, insertionSort, mergeSort, combSort };
	const char name[4][10] = { "Selection", "Insertion", "Merge", "Comb" };
	for (arrSize = 100000; arrSize < 100001; arrSize += 100000) { // testing some numbers
		interface1(&arrSize, &ranMax, &choice);
		arr = (double*)malloc(arrSize * sizeof(double));
		printf_s("---\n");
		for (int i = 0; i < 4; i++) {
			fillarr(arr, arrSize, ranMax);
			StartSort(sorts[i], name[i], arr, arrSize, &clock1, choice);
		}
		printf_s("---\n");
		free(arr); // eof
	}
	return 0;
}


void StartSort(void (*func) (double*, int), const char* name, double *arr, int arrSize, clock_t *clock1, int check) {
	int isMerge = 0;
	if (name[0] == 'M') {
		isMerge = 1;
	}
	if (check) {
		showarr(arr, arrSize);
	}
	*clock1 = clock();
	func(arr, arrSize);
	*clock1 = clock() - *clock1;
	if (check) {
		showarr(arr, arrSize);
	}
	printf_s("%s Sort for %d elements: %li ticks (%li seconds)\nComparisons: %lli, Movements: %lli\n", name, arrSize, (unsigned int)*clock1, (unsigned int)(*clock1/CLOCKS_PER_SEC), countCmpr, countDo);
	if (test(arr, arrSize, isMerge)) {
		if (isMerge) {
			printf_s("Sort was tested with Bubble Sort\n");
		}
		else {
			printf_s("Sort was tested with Merge Sort\n");
		}
	}
	else {
		printf_s("Sort didn't pass the test\n");
	}
	if (name[0] != 'C') {
		printf_s("\n");
	}
	countCmpr = 0;
	countDo = 0;
}

int test(double *arr, int len, int isMerge) {
	double *tmp = (double *)malloc(len * sizeof(double));
	for (int i = 0; i < len; i++) {
		tmp[i] = arr[i];
	}
	if (isMerge) {
		bubbleSort(tmp, len);
	}
	else {
		mergeSort(tmp, len); // use merge sort for test
	}
	for (int i = 0; i < len; i++) {
		if (tmp[i] != arr[i]) {
			//printf_s("(%d)%lf\n", i, tmp[i]);
			free(tmp);
			return 0;
		}
	}
	free(tmp);
	return 1;
}

void combSort(double *ptr, int len) {
	int flag = 1;
	double factor = 1.2473;
	int step = len - 1;
	while (flag == 1 || step != 1) {
		flag = 0;
		for (int i = 0; i + step < len; i++) {
			if (ptr[i] > ptr[i + step]) {
				swap(&ptr[i], &ptr[i + step]);
				flag = 1;
				countDo++; countCmpr++;
			}
		}
		if (step > 1) {
			step /= factor;
		}
	}
}

void mergeSort(double *ptr, int len) {
	double *tmp = (double *)malloc(len * sizeof(double));
	mergeSorting(ptr, tmp, 0, len - 1);
	free(tmp);
}

void merge(double *arr, double *tmp, int l, int m, int r) {
	int pi1, pi2;
	int tmpindex = 0;
	pi1 = l;
	pi2 = m + 1;
	while (pi1 <= m && pi2 <= r) {
		countCmpr++;
		if (arr[pi1] <= arr[pi2]) {
			tmp[tmpindex++] = arr[pi1++];
		}
		else {
			tmp[tmpindex++] = arr[pi2++];
		}
	}
	while (pi1 > m && pi2 <= r) {
		tmp[tmpindex++] = arr[pi2++];
	}
	while (pi2 > r && pi1 <= m) {
		tmp[tmpindex++] = arr[pi1++];
	}
	for (int i = 0; i < tmpindex; i++) {
		arr[l + i] = tmp[i];
		countDo++;
	}
}

void mergeSorting(double *arr, double *tmp, int l, int r) {
	int m = l + (r - l) / 2;
	if (l == r) {
		return;
	}
	mergeSorting(arr, tmp, l, m);
	mergeSorting(arr, tmp, m + 1, r);
	merge(arr, tmp, l, m, r);
}

void insertionSort(double *ptr, int len) {
	for (int i = 1; i < len; i++) {
		for (int j = i; j > 0; j--) {
			countCmpr++;
			if (ptr[j] < ptr[j - 1]) {
				swap(&ptr[j], &ptr[j - 1]);
				countDo++;
			}
			else {
				break;
			}
		}
	}
}

void selectionSort(double *ptr, int len) {
	int minIndex;
	for (int i = 0; i < len - 1; i++) {
		minIndex = i;
		for (int j = i + 1; j < len; j++) {
			if (ptr[j] < ptr[minIndex]) {
				minIndex = j;
			}
			countCmpr++;
		}
		if (minIndex != i) {
			swap(&ptr[i], &ptr[minIndex]);
			countDo++;
		}
	}
}

void fillarr(double *ptr, int len, int ranMax) {
	while (len > 0) {
		*ptr = ((double)rand() / RAND_MAX) * ranMax;
		ptr++; len--;
	}
}

void showarr(double *ptr, int len) {
	printf_s("[");
	while (len > 0) {
		//printf_s("%d", (int)*ptr);
		printf_s("%lf", *ptr);
		if (len == 1) {
			printf_s("]\n\n");
		}
		else {
			printf_s(", ");
		}
		ptr++; len--;
	}
}

void swap(double *p1, double *p2) {
	double temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void interface1(int *arrSize, int *ranMax, int *choice) {
	printf_s("Enter length of array: ");
	scanf_s("%d", arrSize);
	printf_s("Enter randmax: ");
	scanf_s("%d", ranMax);
	printf_s("Print Before/After? (1 or 0): ");
	scanf_s("%d", choice);
}

void bubbleSort(double *ptr, int len) {
	int flag;
	for (int i = 1; i < len; i++) {
		flag = 0;
		for (int j = len-1; j >= i; j--) {
			if (ptr[j] < ptr[j - 1]) {
				swap(&ptr[j], &ptr[j - 1]);
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}
}