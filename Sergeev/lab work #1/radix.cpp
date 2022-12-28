#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int compare(const void* a, const void* b)
{
    double x = *(double*)a;
    double y = *(double*)b;
    if (x < y) return -1;
    if (x == y) return 0;
    else return 1;
}

void countbyte(unsigned long long int * arr, int n, int count[256], int byte)
{
    unsigned char* arrC;
    int bias;
    int tmp, temp;

    bias = sizeof(unsigned long long int);
    arrC = (unsigned char*)arr;
    
    for (int i = 0; i < 256; i++)
        count[i] = 0;

    for (int j = 0; j < n; j++)
        count[arrC[j * bias + byte]]++;

    tmp = count[0];
    
    for (int i = 1; i < 256; i++)
    {
        temp = count[i];
        count[i] = tmp;
        tmp += temp;
    }

    count[0] = 0;
}

void uint_radix_sort(unsigned long long int* arr, int size, unsigned long long int* arr_tmp)
{
    unsigned char* arrc = (unsigned char*)arr;
    int sizetype = sizeof(unsigned long long int);
    int count[256];

    for (int i = 0; i < sizetype; i++)
    {
        countbyte(arr, size, count, i);

        for (int j = 0; j < size; j++)
            arr_tmp[count[arrc[j * sizetype + i]]++] = arr[j];

        for (int k = 0; k < size; k++)
            arr[k] = arr_tmp[k];
    }
}

void radix_double(double* arr, double* tmp, int n)
{
    int count = 0, i;
    uint_radix_sort((unsigned long long int*)arr, n, (unsigned long long int*) tmp);
    while (count < n && arr[count++]>0);
    count--;
    for (i = 0; i < count; i++)
        tmp[n-count+i] = arr[i];

    for (; i < n; i++)
        tmp[n - (++count)] = arr[i];
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
        arr1[j] = (rand() / (double) RAND_MAX)*(max-min)+min;
        arr2[j] = arr1[j];

    }
}

int main()
{
    int amount = 0;
    double* array = NULL;
    double* array2 = NULL;
    double* array0 = NULL;
    int flag = -1;
    clock_t start, end;
    double timer = 0;

    scanf_s("%d", &amount);

    array = (double*)malloc(amount * sizeof(double));
    array2 = (double*)malloc(amount * sizeof(double));
    array0 = (double*)malloc(amount * sizeof(double));

    fill(array, array0, amount);

    start = clock();

    radix_double(array, array2, amount);

    end = clock();

    timer = (end - start) / ((double)CLOCKS_PER_SEC);

    flag = validation(array2, array0, amount);

    printf("validity: %d\ntime: %lf\n", flag, timer);

    free(array0);
    free(array2);
    free(array);

    return 0;
}