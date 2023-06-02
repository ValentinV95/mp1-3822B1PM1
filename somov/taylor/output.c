#include "output.h"
#include "func.h"
#include "stdio.h"
#include "math.h"

void write_report(float lower_bound, float upper_bound, float delta)
{
	float x;
	float stdres, dirres, revres;
	std_math_func std_math_func[] = { expf, sinf, cosf, logf };
	user_math_func user_math_func[] = { u_expf, u_sinf, u_cosf, u_lnf };
	const char filename[MATH_FUNCTIONS_COUNT][255] = { "exp.log", "sin.log", "cos.log", "ln.log" };
	FILE* f;

	for (int i = 0; i < MATH_FUNCTIONS_COUNT - 1; i++)
	{
		x = lower_bound;
		fopen_s(&f, filename[i], "w");
		while (x < upper_bound)
		{
			stdres = std_math_func[i](x);
			dirres = direct_sum(x, user_math_func[i]);
			revres = reverse_sum(x, user_math_func[i]);
			fprintf(f, "%.10f %.10f %.10f %.10f\n", x, stdres, dirres, revres);
			x += delta;
		}
		fclose(f);
	}

	// ln(1+x) обрабатываем отдельно, поскольку он не существует для x < -1.0
	x = (lower_bound < -0.99f ? -0.99f : lower_bound);
	// переставим верхнюю границу, если она больше 1.0 (иначе программа будет работать слишком долго)
	x = (lower_bound > 1.0f ? x = -0.99f : x);
	(upper_bound > 1.0f ? upper_bound = 1.0f : 0);
	fopen_s(&f, filename[3], "w");
	while (x < upper_bound)
	{
		stdres = std_math_func[3](1 + x);
		dirres = direct_sum(x, user_math_func[3]);
		revres = reverse_sum(x, user_math_func[3]);
		fprintf(f, "%.10f %.10f %.10f %.10f\n", x, stdres, dirres, revres);
		x += delta;
	}
	fclose(f);
}

float cli_calc(float x, int chosen_function, int mode)
{
	std_math_func std_math_func[] = { expf, sinf, cosf, logf };
	user_math_func user_math_func[] = { u_expf, u_sinf, u_cosf, u_lnf };

	switch (mode)
	{
	case 0:
		return direct_sum(x, user_math_func[chosen_function]);
	case 1:
		return reverse_sum(x, user_math_func[chosen_function]);
	case 2:
		return (chosen_function == 3 ? std_math_func[chosen_function](1+x) : std_math_func[chosen_function](x));
	default:
		return NAN;
	}
}