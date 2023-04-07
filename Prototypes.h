#pragma once
//#include "Summands.cpp"
//#include "Sums.cpp"
double slag_sind(double prev, double x, int n);
double slag_cosd(double prev, double x, int n);
double slag_lnd(double prev, double x, int n);
double slag_expd(double prev, double x, int n);
float r_slag_sin(float last, float x, int n);
float r_slag_cos(float prev, float x, int n);
float r_slag_ln(float prev, float x, int n);
float r_slag_exp(float prev, float x, int n);
float slag_sin(float prev, float x, int n);
float slag_cos(float prev, float x, int n);
float slag_ln(float prev, float x, int n);
float slag_exp(float prev, float x, int n);
double the_last_of_us(double (*slag)(double, double, int), double x, int quan);
float sum(float (*slag)(float, float, int), float x, int quan);
float r_sum(float (*r_slag)(float, float, int), float x, float last, int quan);