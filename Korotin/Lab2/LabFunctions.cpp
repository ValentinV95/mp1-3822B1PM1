#include "func.h"
#include <locale.h>

int main()
{
    struct res res;
    float x, real;
    int numb, choose=0;
    setlocale(LC_ALL, "Rus");
    do {
        printf("Выберите функцию, которую хотите епосчитать с помощью формулы Тейлора:\n1.Синус\n2.Косинус\n3.Экспонента\n4.Натуральный логарифм\n");
        scanf_s("%i", &choose);
        if ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4)) {
            system("cln");
            printf("ВЫбранной вами функции не существует, попробуйте снова:\n");
        };
    } while ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4));
    printf("Введите значение, в которм вы хотите посчитать выбранную функию: ");
    scanf_s("%f", &x);
    printf("Введите количество слогаемых, которые вы хотите посчитать: ");
    scanf_s("%i", &numb);
    switch (choose)
    {
    case (1):
        res = sum(x, x, numb, mysin);
        real = sinf(x);
        break;
    case (2):
        res = sum(1, x, numb, mycos);
        real = cosf(x);
        break;
    case (3):
        res = sum(1, x, numb, myexp);
        real = powf(M_E, x);
        break;
    case (4):
        res = sum(x-1, x-1, numb, ln);
        real = logf(x);
        break;
    }
    printf("Реальное значение: %f\n", real);
    printf("ПРЯМОЙ СЧЁТ:\n Значение, посчитанное с помощью формулы Тейлора: %f; Разница с реальным значением: %f\n", res.str, fabsf(res.str-real));
    printf("ОБРАТНЫЙ СЧЁТ:\n Значение, посчитанное с помощью формулы Тейлора: %f; Разница с реальным значением: %f", res.rev, fabsf(res.rev - real));
    return 0;
}