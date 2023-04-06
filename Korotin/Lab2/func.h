#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float M_E = 2.718281828459045;

struct res {
    float str;
    float rev;
};

float mysin(float inp, float x, int i, int mod);
float mycos(float inp, float x, int i, int mod);
float myexp(float inp, float x, int i, int mod);
float ln(float inp, float x, int i, int mod);
struct res sum(float first, float x, int numb, float (*fun)(float, float, int, int));