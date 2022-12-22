#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void swap(double* a, double* b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void comb(double* arr, int n)
{
    double factor = 1.247;
    double step = n/factor;

    while (step - 1 > 0)
    {
        for (int i = 0; i + step < n; i++)
            {
            if (arr[i] > arr[i + (int)step])
                swap(&arr[i], &arr[i + (int)step]);
            }
        step /= factor;
    }
}

int compare(const void* a, const void* b)
{
    double x = *(double*)a;
    double y = *(double*)b;
    if (x < y) return -1;
    if (x == y) return 0;
    else return 1;
}

int validation(double* arr1, double* arr_origin, int size)
{
    int flag = 0;

    qsort(arr_origin, size, sizeof(double), compare);

    for (int j = 0; j < size; j++)
    {
        if (arr1[j] != arr_origin[j])
            flag++;
    }
    return flag;
}

void fill(double* arr1, double* arr2, int size)
{
    const int min = -1000000;
    const int max = 1000000;

    for (int j = 0; j < size; j++)
    {
        arr1[j] = (rand() / (double)RAND_MAX) * (max - min) + min;
        arr2[j] = arr1[j];

    }
}

int main()
{
    int amount = 0;
    double* array0 = NULL;
    double* array = NULL;
    int flag = -1;
    clock_t start, end;
    double timer = 0;

    scanf_s("%d", &amount);

    array = (double*)malloc(amount * sizeof(double));
    array0 = (double*)malloc(amount * sizeof(double));

    fill(array, array0, amount);

    start = clock();

    comb(array, amount);

    end = clock();

    timer = (end - start) / ((double)CLOCKS_PER_SEC);

    flag = validation(array, array0, amount);

    printf("validity: %d\ntime: %lf\n", flag, timer);

    free(array0);
    free(array);

    return 0;
}
