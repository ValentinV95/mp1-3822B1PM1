#include <stdio.h>
#define N 200000000
#include <locale.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


void copy_arr(float* a, float* b, int na) {
    for (int i = 0; i < na;++i)
        b[i]=a[i];
}

int InputArray(float* a)
{
    //Функция создания массива
    int na;
    printf("Введите количество элементов в массиве: ");
    scanf_s("%d", &na);
    for (int i = 0; i < na; i++) {
        a[i] = (float)rand() / (float)(rand() + 0.1);
    }
    return na;
}


void PrintArray(float* a, int na)
{
    //Функция печати массива
    for (int i = 0; i < na; ++i)
        printf("%lf ", a[i]);
    printf("\n");
}

int menu_choice(char* menu[], int ns)
{
    // Функция выводит меню
    for (int i = 0; i < ns; i++) {
        printf("%s \n", menu[i]);
    }
    int n;
    printf("Введите номер опреации , которую необходимо выполнить: ");
    scanf_s("%d", &n);
    return n;
}

//Сдвиг элементов a[s],...,a[k-1] на одну позицию влево
void shift(float* a, int s, int k) {
    // s-номер первого сдвигаемого элемента; k- количество упорядоченных элементов
    for (int i = k; i > s; --i)
        a[i] = a[i - 1];
}


// Определение местоположения элемента R среди a[0]<=a[1]<=...<=a[k-1](Линейный поиск)
int place(float* a, float R, int k) {
    // R - новый элемент,положение которого необходимо найти
    // k - количество упорядоченных элементов в массиве

    int s = k, i = 0;
    for (; i < k; ++i) {
        if (a[i] > R) {
            s = i;
            break;
        }
    }
    return s;
}

//Бинарный поиск
int bplace(float* a, float R, int k)
{
    int st = 0;
    int mid;
    int fn = k - 1;
    int s;
    while (st < fn) {
        mid = (st + fn) / 2;
        if (R > a[mid]) st = mid + 1;
        else fn = mid - 1;
    }
    if (R > a[st]) s = st + 1;
    else s = st;
    return s;
}

//Сортировка вставками с линейным поиском
void insert(float* a, int na) {
    int k, s; float R;
    for (k = 1; k < na; ++k) {
        R = a[k];
        s = place(a, R, k);
        shift(a, s, k);
        a[s] = R;
    }
}

//Сортировка вставками с бинарным поиском
void Binsert(float* a, int na) {
    int k, s; float R;
    for (k = 1; k < na; ++k) {
        R = a[k];
        s = bplace(a, R, k);
        shift(a, s, k);
        a[s] = R;
    }
}

// Cортировка  Шелла
void Shell_Sort(float* array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                float temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}


//Поразрядная сортировка Radix_sort
void countByte(unsigned int* mas, int size, int count[256], int byte) {
    unsigned char* masc;
    int bias;
    int tmp1, tmp2;
    bias = sizeof(unsigned int);
    masc = (unsigned char*)mas;
    for (int i = 0; i < 256; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        count[masc[i * bias + byte]]++;
    }
    tmp1 = count[0];
    count[0] = 0;
    for (int i = 1; i < 256; i++) {
        tmp2 = count[i];
        count[i] = count[i - 1] + tmp1;
        tmp1 = tmp2;
    }
}

void radix_sort(unsigned int* mas, int size, unsigned int* mas_tmp) {
    unsigned char* masc = (unsigned char*)mas;
    int count[256];
    int sizetype = sizeof(unsigned int);
    for (int i = 0; i < sizetype; i++) {
        countByte(mas, size, count, i);
        for (int j = 0; j < size; j++) {
            mas_tmp[count[masc[j * sizetype + i]]++] = mas[j];
        }
        for (int j = 0; j < size; j++) {
            mas[j] = mas_tmp[j];
        }
    }
}

void radixFloat(float* mas, int n, float* mas_tmp) {
    int count = 0;
    int i = 0;
    radix_sort((unsigned int*)mas, n, (unsigned int*)mas_tmp);
    while (i < n) {
        if (mas[i] >= 0) {
            count++;
        }
        i++;
    }

    for (i = 0; i < count; i++)
        mas_tmp[i + (n - count)] = mas[i];
    for (; i < n; i++)
        mas_tmp[n - (++count)] = mas[i];
    for (int i = 0; i < n; i++)
        mas[i] = mas_tmp[i];
}
int compare(const void* a, const void* b) {
    const float* ac, * bc;
    ac = (const float*)a;
    bc = (const float*)b;

    if ((*ac - *bc) < 0) return -1;
    else
    {
        if ((*ac - *bc) > 0) return 1;
        else return 0;
    }
}

void correct_sort(float* a,int na,float* c){
    qsort(c,na,sizeof(float),compare);
    for (int i = 0; i < na; i++) {
        if (a[i] == c[i]) continue;
        else printf("!!!!!!!ОШИБКА!!!!!!! Массив упорядочен НЕКОРРЕКТНО. Проверка правильности была реализована с помощью стандартной сортировки qsort(). !!!!!!!ОШИБКА!!!!!!!\n ");
        break;
    }
}

void Sort_menu(int id_2, float* a, int na, float* b, float* c, float* a_tmp)
{
    double st, fn, raz;
    char* menu[5] = { "Сортировка вставками с линейным поиском (0)","Сортировка вставками с бинарным поиском (1)" ,"Сортировка Шелла (2)" ,"Поразрядная сортировка (3)","Вернуться в главное меню (4)" };
    while (1) {
        id_2 = menu_choice(menu, 5);
        switch (id_2)
        {
        case 0:
            st = clock();
            insert(a, na);
            fn = clock();
            raz = (fn - st) / (double)CLOCKS_PER_SEC;
            printf("-------->Ураааа!!! Массив отсортирован)<-------- \n");
            correct_sort(a, na, c);
            printf("-------->Время выполнения соритровки вставками с линейным поиском равно: %lf сек.<--------\n", raz);
            copy_arr(b, a, na);
            break;
        case 1:
            st = clock();
            Binsert(a, na);
            fn = clock();
            raz = (fn - st) / (double)CLOCKS_PER_SEC;
            printf("-------->Ураааа!!! Массив отсортирован)<-------- \n");
            correct_sort(a, na, c);
            printf("-------->Время выполнения соритровки вставками  с бинарным поиском равно: %lf сек.<-------- \n", raz);
            copy_arr(b, a, na);
            break;
        case 2:
            st = clock();
            Shell_Sort(a, na);
            fn = clock();
            raz = (fn - st) / (double)CLOCKS_PER_SEC;
            printf("-------->Ураааа!!! Массив отсортирован)<-------- \n");
            correct_sort(a, na, c);
            printf("-------->Время выполнения соритровки Шелла равно: %lf сек.<-------- \n", raz);
            copy_arr(b, a, na);
            break;
        case 3:
            st = clock();
            radixFloat(a, na, a_tmp);
            fn = clock();
            raz = (fn - st) / (double)CLOCKS_PER_SEC;
            printf("-------->Ураааа!!! Массив отсортирован)<-------- \n");
            correct_sort(a, na, c);
            printf("-------->Время выполнения поразрядной соритровки  равно: %lf сек.<-------- \n", raz);
            copy_arr(b, a, na);
            break;
        case 4:
            return;
        default:
            printf("-------->Don't know this number.... :( Please try again!!!<-------- \n");
            break;
        }

    }
}

void main()
{
    setlocale(LC_CTYPE, "Rus");
    printf("Дорогой пользователь! Данная программа создана , чтобы отсортировать элементы массива с помощью сортировки вставками, сортировки Шелла и поразрядной сортировки и узнать время работы каждой из сортировок ^^ \n");
    float* a_tmp = (float*)malloc(sizeof(float) * N);
    float* a = (float*)malloc(sizeof(float) * N);
    float* b = (float*)malloc(sizeof(float) * N);
    float* c = (float*)malloc(sizeof(float) * N);
    int na = 0;
    int id_1 = 0;
    int id_2 = 0;
    char* menu[3] = { "Ввести массив (0)","Выбрать сортировку (1)" ,"Выйти из программы (2)" };
    while (1) {
        id_1 = menu_choice(menu, 3);
        switch (id_1)
        {
        case 0:
            na = InputArray(a);
            copy_arr(a, b, na);
            copy_arr(a, c, na);
            break;
        case 1:
            Sort_menu(id_2, a, na, b,c, a_tmp);
            continue;
        case 2:
            return;
            break;
        default:
            printf("-------->Don't know this number.... :( Please try again!!!<-------- \n");
            break;
        }

    }

}
