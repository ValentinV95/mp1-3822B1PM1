#pragma once
#include <iostream>
using namespace std;

bool is_null(float x)
{
    float eps = 10e-6f;
    if (abs(x) < eps) return true;
    return false;
}

bool is_null(double x)
{
    double eps = 10e-16;
    if (abs(x) < eps) return true;
    return false;
}

template <typename T>
void print_res(int size, matrix<T> A)
{
    T* res = new T[size];
    for (int i = 0; i < size; i++)
        res[i] = 0;

    for (int i = 0; i < size; i++)
    {
        if (A.Get_matrix(i, i) == 1)
        {
            for (int j = 0; j < size; j++)
                if (j != i)
                    res[i] -= A.Get_matrix(i, j);
            res[i] += A.Get_matrix(i, size);
            if (is_null(res[i])) res[i] = 0;
        }
        else
            if (is_null(A.Get_matrix(i, i)))
            {
                if (is_null(A.Get_matrix(i, size)))
                {
                    res[i] = 1;
                }
                else
                {
                    cout << "Матрица несовместна";
                    break;
                }
            }
        cout << "x" << i + 1 << " = " << res[i];
        cout << "\n";

    }
}

template <typename T>
void solver(size_t size)
{
    //задание матрицы    
    matrix <T>A(size);
    cout << "Введите матрицу построчно:\n";
    A.Set_matrix();

    //задание вектора b
    vec <T>b(size);
    cout << "Введите вектор (в строку или столбец):\n";
    b.Set_vec();
    A.Set_matrix(b);

    int ind_of_max;
    for (int k = 0; k < size; k++)
    {
        ind_of_max = k;
        for (int i = k + 1; i < size; i++)
        {
            if (abs(A.Get_matrix(i, k)) > abs(A.Get_matrix(i - 1, k)))
                ind_of_max = i;
        }

        if (is_null(A.Get_matrix(ind_of_max, k)))
            continue;
        T div;
        for (int i = 0; i < size; i++)
        {
            div = A.Get_matrix(i, k) / A.Get_matrix(ind_of_max, k);
            for (int j = 0; j < size + 1; j++)
            {
                if (i != ind_of_max)
                {
                    A.Set_matrix(i, j, A.Get_matrix(i, j) - A.Get_matrix(ind_of_max, j) * div);
                    if (j == k)
                        A.Set_matrix(i, j, 0);
                }
            }
            div = A.Get_matrix(ind_of_max, k);
            for (int j=0; j < size + 1; j++)
                A.Set_matrix(ind_of_max, j, A.Get_matrix(ind_of_max, j) / div);

        }

        if (ind_of_max != k)
            A.myswap(ind_of_max, k);
        A.print_matrix();
    }

    print_res(size, A);
}
