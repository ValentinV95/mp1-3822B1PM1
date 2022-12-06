#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<locale.h>

#define ll long long int
#define uchar unsigned char

// функция для замены элементов местами
void swap(double* a, double* b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

//функция для реверса массива
void reverse( double* mas, ll n, ll k)
{
	for (int i = 0; i < (n - k) / 2; ++i)
		swap(&mas[i], &mas[(n - k) - i - 1]);
}

//запоолняем исходный массив числами типа double
void filling(double* mas, ll n, ll* kol_negative)
{
	*kol_negative = 0;
	ll i;
	for (i = 0; i < n; ++i)
	{
		mas[i] = (double)rand() / (double)(rand() + 0.1);
		if (rand() % 2) { mas[i] = -mas[i]; ++*kol_negative; }
	}
}

//функция для копирования 1 массива в другой (используется для основного кода)
void copy_(double* mas_a, double* mas_b, ll n)
{
	ll i;
	for (i = 0; i < n; ++i) mas_b[i] = mas_a[i];
}

//реализация сортировки выбором 
void choice_sort(double* mas, ll n)
{
	ll i;
	for (i = 0; i < n - 1; ++i)
	{
		ll min = i;
		ll j;
		for (j = i + 1; j < n; ++j)
		{
			if (mas[j]-mas[min] < 0) min = j;
		}
		if (i != min) swap(&mas[i], &mas[min]);
	}
}

//реализация сортировки расческой
void comb_sort(double* mas, ll n)
{
	double factor = 1.247;
	double step = n / factor;
	while (step - 1 > 0)
	{
		ll i;
		ll st = step;
		for (i = 0; i + st < n; ++i)
		{
			if (mas[i] > mas[i + st])
				swap(&mas[i], &mas[i + st]);
		}
		step /= factor;
	}
}

// реализация поразрядной сортировки 
void radix_sort(double* mas,double* out, ll byte, ll n)
{
	uchar* masc = (uchar*)mas;

	ll counter[256];
	ll tmp;
	ll i;

	for (i = 0; i < 256; ++i) counter[i] = 0;// заполнение нулями, как количество байт

	for (i = 0; i < n; ++i) counter[masc[8 * i + byte]]++;//заполнение массива количеством байт
	
	tmp = counter[0];
	counter[0] = 0;

	for (i = 1; i < 256; ++i)
	{
		ll b = counter[i];
		counter[i] = tmp;
		tmp += b;
	}

	for (i = 0; i < n; ++i)
	{
		out[counter[masc[8 * i + byte]]] = mas[i];
		counter[masc[8 * i + byte]]++;
	}
}

//основная функция, из которой вызывается radix_sort 
// mas - основной массив
// n - кол-во элементов
// k - кол-во отрицательных элементов
void LSD(double* mas, ll n,ll k)
{
	ll i;
	double* out = (double*)malloc(n * sizeof(double));
	for (i = 0; i < 8; ++i)
	{
		(i % 2 == 0) ? radix_sort(mas, out, i, n) : radix_sort(out, mas, i, n);
	}

	reverse(mas, n, k);
	reverse(mas, n, 0);
}

// вспомогательная функция (компоратор) для qsort, которая сравнивает 2 числа в double
int compare(const void* a, const void* b)
{
	const double* ad, * bd;
	// так как принимаем указатели без типов данных мы должны в скобках укахзать сколько байт приходится на каждый элемент
	ad = (const double*)a;
	bd = (const double*)b;

	if ((*ad - *bd) < 0) return -1;
	else
	{
		if ((*ad - *bd) > 0) return 1;
		else return 0;
	}
}

//проверка на сортировку массива (юзаем qsort, который точно сортирует массив, а далее сравниваем результат с полученным массивом из qsort)
ll check(double* mas_a, double* mas_b, ll n)
{
	ll i;
	qsort(mas_a, n, sizeof(double), compare);
	//mas_a указатель на начало массива
	//n кол-во элементов
	//sizeof(double) размер каждого элемента
	for (i = 0; i < n; ++i)
	{
		if (abs(mas_a[i] - mas_b[i]) > 1e-16)
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	srand(time(0));
	setlocale(LC_CTYPE, "RUS");
	ll x = 1;
	printf("привет пользователь!\nДанная программа предназначена для сравнения сортировок Выбором, Расческой и Поразрядной.\nВсе тесты будут проходить на типе double.\n");
	while (x)
	{
		printf("ввести кол-во элементов в массиве.\n");
		ll n;
		scanf_s("%llu", &n);
		ll button = 1;
		ll kol_negative = 0;
		double* mas_a = (double*)malloc(n * sizeof(double));
		double* mas_b = (double*)malloc(n * sizeof(double));
		double* mas_c = (double*)malloc(n * sizeof(double));
		filling(mas_a, n, &kol_negative);
		while (button == 1)
		{
			printf("\n");
			printf("Menu:\n");
			printf("Выбором - 1\n");
			printf("Расческой - 2\n");
			printf("Поразрядная - 3\n");
			printf("смена кол-ва элементов массива- 4\n");
			printf("Выход - 5\n");
			int k;
			scanf_s("%d", &k);

			switch (k)
			{
				case 1:
				{
					clock_t start, finish;
					copy_(mas_a, mas_b, n);
					copy_(mas_a, mas_c, n);
					start = clock();
					choice_sort(mas_b, n);
					finish = clock();
					ll ch = check(mas_c, mas_b, n);
					if (ch)
					{
						printf("Массив отсортирован успешно\n");
						printf("Время сортировки: %d секунд\n", (finish - start) / CLOCKS_PER_SEC);
					}
					else printf("Ошибка, массив не отсортировался\n");
					break;
				}
				case 2:
				{
					clock_t start, finish;
					copy_(mas_a, mas_b, n);
					copy_(mas_a, mas_c, n);
					start = clock();
					comb_sort(mas_b, n);
					finish = clock();
					ll ch = check(mas_c, mas_b, n);
					if (ch)
					{
						printf("Массив отсортирован успешно\n");
						printf("Время сортировки: %d секунд\n", (finish - start)/ CLOCKS_PER_SEC);
					}
					else printf("Ошибка, массив не отсортировался\n");
					break;
				}
				case 3:
				{
					clock_t start, finish;
					copy_(mas_a, mas_b, n);
					copy_(mas_a, mas_c, n);
					start = clock();
					LSD(mas_b, n, kol_negative);
					finish = clock();

					ll ch = check(mas_c, mas_b, n);
					if (ch)
					{
						printf("Массив отсортирован успешно\n");
						printf("Время сортировки: %d секунд\n", (finish - start) / CLOCKS_PER_SEC);
					}
					else printf("Ошибка, массив не отсортировался\n");
					break;
				}
				case 4:
				{
					printf("ввести кол-во элементов в массиве.\n");
					scanf_s("%llu", &n);

					mas_a = (double*)malloc(n * sizeof(double));
					mas_b = (double*)malloc(n * sizeof(double));
					mas_c = (double*)malloc(n * sizeof(double));
					filling(mas_a, n, &kol_negative);
					break;
				}
				case 5:
				{
					printf("спасибо за работу!\n");
					button = 0;
				}
				default:
					break;
				
			}
		}
		if (button == 0) break;
	}
}