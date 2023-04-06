#include "funcs.h"

float mysin1(float x, float prev, int n) {
	if (n == 0) {
		return x;
	}
	prev *= -x * x / (2.0f * n * (2.0f * n + 1.0f));
	return prev;
}

float mycos1(float x, float prev, int n) {
	if (n == 0) {
		return 1.0f;
	}
	prev *= -x * x / (2.0f * n * (2.0f * n - 1.0f));
	return prev;
}

float myln1(float x, float prev, int n) {
	if (n == 0) {
		return x;
	}
	prev *= -x * ((float)n / ((float)n + 1.0f));
	return prev;
}

float myexp1(float x, float prev, int n) {
	if (n == 0) {
		return 1.0f;
	}
	prev *= x / (float)n;
	return prev;
}

float mysum(float x, int n, int is_reverse, float (*func) (float, float, int)) {
	float *resarr = (float *)malloc(n * sizeof(float));
	float res = 0.0f;
	float aiter = -1.0f;
	if (func == myln1 && x <= -1) {
		return NAN;
	}
	for (int i = 0; i < n; i++) {
		if (aiter != 0.0f) {
			resarr[i] = func(x, aiter, i);
			aiter = resarr[i];
		}
		else {
			resarr[i] = 0.0f;
		}
	}
	if (is_reverse == 0) {
		for (int i = 0; i < n; i++) {
			res += resarr[i];
		}
	}
	else {
		for (int i = n - 1; i >= 0; i--) {
			res += resarr[i];
		}
	}
	free(resarr);
	return res;
}

float myln2(float x, int n, int is_reverse) {
	float aiter;
	float point = 0.0f;
	float deltapoint = 0.0f;
	float res = 0.0f;
	float *elems;
	float tmp;
	int j;
	if (x <= 0.0f) {
		return NAN;
	}
	for (j = -5;; j++) {
		deltapoint = point - x;
		tmp = point;
		if (deltapoint < 0) {
			deltapoint *= -1.0f;
		}
		point = mysum((float)j, 1000, is_reverse, myexp1);
		if (point - x > deltapoint || x - point > deltapoint) {
			break;
		}
	}
	point = tmp;
	if (point < 0.0f) {
		return NAN;
	}
	elems = (float *)malloc(n * sizeof(float));
	elems[0] = (float)j - 1.0f;
	aiter = (x - point) / point;
	elems[1] = aiter;
	for (int i = 2; i < n; i++) {
		aiter *= -(x - point) / (point * ((float)i / ((float)i - 1.0f)));
		elems[i] = aiter;
	}
	if (is_reverse == 0) {
		for (int i = 0; i < n; i++) {
			res += elems[i];
		}
	}
	else {
		for (int i = n - 1; i >= 0; i--) {
			res += elems[i];
		}
	}
	free(elems);
	return res;
}