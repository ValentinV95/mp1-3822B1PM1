#include "stdio.h""
#include "stdlib.h"
#include "math.h"
#include "prototypes.h"

float lnup(int number, float x, float previous) {
	float res;
	if (number == 0) {
		return x;
	}
	res = ((-1) * ((number * x) / (number + 1))) * previous;
	return res;
}

float lndown(int number, float x, float previous) {
	float res;
	if (number == 0) {
		return 0;
	}
	res = ((-1) * (number + 1) / (number * x)) * previous;
	return res;
}

float expup(int number, float x, float previous) {
	float res;
	if (number == 0) {
		previous = 1.0;
		return previous;
	}
	res = (x / number) * previous;
	return res;
}

float expdown(int number, float x, float previous) {
	float res;
	res = (number / x) * previous;
	return res;
}

float cosup(int number, float x, float previous) {
	float res;
	if (number == 0) {
		previous = 1.0;
		return previous;
	}
	res = ((-1) * (x * x) / ((2 * number - 1) * 2 * number)) * previous;
	return res;
}

float cosdown(int number, float x, float previous) {
	float res;
	res = ((-1) * ((2 * number - 1) * 2 * number) / (x * x)) * previous;
	return res;
}

float sinup(int number, float x, float previous) {
	float res;
	if (number == 0) {
		return x;
	}
	res = ((-1) * (x * x) / (2 * number * (2 * number + 1))) * previous;
	return res;
}

float sindown(int number, float x, float previous) {
	float res;
	res = ((-1) * (2 * number * (2 * number + 1)) / (x * x)) * previous;
	return res;
}

float summ(float(*foo)(int, float, float), int number, float x) {
	float res = 0.0;
	float previous = 0.0;
	for (int i = 0; i < number; i++) {
		res += foo(i, x, previous);
		previous = foo(i, x, previous);
	}
	return res;
}


float summ_reverse(float(*foo)(int, float, float), float(*previousfoo)(int, float, float), int number, float x) {
	int k = 0;
	float res = 0.0;
	float fall = 0.0;
	float previous = 0.0;
	for (int i = 0; i < number; i++) {
		previous = previousfoo(i, x, previous);
		if ((fabs(previous) - (3.4e-38)) < 0) {
			previous = fall;
			k = i;
			break;
		}
		fall = previous;
		k = i + 1;
	}
	res += previous;
	for (int i = k - 1; i >= 0; i--) {
		res += foo(i, x, previous);
		previous = foo(i, x, previous);
	}
	return res;
}