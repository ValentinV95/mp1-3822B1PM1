#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "math.h"
#include "time.h" 

#define true 1
#define N 10

void test(unsigned int* mas, int size, int count[256], int byte);
int menu();
void swap(float mas[], int i, int j);
int bubble(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm);
void ckoarrr(float mas[], int l, int r, long long int* p_count_comp, long long int* p_count_perm);
int middle(float mas[], int l, int r, long long int* p_count_comp, long long int* p_count_perm);
void insert_sort(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm);
void shift(float mas[], int first_el, int last_el);
void shell(int array[], int size, long long int* p_count_comp, long long int* p_count_perm);
void sort_menu(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm, clock_t* start, clock_t* end);
int check_result(float mas[], int len_mas);
void test_sort(float sortmas[], float unsortmas[], int len_mas);
int compare(const void* a, const void* b);
void* malloc(size_t size);
int test_result(float rmas[], float mas[]);

int main()
{
    float* mas = NULL;//исходный массив
    float* dmas = NULL; //дублированный массив
    int len_mas = 0; //длинна массива
    long long int count_comp = 0; //количество сравнений
    long long int* p_count_comp = &count_comp;
    long long int count_perm = 0; // количество перестановок
    long long int* p_count_perm = &count_perm;
    clock_t start = 0, end = 0; //начало выполнения сортировки, конец выполнения сортировки
    double time = 0.0; //время выполнения сортировки
    int flag = 1;
    int i;

    setlocale(LC_CTYPE, "Rus");
    while (flag)
    {
        switch (menu())
        {
        case 1:
            printf_s("Введите размер массива: ");
            scanf_s("%d", &len_mas);
            mas = (float*)malloc(sizeof(float) * len_mas);
            dmas = (float*)malloc(sizeof(float) * len_mas);
            for (i = 0; i < len_mas; i++)
            {
                mas[i] = (rand() / 100.0);
                dmas[i] = mas[i];
            }
            break;
        case 2:
            if (len_mas != 0)
            {
                sort_menu(dmas, len_mas, p_count_comp, p_count_perm, &start, &end);
                test_sort(dmas, mas, len_mas);
                printf_s("Количество сравнений при выполнении сортировки: %ld \n", count_comp);
                printf_s("Количество перестановок при выполнении сортировки: %ld \n", count_perm);
                time += (end - start)/ (double)(CLOCKS_PER_SEC);
                printf_s("Время выполнения сортировки: %f \n", time);
                time = 0.0; start = 0, end = 0;
                count_comp = 0;
                count_perm = 0;
                for (i = 0; i < len_mas; i++)
                {
                    dmas[i] = mas[i];
                }
                break;
            }
            else
            {
                printf("\nСначала необходимо ввести массив!!!\n");
                break;
            }
        case 3:
            flag = 0;
            break;
        }
    }
    return 0;
}

int menu()
{
    int choice;
    printf_s("\n        Меню\n1.Ввести новый массив.\n2.Выбрать сортировку.\n3.Закрыть программу.\nВыберите действие: ");
    scanf_s("%d", &choice);
    return choice;
}

void sort_menu(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm, clock_t* start, clock_t* end)
{
    int turn; // переменная выбора сортировки
    printf_s("\n1.Сортировка пузырьком.\n2.Сортировка Хоара.\n3.Сортировка вставками.\n4.Сортировка Шелла.\nВыберите сортировку: ");
    scanf_s("%d", &turn);
    switch (turn)
    {
    case 1:
        *start += clock();
        bubble(mas, len_mas, p_count_comp, p_count_perm);
        *end += clock();
        break;
    case 2:
        *start = clock();
        ckoarrr(mas, 0, len_mas - 1, p_count_comp, p_count_perm);
        *end = clock();
        break;
    case 3:
        *start = clock();
        insert_sort(mas, len_mas, p_count_comp, p_count_perm);
        *end = clock();
        break;
    case 4:
        *start = clock();
        shell(mas, len_mas, p_count_comp, p_count_perm);
        *end = clock();
        break;
    }
}

void swap(float mas[], int i, int j)
{
    float tmp;
    tmp = mas[i];
    mas[i] = mas[j];
    mas[j] = tmp;
}

/*int input(int* mas)
{
    int i; //если все еще не будет работать, переместить в main
    int N;
    printf_s("Введите размер массива: ");
    scanf_s("%d", &N);
    mas = (int*)malloc(sizeof(int) * N);
    for (i = 0; i < N; i++)
    {
        printf_s("Введите элемент массива:");
        scanf_s("%d", &mas[i]);
    }
    for (i = 0; i < N; i++)
    {
        printf_s("%d", mas[i]);
    }
    return N;
}*/

int bubble(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm)
{
    int flag;
    int i, j;
    for (i = 0; i < len_mas - 1; i++)
    {
        *p_count_comp += 1;
        flag = 0;
        for (j = 0; j < len_mas - 1 - i; j++)
        {
            *p_count_comp += 1;
            if (mas[j] > mas[j + 1])
            {
                swap(mas, j, j + 1);
                *p_count_perm += 1;
                flag = 1;
            }
            *p_count_comp += 1;
        }
        if (flag == 0)
        {
            *p_count_comp += 1;
            break;
        }
        *p_count_comp += 1;
    }

    return 0;
}

void ckoarrr(float mas[], int l, int r, long long int* p_count_comp, long long int* p_count_perm)
{
    int mid;
    if (l < r)
    {
        *p_count_comp += 1;
        mid = middle(mas, l, r, p_count_comp, p_count_perm);
        ckoarrr(mas, l, mid, p_count_comp, p_count_perm);
        ckoarrr(mas, mid + 1, r, p_count_comp, p_count_perm);
    }
}
int middle(float mas[], int l, int r,long int* p_count_comp,long int* p_count_perm)
{
    float main_element = mas[(l + r) / 2];
    while (true)
    {
        while (mas[l] < main_element) { l++; *p_count_comp+=1; }
        while (mas[r] > main_element) { r--; *p_count_comp+=1; }

        if (l >= r) return r;
        *p_count_comp += 1;
        swap(mas, l, r);
        *p_count_perm += 1;
        l++; r--;
    }
}

void insert_sort(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm)
{
    int i, j;
    float tmp;
    for (i = 1; i < len_mas; i++)
    {
        *p_count_comp += 1;
        for (j = 0; j < i; j++)
        {
            *p_count_comp += 1;
            if (mas[i] < mas[j])
            {
                tmp = mas[i];
                shift(mas, j, i, p_count_comp);
                *p_count_perm += (i - j);
                mas[j] = tmp;
            }
            *p_count_comp += 1;
        }
    }
}
void shift(float mas[], int first_el, int last_el, long long int* p_count_comp)
{
    int i;
    for (i = last_el; i > first_el; i--)
    {
        *p_count_comp += 1;
        mas[i] = mas[i - 1];
    }
}

void shell(float mas[], int len_mas, long long int* p_count_comp, long long int* p_count_perm)
{
    int step;
    int i, j;
    for (step = len_mas / 2; step > 0; step /= 2)
    {
        *p_count_comp += 1;
        for (i = step; i < len_mas; ++i)
        {
            *p_count_comp += 1;
            for (j = i - step; j >= 0; j -= step)
            {
                *p_count_comp += 1;
                if (mas[j] < mas[j + step]) break;
                else
                {
                    swap(mas, j, j + step);
                    *p_count_perm += 1;
                }
                *p_count_comp += 1;
            }
        }
    }
}

void test_sort(float sortmas[], float unsortmas[], int len_mas)
{
    float* dunsortmas = (float*)malloc(sizeof(float) * len_mas);
    int flag = 0;
    int i;
    for (i = 0; i < len_mas; i++)
    {
        dunsortmas[i] = unsortmas[i];
    }
    qsort(dunsortmas, len_mas, sizeof(float), compare);
    for (i = 0; i < len_mas; i++)
    {
        if (sortmas[i] != dunsortmas[i])
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0) printf("\nВаш массив был успешно отсортирован!\n");
    else printf("\nПроизошла ошибка, массив отсортирован неверно!!!\n");
}

int compare(const void* a, const void* b)
{
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
}

int check_result(float mas[], int len_mas)
{
    int i;
    printf("[ ");
    for (i = 0; i < len_mas; i++)
    {
        printf("%f ", mas[i]);
    }
    printf("]\n");
    return 0;
}