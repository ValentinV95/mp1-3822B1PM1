#pragma once

float lnup(int number, float x, float previous);
float lndown(int number, float x, float previous);

float expup(int number, float x, float previous);
float expdown(int number, float x, float previous);

float cosup(int number, float x, float previous);
float cosdown(int number, float x, float previous);

float sinup(int number, float x, float previous);
float sindown(int number, float x, float previous);

float summ(float(*foo)(int, float, float), int number, float x);
float summ_reverse(float(*foo)(int, float, float), float(*previousfoo)(int, float, float), int number, float x);