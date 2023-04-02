

#include <iostream>
#define _USE_MATH_DEFINES
#include "fun.h"

int main()
{
    int n;
    float x, value;
	int choicef,choicem;
	char fl1 = 1;
    printf("Enter the point at which you want to calculate the value of the function ");
    scanf_s("%f",&x);
    printf("Enter the number of steps (row members) ");
    scanf_s("%i", &n);
	printf("\n\nSelect function: enter 1 for sin(x); 2 for cos(x) 3 for ln(1+x); 4 for exp(x) \n");
	do {
		scanf_s("%d", &choicef);
		if ((choicef != 1) && (choicef != 2) && (choicef != 3) && (choicef != 4)) {
			printf("Invalid input. Try again\n");
		}
		else fl1 = 0;
	} while (fl1);

    printf("\nSelect summation method: enter 1 for straight way; 2 for backway \n");
    do {
        scanf_s("%d", &choicem);
        if ((choicem != 1) && (choicem != 2)) {
            printf("Invalid input. Try again\n");
        }
        else fl1 = 0;
    } while (fl1);

    switch(choicef){
    case 1:
        if (choicem == 1) {
            value = strway(n, x, sins);
        }
        else value = backway(n, x, sins, sinb);
        break;
    case 2:
        if (choicem == 1) {
            value = strway(n, x, coss);
        }
        else value = backway(n, x, coss, cosb);
        break;
    case 3:
        if (choicem == 1) {
            value = strway(n, x, lns);
        }
        else value = backway(n, x, lns, lnb);
        break;
    case 4:
        if (choicem == 1) {
            value = strway(n, x, exps);
        }
        else value = backway(n, x, exps, expb);
        break;
    }
    printf("Value is %f\n", value);
    switch (choicef) {
    case 1:
        printf("Real value is: %f", sin(x));
        break;
    case 2:
        printf("Real value is: %f", cos(x));
        break;
    case 3:
        printf("Real value is: %f", log(1+x));
        break;
    case 4:
        printf("Real value is: %f", exp(x));
        break;
    }
}
