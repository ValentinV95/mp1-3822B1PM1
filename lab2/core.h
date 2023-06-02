#pragma once
float pr_sin(int n, float x, float ai);
float ob_sin(int n, float x, float ai);
float pr_cos(int n, float x, float ai);
float ob_cos(int n, float x, float ai);
float pr_ln(int n, float x, float ai);
float ob_ln(int n, float x, float ai);
float pr_ex(int n, float x, float ai);
float ob_ex(int n, float x, float ai);
float sum(float(*fun)(int, float, float), int n, float x);
float reversesum(float(*fun1)(int, float, float), float(*fun2)(int, float, float), int n, float x);
