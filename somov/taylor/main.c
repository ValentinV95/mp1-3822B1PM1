#include "func.h"
#include "output.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

int main()
{
	int choice;

	float lower_bound, upper_bound, delta;
	float x;
	float result_dir, result_rev, result_std;

	setlocale(LC_CTYPE, "RUSSIAN");

	printf("Суммирование рядов математических функций\n");
	printf("------------------\n");
	printf("Выбор:\n");
	printf("1. Создать отчёт\n");
	printf("2. Посчитать значение функции напрямую\n");
	printf("> ");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("Введите нижнюю, верхнюю границу вычисления значений функций и шаг вычислений. Программа создаст четыре лог-файла, содержащих значения, вычисленных на указанном промежутке.\n> ");
		scanf_s("%f%f%f", &lower_bound, &upper_bound, &delta);
		write_report(lower_bound, upper_bound, delta);
		break;
	case 2:
		printf("Выберите функцию (введите любую из цифр):\n");
		printf("1. exp(x):\n");
		printf("2. sin(x):\n");
		printf("3. cos(x):\n");
		printf("4. ln(1+x):\n");
		printf("> ");
		scanf_s("%d", &choice);

		if ((choice > MATH_FUNCTIONS_COUNT) || (choice < 1))
		{
			printf("Введено недопустимое значение.\n");
		}

		else
		{
			choice--;
			printf("Введите значение x, для которого хотите вычислить значение.\n> ");
			scanf_s("%f", &x);
			result_dir = cli_calc(x, choice, 0);
			result_rev = cli_calc(x, choice, 1);
			result_std = cli_calc(x, choice, 2);
			printf("Полученные значения: прямое суммирование, обратное суммирование, функция из math.h\n");
			printf("%.8f %.8f %.8f\n", result_dir, result_rev, result_std);
			printf("Абсолютная погрешность\n");
			printf("%.8f %.8f\n", result_dir - result_std, result_rev - result_std);
			printf("Относительная погрешность\n");

			(fabs(result_std) < EPS) ?
				printf("%.8f %.8f\n", result_dir - result_std, result_rev - result_std) :
				printf("%.8f %.8f\n", (result_dir - result_std) / result_std, (result_rev - result_std) / result_std);

		}

		break;
	default:
		printf("Выбор не распознан.\n");
		break;
	}
	
	return 0;
}