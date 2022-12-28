#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int n; 
int type;

int comp(void* x1, void* x2)
{
    if (*(double*)x1 > *(double*)x2) return 1;
    else
    {
        if (*(double*)x1 < *(double*)x2) return -1;
        else return 0;
    }
}

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

int partition(double* a, int l, int r)
{
    double mid = a[l + (r - l) / 2];
    while (l < r)
    {
        while ((a[l] < mid) && (l < r)) l++;
        while ((a[r] > mid) && (l < r)) r--;
        if (l < r) 
        { 
            if (a[l] > a[r]) swap(&a[l], &a[r]);
            else if (fabs(a[l] - a[r]) < 0.0000000001) r--;
        }
    }
    return l;
}

void quicksort(double* a, int l, int r)
{
    int p;
    if (l < r)
    { 
        p = partition(a, l, r);
        quicksort(a, l, p);
        quicksort(a, p + 1, r);
    }
}

void insert(double* a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; (j > 0) && (a[j] < a[j - 1]); --j)
        {
            swap(&a[j], &a[j - 1]);
        }
    }
}

void countByte(unsigned long long* mas, int т, int count[256], int Byte) //исходный массив, размер массива, массив чаров, текущий разряд
{  
    int i, tmp1, tmp2;	//временная переменная 
    unsigned char* masc = (unsigned char*)mas;
    int bias = sizeof(unsigned long long);	//он хранит размер беззнакового инта
    for (i = 0; i < 256; ++i) count[i] = 0;
    for (i = 0; i < n; ++i) count[masc[i * bias + Byte]]++;
    
    tmp1 = count[0];		//распределяю по индескам куда ставить числа
    count[0] = 0;
    for (i = 1; i < 256; ++i) 
    {
        tmp2 = count[i];
        count[i] = count[i - 1] + tmp1;  //теперь в count лежат индексы, на которые нужно ставить числа каждого индекса массива
        tmp1 = tmp2;
    }
}

void radix_unsigned(unsigned long long* mas, int n, unsigned long long* mas_tmp) 
{
    unsigned char* masc = (unsigned char*)mas;  //копирую массив чаров
    int count[256];
    int i, j, sizetype = sizeof(unsigned long long);
    for (i = 0; i < sizetype; i++) 
    {
        countByte(mas, n, count, i);		//где i - это номер разряда
        for (j = 0; j < n; ++j)     mas_tmp[count[masc[j * sizetype + i]]++] = mas[j];
        for (j = 0; j < n; ++j) 	mas[j] = mas_tmp[j];
    }
}

void radix_double(double* mas, int n, double* mas_tmp) 
{
    int count = 0;
    int i = n - 1;
    radix_unsigned((unsigned long long*)mas, n, (unsigned long long*)mas_tmp);
    while (i >= 0 && mas[i] < 0) //Считаем количество положительных чисел
    {		
        mas_tmp[count++] = mas[i];
        i--;
    }
    i = 0;
    for (count; count < n; ++count)    mas_tmp[count] = mas[i++];
    for (i = 0; i < n; ++i)    mas[i] = mas_tmp[i];
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int repeat = 1;
    while (repeat)
    {
        printf("Введите количество элементов сортируемого массива: ");
        scanf_s("%d", &n);        
        double* a = (double*)malloc(sizeof(double) * n);
        double* b = (double*)malloc(sizeof(double) * n);
        double* c = (double*)malloc(sizeof(double) * n);
        for (int i = 0; i < n; ++i)
        {
            double k = ((double)rand() / RAND_MAX);
            a[i] = k;
            b[i] = k;
        }
        clock_t st = clock();
        qsort(b, n, sizeof(double), comp);
        clock_t fin = clock(); 
        double timeq = (double)(fin - st) / CLOCKS_PER_SEC;
        printf("Выберите тип сортировки: \n\t 1. Сортировка вставками \n\t 2. Сортировка Хоара\n\t 3. Поразрядная сортировка\nВведите номер: ");
        scanf_s("%d", &type);
        if (type == 1)
        {
            st = clock();
            insert(a, n);
            fin = clock();
        }
        if (type == 2)
        {
            st = clock();
            quicksort(a, 0, n - 1);
            fin = clock();
        }
        if (type == 3)
        {
            st = clock();
            radix_double(a, n, c);
            fin = clock();
        }
        int l = 0;
        for (int i = 0; i < n; ++i)
        {
            // printf("%lf  %lf  %d\n", a[i], b[i], i);
            if (b[i] - a[i])
            {
                //printf("здесь не работает\n");
                l++;
            }
        }
        if (l) printf("НЕ РАБОТАЕТ"); 
        double times = (double)(fin - st) / CLOCKS_PER_SEC;
        printf("Время работы выбранной сортировки: %lf секунд\n", times);
        printf("Время работы встроенной сортировки: %lf секунд\n", timeq);
        printf("\nВыполнить программу ещё раз? (0 - нет, 1 - да): ");
        scanf_s("%d", &repeat);
        free(a);
        free(b);
    }
}
