#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float PI = 3.14159265F;

float mysin1(float x, float prev, int n);
float mycos1(float x, float prev, int n);
float myln1(float x, float prev, int n);
float myexp1(float x, float prev, int n);
float mysum(float x, int n, int is_reverse, float (*func) (float, float, int));
float myln2(float x, int n, int is_reverse);