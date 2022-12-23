#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>


int printMenu1()
{
	int variant = 0;
	int N = 0;
	printf("~ ~ ~ ~ ~ ~ ~ ~ \n");
	printf("1. Set an array\n");
	printf("2. I want to compare the sorting times\n");
	printf("~ ~ ~ ~ ~ ~ ~ ~ \n");
	scanf_s("%d", &variant);
	if ((variant < 1) || (variant > 2))
	{
		system("cls");
		printf("Error.Try again\n");
		printMenu1();
	}
	system("cls");
	return variant;
}


int inputArray()
{
	int N = 0;
	printf_s("Set the number of elements in the array\n");
	scanf_s("%d", &N);
	if (N < 1)
	{
		system("cls");
		printf("Error. Try again.\n");
		inputArray();
	}
	return N;
}


int printMenu2()
{
	int variant = 0;
	printf("~ Sorting Selection ~\n");
	printf("1.Insert Sort\n");
	printf("2.Selection Sort\n");
	printf("3.Quick Sort\n");
	printf("4.Shell Sort\n");
	printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	scanf_s("%d", &variant);
	if ((variant < 1) || (variant > 4))
	{
		system("cls");
		printf("Error.Try again\n");
		variant=printMenu2();
	}
	return variant;
}


void insertSort(int N, double* mas)
{
	for (int i = 1; i < N; i++)
	{
		int k = i;
		while ((k > 0) && (mas[k - 1] > mas[k]))
		{
			mas[k] = mas[k] + mas[k - 1];
			mas[k - 1] = mas[k] - mas[k - 1];
			mas[k] = mas[k] - mas[k - 1];
			k -= 1;
		}
	}
}


void selectionSort(int N, double* mas)
{
	int i, j, min;
	double tmp;
	for (i = 0; i < N; i++)
	{
		min = i;
		for (j = i + 1; j < N; j++)
			if (mas[min] > mas[j])
				min = j;
		tmp = mas[min];
		mas[min] = mas[i];
		mas[i] = tmp;
	}
}


void quickSort(double* mas, int l, int r)
{
	int i = l;
	int j = r;
	double tmp = 0;
	double mid = mas[(l + r) / 2];
	do {
		while ((mas[i] < mid) && (i < r)) i++;
		while ((mas[j] > mid) && (j > l)) j--;
		if (i <= j)
		{
			tmp = mas[j];
			mas[j] = mas[i];
			mas[i] = tmp;
			i++;
			j--;
		}
	} while (i <= j);
	if (i < r)
		quickSort(mas, i, r);
	if (l < j)
		quickSort(mas, l, j);
}


void shellSort(double* mas, int N)
{
	int i, j, k;
	double tmp = 0;
	for (i = (N / 2); i > 0; i /= 2)
	{
		for (j = i; j < N; ++j)
		{
			for (k = j - i; (k >= 0) && (mas[k] > mas[k + i]); k -= i)
			{
				tmp = mas[k];
				mas[k] = mas[k + i];
				mas[k + i] = tmp;
			}
		}
	}
}


int sortNumber(const void* a, const void* b)
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

void check(int N, double* mas, double* mas1, double* mas2)
{
	int i;
	qsort(mas2, N, sizeof(double), sortNumber);
	for (i = 0; i < N; i++)
	{
		if (fabs(mas2[i] - mas1[i]) < (0.000000001))
		{
			printf_s(" Something went wrong\n");
			break;
		}
	}
	if (i == N)
		printf_s(" Verification passed successfully\n");
}


int main()
{
	int N = 1;
	int i;
	double* mas;
	double* mas1;
	double* mas2;
	int variant = 0;
	double startTime = 0;
	double endTime = 0;
	int f = 1;
	variant = printMenu1();
	switch (variant)
	{
	case 1:
	{
		f = 1;
		break;
	}
	case 2:
	{
		f = 0;
		N = inputArray();
		mas = (double*)malloc(N * sizeof(double));
		mas1 = (double*)malloc(N * sizeof(double));
		mas2 = (double*)malloc(N * sizeof(double));
		for (i = 0; i < N; i++)
			mas[i] = ((double)rand() / (double)RAND_MAX);
		for (i = 0; i < N; i++)
			mas1[i] = mas[i];
		startTime = clock();
		insertSort(N, mas1);
		endTime = clock();
		printf_s("insert Sort:    ");
		printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));
		check(N, mas, mas1, mas2);
		for (i = 0; i < N; i++)
			mas1[i] = mas[i];
		startTime = clock();
		selectionSort(N, mas1);
		endTime = clock();
		printf_s("selection Sort: ");
		printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));
		check(N, mas, mas1, mas2);
		for (i = 0; i < N; i++)
			mas1[i] = mas[i];
		startTime = clock();
		quickSort(mas1, 0, N - 1);
		endTime = clock();
		printf_s("quick Sort:     ");
		printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));
		check(N, mas, mas1, mas2);
		for (i = 0; i < N; i++)
			mas1[i] = mas[i];
		startTime = clock();
		shellSort(mas1, N);
		endTime = clock();
		printf_s("shell Sort:     ");
		printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));
		check(N, mas, mas1, mas2);
		free(mas);
		free(mas1);
		free(mas2);
		break;
	}
	}
	if (f == 1)
	{
		N = inputArray();
		mas = (double*)malloc(N * sizeof(double));
		mas1 = (double*)malloc(N * sizeof(double));
		mas2 = (double*)malloc(N * sizeof(double));
		for (i = 0; i < N; i++)
			mas[i] = ((double)rand() / (double)RAND_MAX);
		for (i = 0; i < N; i++)
			mas1[i] = mas[i];
		system("cls");
		variant = printMenu2();
		switch (variant)
		{
		case 1:
		{
			startTime = clock();
			insertSort(N, mas1);
			endTime = clock();
			check(N, mas, mas1, mas2);
			break;
		}
		case 2:
		{
			startTime = clock();
			selectionSort(N, mas1);
			endTime = clock();
			check(N, mas, mas1, mas2);
			break;
		}
		case 3:
			startTime = clock();
			quickSort(mas1, 0, N - 1);
			endTime = clock();
			check(N, mas, mas1, mas2);
			break;
		case 4:
			startTime = clock();
			shellSort(mas1, N);
			endTime = clock();
			check(N, mas, mas1, mas2);
			break;
		}

		printf("\n");
		printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));
		free(mas);
		free(mas1);
		free(mas2);
	}
	return 0;
}