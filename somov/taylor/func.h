#pragma once

#define EPS 1.0e-7f

// mode:
// 1 - считает слагаемые для обратного суммирования
// 0 - считаем слагаемые для прямого суммирования

float u_expf(float x, float t, int i, int mode);
float u_sinf(float x, float t, int i, int mode);
float u_cosf(float x, float t, int i, int mode);
float u_lnf(float x, float t, int i, int mode);
float direct_sum(float x, float (*fun)(float, float, int, int));
float reverse_sum(float x, float (*fun)(float, float, int, int));