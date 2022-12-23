#include "stdio.h"
#include "cstdlib"
#include "locale.h"
#include "time.h"
#include "string.h"

int menu() {
    int v;
    printf_s("1. Задать массив\n2. Отсортировать массив\n3. Выход\n");
    scanf_s("%d", &v);
    return v;
}

void swap(float*  a, float* b) {
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(float* arr, int n) {
    int i, j;
    int flag = 0;
    for (i = 0; i < n; i++) {
        flag = 0;
        for (j = 0; j < n - 1-i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }

}


void merge(float* in, float* out, int l, int m, int r) {
    int l1, l2;
    int index = 0;
    l1 = l;
    l2 = m + 1;
    while (l1 <= m && l2 <= r) {
        if (in[l1] <= in[l2]) {
            out[index++] = in[l1++];
        }
        else {
            out[index++] = in[l2++];
        }
    }
    while (l1 > m && l2 <= r) {
        out[index++] = in[l2++];
    }
    while (l2 > r && l1 <= m) {
        out[index++] = in[l1++];
    }
    for (int i = 0; i < index; i++) {
        in[l + i] = out[i];
    }
}

void merge_sort(float* arr, float* tmp, int l, int r) {
    int m = l + ((r - l) / 2);
    if (l == r) {
        return;
    }
    merge_sort(arr, tmp, l, m);
    merge_sort(arr, tmp, m + 1, r);
    merge(arr, tmp, l, m, r);
}



void countByte(unsigned int* arr, int size, int count[256], int Byte) {  //исхоодный массив, размер массива, символьный массив, текущий разряд
    int tmp1, tmp2;	//временная переменная 
    int i;
    unsigned char* arrc = 0;	// символьный массив																
    arrc = (unsigned char*)malloc(sizeof(unsigned char) * size); //?????????????/
    int bias;	//cмещение (нужен для отрицательных чисел, потому что (-5 = -5 + bias) в беззнаковой системе
    bias = sizeof(unsigned int);	//он хранит размер беззнакового инта
    arrc = (unsigned char*)arr; //делаю массив символов из предыдущего массива
    for (i = 0; i < 256; i++) { //заполняю вспомогательный массив  нулями
        count[i] = 0;
    }
    for (i = 0; i < size; i++) {   //накидываю сколько раз определенное число входило в массив
        count[arrc[i * bias + Byte]]++; //??????????
    }
    tmp1 = count[0];		//распределяю по индескам куда ставить числа
    count[0] = 0;
    for (i = 1; i < 256; i++) {
        tmp2 = count[i];
        count[i] = count[i - 1] + tmp1;  //теперь в count лежат индексы, на которые нужно ставить числа каждого индекса массива
        tmp1 = tmp2;
    }

}

void radix_sort(unsigned int* arr, int size, unsigned* arr_tmp) {
    unsigned char* arrc = (unsigned char*)arr;  //копирую массив чаров
    int count[256];
    int sizetype = sizeof(unsigned int);
    int i, j;
    for (i = 0; i < sizetype; i++) {
        countByte(arr, size, count, i);		//где i - это номер разряда
        for (j = 0; j < size; j++) {	//Заполняем числами с выведенной индексацией
            arr_tmp[count[arrc[j * sizetype + i]]++] = arr[j];
        }
        for (j = 0; j < size; j++) {	//Из временного массива в основной
            arr[j] = arr_tmp[j];
        }
    }
}

void radixFloat(float* arr, float* arr_tmp, int N) {
    int count = 0;
    int i = 0;
    radix_sort((unsigned int*)arr, (unsigned int)N, (unsigned int*)arr_tmp);
    while (i < N) {		//Считаем количество положительных чисел
        if (arr[i]  >= 0) {
            count++;
        }
        i++;
    }   
    for (i = 0; i < count; i++) {
        arr_tmp[N - count + i] = arr[i];
    }
    count = N - count;
    for (count = count--; count >= 0; count--) {
        arr_tmp[count] = arr[i++];
    }

    for (i = 0; i < N; i++) {
        arr[i] = arr_tmp[i];
    }
}

int compare(const void* a, const void* b)
{
    const float* ad, * bd;
    ad = (const float*)a;
    bd = (const float*)b;

    if ((*ad - *bd) < 0) return -1;
    else
    {
        if ((*ad - *bd) > 0) return 1;
        else return 0;
    }
}

int check(float* arr, float* arrforsort, int n) {
    int f = 0;
    int i = 0;
    float* qarr = 0;
    qarr = (float*)malloc(sizeof(float) * n);
    qarr = arr;
    qsort(qarr, n, sizeof(float*), compare);
    for (i = 0; i < n; i++) {
        if (qarr[i] != arrforsort[i]) {
            return 0;
        }
    }
    return 1;
}


int main()
{
    int v, n, v2, v3, i;
    float* arrforsorts = 0;
    float* arr = 0;
    clock_t start, end;
    setlocale(LC_ALL, "Rus");
    while (true) {
        int f = 0;
        printf("Введите цифру, которая ссответсвует вашему выбору:\n");
        v = menu();
        switch (v) {
        case(1):
        {
            
            printf("Укажите размерность массива:\n");
            scanf_s("%d", &n);
            arr = (float*) malloc(sizeof(float) * n);
            arrforsorts = (float*)malloc(sizeof(float) * n);
          
            printf("1. Заполнить с клавиатуры\n2. Заполнить автоматически (-1000 <= рандом < 1000)\n");
            scanf_s("%d", &v2);
            switch (v2) {
            case(1):
            {
                printf("Введите %d чисел:\n", n);
                for (i = 0; i < n; i++) {
                    printf("%d. ", i + 1);
                    scanf_s("%f", &arr[i]);
                    arrforsorts[i] = arr[i];
                }
                continue;
            }
            case(2):
            {
                for (i = 0; i < n; i++) {
                    arr[i] = (((float) rand() / RAND_MAX) * 1000) - (((float)rand() / RAND_MAX) * 1000);
                    arrforsorts[i] = arr[i];
                }
                continue;
            }
        
            default:
            {
                free(arrforsorts);
                free(arr);
                continue;
            }
            }
        }
        case (2):
        {
            printf("Выберите номер сортировки:\n1. Сортировка пузырьком\n2. Сортировка слиянием\n3. Поразрядная сортировка\n");
            scanf_s("%d", &v3);
            switch(v3) { 
                case(1): 
                {
                    start = clock();
                    bubble_sort(arrforsorts , n);
                    end = clock();
                    if (check(arr, arrforsorts, n) == 1) {
                        printf_s("OK\n");
                        printf_s("%d\n", (end - start));
                    }
                    else printf_s("ERORR!\n");
                    continue;
                }
                case(2):
                {
                    float* out = 0;
                    out = (float*)malloc(sizeof(float)*n);
                    start = clock();
                    merge_sort(arrforsorts, out, 0, n-1);
                    end = clock();
                    if (check(arr, arrforsorts, n) == 1) {
                        printf_s("OK\n");
                        printf_s("%d\n", (end - start));
                    }
                    else printf_s("ERORR!\n");
                    free(out);
                    continue;
                }
                case(3):
                {
                    float* arr_tmp = (float*)malloc(sizeof(float) * n);
                    start = clock();
                    radixFloat(arrforsorts, arr_tmp, n);
                    end = clock();
                    if (check(arr, arrforsorts, n) == 1) {
                        printf_s("OK\n");
                        printf_s("%d\n", (end - start));
                    } 
                    else printf_s("ERORR!\n");
                    free(arr_tmp);
                    continue;
                }
            }
        }
        case(3):
        {
            f = 1;
        }
        default:
        {
            free(arr);
            break;
        }
        }
        if (f == 1) {
         
            break;
        }
        free(arrforsorts);
        free(arr);
    }
   

}

