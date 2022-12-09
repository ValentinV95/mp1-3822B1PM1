#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<locale.h>

#define ll long long int
#define uchar unsigned char

// ôóíêöèÿ äëÿ çàìåíû ýëåìåíòîâ ìåñòàìè
void swap(double* a, double* b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

//ôóíêöèÿ äëÿ ðåâåðñà ìàññèâà
void reverse( double* mas, ll n, ll k, ll* kol_permutation)
{
	for (int i = 0; i < (n - k) / 2; ++i)
	{
		++*kol_permutation;
		swap(&mas[i], &mas[(n - k) - i - 1]);
	}
}

//çàïîîëíÿåì èñõîäíûé ìàññèâ ÷èñëàìè òèïà double
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

//ôóíêöèÿ äëÿ êîïèðîâàíèÿ 1 ìàññèâà â äðóãîé (èñïîëüçóåòñÿ äëÿ îñíîâíîãî êîäà)
void copy_(double* mas_a, double* mas_b, ll n)
{
	ll i;
	for (i = 0; i < n; ++i) mas_b[i] = mas_a[i];
}

//ðåàëèçàöèÿ ñîðòèðîâêè âûáîðîì 
void choice_sort(double* mas, ll n, ll* kol_comparison, ll* kol_permutation)
{
	ll i;
	for (i = 0; i < n - 1; ++i)
	{
		ll min = i;
		ll j;
		for (j = i + 1; j < n; ++j)
		{
			++*kol_comparison;
			if (mas[j]-mas[min] < 0) min = j;
		}
		if (i != min)
		{
			swap(&mas[i], &mas[min]);
			++* kol_permutation;
		}
	}
}

//ðåàëèçàöèÿ ñîðòèðîâêè ðàñ÷åñêîé
void comb_sort(double* mas, ll n, ll* kol_comparison, ll* kol_permutation)
{
	double factor = 1.247;
	double step = n / factor;
	while (step - 1 > 0)
	{
		ll i;
		ll st = step;
		for (i = 0; i + st < n; ++i)
		{
			++*kol_comparison;
			if (mas[i] > mas[i + st])
			{
				++*kol_permutation;
				swap(&mas[i], &mas[i + st]);
			}
		}
		step /= factor;
	}
}

// ðåàëèçàöèÿ ïîðàçðÿäíîé ñîðòèðîâêè 
void radix_sort(double* mas,double* out, ll byte, ll n, ll* kol_permutation)
{
	uchar* masc = (uchar*)mas;

	ll counter[256];
	ll tmp;
	ll i;

	for (i = 0; i < 256; ++i) counter[i] = 0;// çàïîëíåíèå íóëÿìè, êàê êîëè÷åñòâî áàéò

	for (i = 0; i < n; ++i) counter[masc[8 * i + byte]]++;//çàïîëíåíèå ìàññèâà êîëè÷åñòâîì áàéò
	
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
		++*kol_permutation;
		out[counter[masc[8 * i + byte]]] = mas[i];
		counter[masc[8 * i + byte]]++;
	}
}

//îñíîâíàÿ ôóíêöèÿ, èç êîòîðîé âûçûâàåòñÿ radix_sort 
// mas - îñíîâíîé ìàññèâ
// n - êîë-âî ýëåìåíòîâ
// k - êîë-âî îòðèöàòåëüíûõ ýëåìåíòîâ
void LSD(double* mas, ll n,ll k, ll* kol_permutation)
{
	ll i;
	double* out = (double*)malloc(n * sizeof(double));
	for (i = 0; i < 8; ++i)
	{
		(i % 2 == 0) ? radix_sort(mas, out, i, n, kol_permutation) : radix_sort(out, mas, i, n, kol_permutation);
	}

	reverse(mas, n, k, &*kol_permutation);
	reverse(mas, n, 0, &*kol_permutation);
}

// âñïîìîãàòåëüíàÿ ôóíêöèÿ (êîìïîðàòîð) äëÿ qsort, êîòîðàÿ ñðàâíèâàåò 2 ÷èñëà â double
int compare(const void* a, const void* b)
{
	const double* ad, * bd;
	// òàê êàê ïðèíèìàåì óêàçàòåëè áåç òèïîâ äàííûõ ìû äîëæíû â ñêîáêàõ óêàõçàòü ñêîëüêî áàéò ïðèõîäèòñÿ íà êàæäûé ýëåìåíò
	ad = (const double*)a;
	bd = (const double*)b;

	if ((*ad - *bd) < 0) return -1;
	else
	{
		if ((*ad - *bd) > 0) return 1;
		else return 0;
	}
}

//ïðîâåðêà íà ñîðòèðîâêó ìàññèâà (þçàåì qsort, êîòîðûé òî÷íî ñîðòèðóåò ìàññèâ, à äàëåå ñðàâíèâàåì ðåçóëüòàò ñ ïîëó÷åííûì ìàññèâîì èç qsort)
ll check(double* mas_a, double* mas_b, ll n)
{
	ll i;
	qsort(mas_a, n, sizeof(double), compare);
	//mas_a óêàçàòåëü íà íà÷àëî ìàññèâà
	//n êîë-âî ýëåìåíòîâ
	//sizeof(double) ðàçìåð êàæäîãî ýëåìåíòà
	for (i = 0; i < n; ++i)
	{
		if (abs(mas_a[i] - mas_b[i]) > 1e-16)
		{
			return 0;
		}
	}
	return 1;
}

void answer(double* mas_a, double* mas_b, ll n, ll time, ll kol_comparison, ll kol_permutation)
{
	ll ch = check(mas_a, mas_b, n);
	if (ch)
	{
		printf("Ìàññèâ îòñîðòèðîâàí óñïåøíî\n");
		printf("Âðåìÿ ñîðòèðîâêè: %lf ñåêóíä\n", time / (double)CLOCKS_PER_SEC);
		printf("êîëè÷åñòâî ñðàâíåíèé: %d\n", kol_comparison);
		printf("êîëè÷åñòâî ïåðåñòàíîâîê: %d\n", kol_permutation);
	}
	else printf("Îøèáêà, íå óäàëîñü îòñîðòèðîâàòü ìàññèâ\n");
}

int main()
{
	srand(time(0));
	setlocale(LC_CTYPE, "RUS");
	ll x = 1;
	printf("ïðèâåò ïîëüçîâàòåëü!\nÄàííàÿ ïðîãðàììà ïðåäíàçíà÷åíà äëÿ ñðàâíåíèÿ ñîðòèðîâîê Âûáîðîì, Ðàñ÷åñêîé è Ïîðàçðÿäíîé.\nÂñå òåñòû áóäóò ïðîõîäèòü íà òèïå double.\n");	
	printf("ââåñòè êîë-âî ýëåìåíòîâ â ìàññèâå.\n");

	ll n;
	scanf_s("%llu", &n);
	ll kol_negative = 0;
	double* mas_a = (double*)malloc(n * sizeof(double));
	double* mas_b = (double*)malloc(n * sizeof(double));
	double* mas_c = (double*)malloc(n * sizeof(double));
	filling(mas_a, n, &kol_negative);
	while (1)
	{
		printf("\n");
		printf("Menu:\n");
		printf("Âûáîðîì - 1\n");
		printf("Ðàñ÷åñêîé - 2\n");
		printf("Ïîðàçðÿäíàÿ - 3\n");
		printf("ñìåíà êîë-âà ýëåìåíòîâ ìàññèâà- 4\n");
		printf("Âûõîä - 5\n");
		int k;
		scanf_s("%d", &k);
		switch (k)
		{
			case 1:
			{
				clock_t start, finish;
				ll kol_comparison = 0;
				ll kol_permutation = 0;
				copy_(mas_a, mas_b, n);
				copy_(mas_a, mas_c, n);
				start = clock();
				choice_sort(mas_b, n, &kol_comparison, &kol_permutation);
				finish = clock();
				answer(mas_c, mas_b, n, finish - start, kol_comparison, kol_permutation);
				break;
			}
			case 2:
			{
				clock_t start, finish;
				ll kol_comparison = 0;
				ll kol_permutation = 0;
				copy_(mas_a, mas_b, n);
				copy_(mas_a, mas_c, n);
				start = clock();
				comb_sort(mas_b, n, &kol_comparison, &kol_permutation);
				finish = clock();
				answer(mas_c, mas_b, n, finish - start, kol_comparison, kol_permutation);
				break;
			}
			case 3:
			{
				clock_t start, finish;
				ll kol_comparison = 0;
				ll kol_permutation = 0;
				copy_(mas_a, mas_b, n);
				copy_(mas_a, mas_c, n);
				start = clock();
				LSD(mas_b, n, kol_negative, &kol_permutation);
				finish = clock();
				answer(mas_c, mas_b, n, finish - start, kol_comparison, kol_permutation);
				break;
			}
			case 4:
			{
				printf("ââåñòè êîë-âî ýëåìåíòîâ â ìàññèâå.\n");
				scanf_s("%llu", &n);
				mas_a = (double*)malloc(n * sizeof(double));
				mas_b = (double*)malloc(n * sizeof(double));
				mas_c = (double*)malloc(n * sizeof(double));
				filling(mas_a, n, &kol_negative);
				break;
			}
			case 5:
			{
				printf("ñïàñèáî çà ðàáîòó!\n");
				return 0;
			}
			default:
				break;		
		}
	}
}
