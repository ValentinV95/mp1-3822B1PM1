#pragma once
//#include "Summands.cpp"
//#include "Sums.cpp"
float r_slag_sin(float last, float x, int n);
float r_slag_cos(float prev, float x, int n);
float r_slag_ln(float prev, float x, int n);
float r_slag_exp(float prev, float x, int n);
float slag_sin(float prev, float x, int n);
float slag_cos(float prev, float x, int n);
float slag_ln(float prev, float x, int n);
float slag_exp(float prev, float x, int n);
float the_last_of_us(float (*slag)(float, float, int), float x, int &quan);
float sum(float (*slag)(float, float, int), float x, int quan);
float r_sum(float (*r_slag)(float, float, int), float x, float last, int quan);