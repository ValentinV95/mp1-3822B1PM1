#pragma once
#include "vector.h"
#include "matrix.h"
#include <iostream>

template <typename T>
bool was_using(int k, int n, vec<T> &U);

template <typename T>
int search_max(int n, int ind, matrix<T> &A, vec<T> &U);

template <typename T>
int search_max_for_result(int n, int ind, matrix<T> &A);

template <typename T>
bool is_null(int n, int ind, matrix<T>&A);

template <typename T>
void solver(int n);

