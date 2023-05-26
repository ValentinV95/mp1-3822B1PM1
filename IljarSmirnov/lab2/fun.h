#pragma once
float sins(int i, float x, float last);
float coss(int i, float x, float last);
float lns(int i, float x, float last);
float exps(int i, float x, float last);

float sinb(int i, float x, float prev);
float cosb(int i, float x, float prev);
float lnb(int i, float x, float prev);
float expb(int i, float x, float prev);

float strway(int n, float x, float (*fun)(int, float, float));
float backway(int n, float x, float (*funs)(int, float, float), float (*funb)(int, float, float));