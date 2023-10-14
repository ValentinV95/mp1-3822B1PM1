#include "Prototypes.h"
#include <math.h>
float r_sum(float (*r_slag)(float, float, int), float x, float last, int quan)
{
	float rez = 0;
	for (; quan > 0; quan--)
	{
		rez += last;
		last = r_slag(last, x, quan - 1);
	}
	return rez;
}
float sum(float (*slag)(float, float, int), float x, int quan)
{
	float rez = 0, prev = 0;
	for (int i = 1; i <= quan; i++)
	{
		prev = slag(prev, x, i - 1);
		rez += prev;
	}
	return rez;
}
float the_last_of_us(float (*slag)(float, float, int), float x, int* quan)
{
	float prev = 0;
	for (int i = 1; i <= *quan; i++)
	{
		if (fabsf(slag(prev, x, i - 1)) <= 1E-8)
		{
			*quan = i - 1;
			return prev;
		}
		prev = slag(prev, x, i - 1);
	}
	return prev;
}