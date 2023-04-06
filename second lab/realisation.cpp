#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "prototypes.h"

int main() {
	setlocale(LC_CTYPE, "RUS");
	float x, sum;
	int number, action;

	printf("Привет пользователь!\n");
	printf("\n");
	printf("Введите количество элементов массива, для суммирования: ");
	scanf_s("%d", &number);
	printf("Введите точку, в которой хотите посчитать функцию: ");
	scanf_s("%f", &x);

	while (1)
	{
		printf("Меню:\n");
		printf("Прямое суммирование        Обратное суммирование\n");
		printf("	sin(x): 1                     sin(x): 2\n");
		printf("	cos(x): 3                     cos(x): 4\n");
		printf("	exp(x): 5                     exp(x): 6\n");
		printf("	ln(x+1): 7                    ln(x+1): 8\n");
		printf("Изменить количество элементов суммирования: 9\n");
		printf("Изменить точку функции: 10\n");
		printf("Завершить работу программы: 11\n");
		printf("\n");
		printf("=============================================\n");
		printf("Выбор действия: ");
		scanf_s("%d", &action);
		switch (action)
		{
		case 1:
		{
			sum = summ(sinup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 2:
		{
			sum = summ_reverse(sindown, sinup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 3:
		{
			sum = summ(cosup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 4:
		{
			sum = summ_reverse(cosdown, cosup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 5:
		{
			sum = summ(expup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 6:
		{
			sum = summ_reverse(expdown, expup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 7:
		{
			if ((x > 1.0) || (x < -1.0)) {
				printf("Измените точку на значение из -1<x<1\n");
				printf("Введите точку, в которой хотите посчитать функцию: ");
				scanf_s("%f", &x);
			}
			sum = summ(lnup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 8:
		{
			if ((x > 1.0) || (x < -1.0)) {
				printf("Измените точку на значение из -1<x<1\n");
				printf("Введите точку, в которой хотите посчитать функцию: ");
				scanf_s("%f", &x);
			}
			sum = summ_reverse(lndown, lnup, number, x);
			printf("%f\n", sum);
			printf("=============================================\n");
			break;
		}
		case 9:
		{
			printf("Введите количество элементов массива, для суммирования: ");
			scanf_s("%d", &number);
			printf("\n");
			printf("=============================================\n");
			break;
		}
		case 10:
		{
			printf("Введите точку, в которой хотите посчитать функцию: ");
			scanf_s("%f", &x);
			printf("\n");
			printf("=============================================\n");
			break;
		}
		case 11:
		{
			printf("\n");
			printf("\n");
			printf("Программа завершена!\n");
			return 0;
		}
		default:
		{
			printf("\n");
			printf("Неправильный выбор!\n");
			printf("\n");
			printf("=============================================\n");
			printf("\n");
			break;
		}
		}
	}
	
	return 0;
}