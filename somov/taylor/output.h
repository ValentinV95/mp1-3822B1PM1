#pragma once

#define MATH_FUNCTIONS_COUNT 4

typedef float (*std_math_func)(float x);
typedef float (*user_math_func)(float x, float t, int i, int mode);

void write_report(float lower_bound, float upper_bound, float delta);
float cli_calc(float x, int chosen_function, int mode);