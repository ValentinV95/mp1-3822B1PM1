#include "func.h"
#include "math.h"

float u_expf(float x, float t, int i, int mode)
{
	if (i == 0) return 1.0f;
	return (mode ?
		t * i / x :
		t * x / i);
}

float u_sinf(float x, float t, int i, int mode)
{
	if (i == 0) return x;
	return (mode ?
		-1.0f * t * (2 * i * (2 * i + 1)) / (x * x) :
		-1.0f * t * x * x / (2 * i * (2 * i + 1)));
}

float u_cosf(float x, float t, int i, int mode)
{
	if (i == 0) return 1.0f;
	return (mode ?
		-1.0f * t * (2 * i * (2 * i - 1)) / (x * x) :
		-1.0f * t * x * x / (2 * i * (2 * i - 1)));
}

float u_lnf(float x, float t, int i, int mode)
{
	if (i == 0) return x;
	return (mode ?
		-1.0f * t * (i + 1) / (i * x) :
		-1.0f * t * i * x / (i + 1));
}

float direct_sum(float x, float (*fun)(float, float, int, int))
{
	float res = 0.0f;
	float term = 0.0f;

	for (int i = 0; fabs(term = fun(x, term, i, 0)) > EPS; i++)
		res += term;

	return res;
}

float reverse_sum(float x, float (*fun)(float, float, int, int))
{
	float res = 0.0f;
	float term = 0.0f;
	int i = 0;

	// ищем последнее ненулевое слагаемое...
	while (fabs(term = fun(x, term, i, 0)) > EPS) i++;

	// добавляем слагаемые с конца
	for (; i > 0; i--)
	{
		res += term;
		term = fun(x, term, i, 1);
	}

	// добавляем неучтённое при обратном суммировании первое слагаемое
	return res + fun(x, 0.0f, 0, 0);
}