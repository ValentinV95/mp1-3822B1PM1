#include <stdio.h>
#include <math.h>
#include "core.h"
int main()
{
	int a, b, n;
	float res, x;
	float funres;

	printf("Choose the sum: 1.direct 2.reverse\n");
	scanf_s("%d", &b);
	if (b == 1)
	{
		printf("Choose the fun: 1.sinx 2. cosx 3. ln(1+x) 4. e^x\n");
		scanf_s("%d", &a);
		printf("Enter x and n:\n");
		scanf_s("%f %d", &x, &n);

		if (a == 1)
		{
			res = sum(pr_sin, n, x);
			funres = (float)sin(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 2)
		{
			res = sum(pr_cos, n, x);
			funres = (float)cos(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 3)
		{
			res = sum(pr_ln, n, x);
			funres = (float)log(x + 1);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 4)
		{
			res = sum(pr_ex, n, x);
			funres = (float)exp(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
	}
	if (b == 2)
	{
		printf("Choose the fun: 1.sinx 2. cosx 3. ln(1+x) 4. e^x\n");
		scanf_s("%d", &a);
		printf("Enter x and n:\n");
		scanf_s("%f %d", &x, &n);

		if (a == 1)
		{
			res = reversesum(ob_sin, pr_sin, n, x);
			funres = (float)sin(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 2)
		{
			res = reversesum(ob_cos, pr_cos, n, x);
			funres = (float)cos(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 3)
		{
			res = reversesum(ob_ln, pr_ln, n, x);
			funres = (float)log(x + 1);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
		if (a == 4)
		{
			res = reversesum(ob_ex, pr_ex, n, x);
			funres = (float)exp(x);
			printf("Result: %f\n", res);
			printf("Error: %f", fabs(funres - res));
		}
	}

	return 0;
}
