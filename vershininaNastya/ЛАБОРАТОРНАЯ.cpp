#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int printMenu1()
{
	int variant; int N;
	printf("~ ~ ~ ~ ~ ~ ~ ~ \n");
	printf("1. Set an array\n");
	printf("~ ~ ~ ~ ~ ~ ~ ~ \n");
	scanf_s("%d", &variant);
	if (variant < 1 || variant > 1)
	{
		do
		{
			system("cls");
			printf("\nError.Try again.\n");
			printMenu1();
		} while (variant == 1);
	}
	system("cls");
	return variant;
}
int inputArray()
{
	int N;
	printf_s("Set the number of elements in the array\n");
	scanf_s("%d", &N);
	if (N < 1)
	{
		do
		{
			system("cls");
			printf("Error. Try again.\nSet the number of elements in the array\n");
			scanf_s("%d", &N);
		} while (N > 0);
	}
	return N;
}

int printMenu2()
{
	int variant;
	printf("~ Sorting Selection ~\n");
	printf("1.Insert Sort\n");
	printf("2.Selection Sort\n");
	printf("3.Hoara Sort\n");
	printf("4.Shell Sort\n");
	printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	scanf_s("%d", &variant);
	if ((variant < 1) || (variant > 4))
	{
		do
		{
			system("cls");
			printf("Error.Try again\n");
			printMenu2();
		} while ((variant < 5) && (variant > 0));
	}
	return variant;
}

void insertSort(int N, int* mas)
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

void selectionSort( int N, int* mas)
{
	int i, j, min, tmp;
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

void quickSort(int* mas, int l, int r)
{
	int i = l;
	int j = r;
	int tmp = 0;
	int mid = mas[(l + r) / 2];
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

void shellSort(int* mas, int N)
{
	int i, j, k, tmp = 0;
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

int main()
{
	//N- число элементов в массиве 
	int N = 1;
	int i,*mas;//указатель на массив
	int variant=0;
	double startTime = 0;
	double endTime = 0;
	variant=printMenu1();
	switch (variant)
	{
	case 1:
	{
		N = inputArray();
		break;
	}
	}
	mas = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
		mas[i] = rand();
	system("cls");
	variant=printMenu2();
	switch (variant)
	{
	case 1:
	{
		//for (i = 0; i < N; i++)
			//rintf_s("%d ", mas[i]);
		//printf_s("\n");
		startTime = clock();
		insertSort(N, mas);
		endTime = clock();
		//for (i = 0; i < N; i++)
			//printf_s("%d ", mas[i]);
		printf_s("\n");
		break;
	}
	case 2:
	{
		startTime = clock();
		selectionSort(N,mas);
		endTime = clock();
		break;
	}
	case 3:
		startTime = clock();
		quickSort(mas, 0, N - 1);
		endTime = clock();
		break;
	case 4:
		startTime = clock();
		shellSort(mas, N);
		endTime = clock();
		break;
	}

	printf("\n");
	printf("%f", ((double)(endTime - startTime) / CLOCKS_PER_SEC));

	free(mas);
	return 0;
}
