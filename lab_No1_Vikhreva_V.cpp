#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"

void swap(float* a,int i, int j)
{
	float t;
	t = a[i]; a[i] = a[j]; a[j] = t;
}
void copy_arr(float* arr1, float* arr2, int n)
{
	int i;
	for (i = 0; i < n; i++)
		arr2[i] = arr1[i];
}
int compare(const void* a, const void* b)
{
	float arg1,  arg2;
	arg1 = *(const float*)a;
	arg2 = *(const float*)b;

	if (arg1 < arg2) 
		return -1;
	if (arg1 > arg2) 
		return 1;
	return 0;
}
int check(float* arr, float* orig_arr, int na)
{
	int i;
	float* arr1;
	arr1 = (float*)malloc(sizeof(float) * na);
	copy_arr(orig_arr, arr1, na);
	qsort(arr1, na, sizeof(float), compare);
	for (i = 0; i < na-1; i++)
		if (arr[i] != arr1[i]) 
			return 0;
	return 1;
}
void check_result(float* arr, float* orig_arr, int na, clock_t st, clock_t f)
{
	if (check(arr, orig_arr, na))
	{
		printf("массив отсортирован верно!\n");
		printf("время сортировки: %f сек\n", (f - st) / (double)CLOCKS_PER_SEC);
	}
	else printf("Ошибка сортировки!");
}
void bubble(float* arr, int na)
{
	int i, j, f;
	for (i = 0; i < na; i++)
	{
		f = 0;
		for (j = 0; j < na - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				swap(arr,j,j+1);
				f = 1;
			}
		if (f == 0)
			return;
	}
}
void choice(float* arr, int na)
{
	int i, j, i_min;
	for (i = 0; i < na - 1; i++)
	{
		i_min = i;
		for (j = i; j < na; j++)
			if (arr[j] < arr[i_min])
				i_min = j;
		swap(arr, i, i_min);
	}
}
int partition(float* arr, int left, int right)
{
	float mid = arr[left + (right - left) / 2];
	while (left < right)
	{
		while (arr[left] < mid && (left != right))
			left++;
		while (arr[right] > mid && (right != left))
			right--;
		if (left < right) {
			if (arr[left] > arr[right])
				swap(arr,left,right);
			else if (arr[left] == arr[right]) 
				right--;
		}
	}
	return right;
}
void QuickSort(float* arr, int left, int right) {
	int p;
	if (left <= right) 
	{
		p = partition(arr, left, right);
		QuickSort(arr, left, p - 1);
		QuickSort(arr, p + 1, right);
	}
}
void ShellaSort(float* arr, int na)
{
	int step, i, j;
	for (step = na / 2; step > 0; step /= 2)
		for (i = step; i < na; i++)
			for (j = i - step; j >= 0 && arr[j] > arr[j + step]; j -= step)
				swap(arr, j, j + step);
}

int main()
{
	int n;
	int i,key;
	float *a;
	float* arr1;
	clock_t start, finish;
	setlocale(LC_CTYPE, "Rus");
	printf("введите количество элементов в массиве: ");
	scanf_s("%d", &n);
	a = (float*)malloc(sizeof(float) * n);
	arr1 = (float*)malloc(sizeof(float) * n);
	for (i = 0; i < n; i++)
		a[i] = rand() / (float)RAND_MAX * (100 + 100) - 100;

	char menu[5][25] = { "1 - пузырек", "2 - сортировка выбором", "3 - сортировка Хоара", "4 - сортировка Шелла", "5 - выход"};
	printf("\nменю:\n");
	for (i = 0; i < 5; i++)
		printf("%s\n", menu[i]);	

	key = 0;
	while (key < 5) 
	{
		printf("\nвыберите действие (1-5): ");
		scanf_s("%d", &key);
		switch (key)
		{
		case 1:
		{
			copy_arr(a, arr1, n);
			start = clock();
			bubble(arr1, n);
			finish = clock();
			check_result(arr1, a, n, start,finish);
			break;
		}
		case 2:
		{
			copy_arr(a, arr1, n);
			start = clock();
			choice(arr1, n);
			finish = clock();
			check_result(arr1, a, n, start, finish);
			break;
		}
		case 3:
		{
			copy_arr(a, arr1, n);
			start = clock();
			QuickSort(arr1, 0, n - 1);
			finish = clock();
			check_result(arr1, a, n, start, finish);
			break;
		}
		case 4:
		{
			copy_arr(a, arr1, n);
			start = clock();
			ShellaSort(arr1, n);
			finish = clock();
			check_result(arr1, a, n, start, finish);
			break;
		}
		case 5: break;
		default:
		{
			printf("нет команды под таким номером, повторите ввод");
			key = 0;
		}
		}
	}

}