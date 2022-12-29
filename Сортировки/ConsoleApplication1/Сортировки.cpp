#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "locale.h"

int compare(const void* a, const void* b)
{
    const float* arg1, * arg2;
    arg1 = (const float*)a;
    arg2 = (const float*)b;
    if ((*arg1 - *arg2) < 0) return -1;
    else
    {
        if ((*arg1 - *arg2) > 0) return 1;
        else return 0;
    }
}
int check(float* mas_a, float* mas_b, int size)
{
    qsort(mas_a, size, sizeof(float), compare);
    for (int i = 0; i < size; i++)
        if ((mas_a[i] - mas_b[i]) > 1e-8 || (mas_a[i] - mas_b[i]) < -(1e-8))
            return 0;
    return 1;
}

void* malloc(size_t size);

float* creature(int size)
{
    float* mas;
    mas = (float*)malloc(sizeof(float*) * size);
    for (int i = 0; i < size; i++)
       mas[i] =rand() + ((float)rand() / ((float)RAND_MAX));
    return mas;
}

void swap(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble(float* array, int size)
{
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        flag = 0;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                flag = 1;
            }

        }
        if (flag == 0) return;
    }

}

void Insert(float* array, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i; j > 0; j--)
            if (array[j] < array[j - 1])
                swap(&array[j], &array[j - 1]);
            else break;
}

int partition(float* mas, int l, int r)
{
    int tmp = l + (r - l) / 2;
    float  mid = mas[tmp];
    while (l < r)
    {

        while ((mas[l] < mid) && (l != r))
            l++;
        while ((mas[r] > mid) && (r != l))
            r--;
        if (mas[r] == mid && r != tmp && r != l)
        {
            swap(&mas[r], &mas[l]);
            r--;
        }
        else if (mas[l] == mid && l != tmp && r != l)
        {
            swap(&mas[r], &mas[l]);
            l++;
        }
        else swap(&mas[r], &mas[l]);
        
    }
    return r;
}
void comb(float* arr, int size)
{
    float factor = 1.246;
    int step = size - 1;
    while (step != 0)
    {
        for (int i = 0; i + step < size; i++)
            if (arr[i] > arr[i + step])
                swap(&arr[i], &arr[i + step]);
        step /= factor;
    }

}

void  Quicksort(float* array, int left, int right)
{
    if (left <= right)
    {
        int p = partition(array, left, right);
        Quicksort(array, left, p-1);
        Quicksort(array, p+1, right);
    }

}

int main()
{
    clock_t start, finish;
    int n, vibor, itog, nachalo;
    float* arr;
    float* arr1;
    setlocale(LC_ALL, "Rus");
    printf("Выберите сортировку\n");
    printf("1 - сортировка пузырьком\n");
    printf("2 - сортировка вставками\n");
    printf("3 - сортировка Хоара\n");
    printf("4 - сортировка расческой\n");
    scanf_s("%i", &vibor);
    printf("Введите количество элементов\n");
    scanf_s("%i", &n);
    arr = creature(n);
    arr1 = (float*)malloc(sizeof(float*) * n);
    for (int i = 0; i < n; i++)
        arr1[i] = arr[i];
    printf("5 - Вывод массива \n");
    scanf_s("%i", &nachalo);
    if (nachalo == 5)
        for (int i = 0; i < n; i++)
            printf("%f ", arr[i]);
    printf("\n");
    if (vibor == 1)
    {
        start = clock();
        bubble(arr, n);
        finish = clock();
    }
    else if (vibor == 2)
    {
        start = clock();
        Insert(arr, n);
        finish = clock();
    }
    else if (vibor == 3)
    {
        start = clock();
        Quicksort(arr, 0, n-1);
        finish = clock(); 
    }
    else if (vibor == 4)
    {
        start = clock();
        comb(arr, n);
        finish = clock();
    }
    printf("6 - Вывод отсортированного массива \n");
    scanf_s("%i", &itog);
    if (itog == 6)
        for (int i = 0; i < n; i++)
            printf("%f ", arr[i]);
    printf("\n");
    printf("Время, коорое потребовалось : ");
    printf("%f\n", (finish - start) / (double)(CLOCKS_PER_SEC));
    printf("Проверка корректности: ");
    if (check(arr1, arr, n) == 1)
        printf("Сортировка работает корректно");
    else
        printf("Сортировка работает некорректно");
    return 0;
}
