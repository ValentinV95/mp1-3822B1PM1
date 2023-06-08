#pragma once
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

bool check_null(float t) //�������� �� ������� �������
{
    float eps = 10e-6f;
    if (abs(t) < eps) return true;
    else return false;
}

bool check_null(double t)
{
    double eps = 10e-16;
    if (abs(t) < eps) return true;
    else return false;
}

template <typename T>
void print_res(int size, Matrix<T> A) //��������� ����������
{
    T* res = new T[size];
    for (int i = 0; i < size; i++)
        res[i] = 0;

    bool flag = true;

    for (int i = 0; i < size; i++)
    {
        if (A.Get_Matrix(i, i) == 1)
        {
            for (int j = 0; j < size; j++)
                if (j != i)
                    res[i] -= A.Get_Matrix(i, j);
            res[i] += A.Get_Matrix(i, size);
            if (check_null(res[i])) res[i] = 0;
        }
        else
            if (check_null(A.Get_Matrix(i, i)))
            {
                if (check_null(A.Get_Matrix(i, size))) //���� ���������� xi �������� ���������, �� ������������� �������� 1
                {
                    res[i] = 1;
                    cout << "��������� ���������� �������� x" << i + 1 << endl;
                }
                else
                {
                    cout << "��� �������, ��� ��� ������� �����������\n";
                    flag = false;
                    break;
                }
            }
    }
    if (flag)
    {
        for (int i = 0; i < size; i++)
            cout << "x" << i + 1 << " = " << res[i] << endl;
    }

}

template <typename T>
void solver(size_t size)
{
    Matrix <T>A(size);
    cout << "������� ������� ���������: \n";
    A.Set_Matrix();

    Vector <T>b(size);
    cout << "������� ������: \n";
    b.Set_Vector();

    A.extended_matrix(b); //�������� ����������� ������� �

    int max_index;
    for (int k = 0; k < size; k++)
    {
        max_index = k;
        for (int i = k + 1; i < size; i++)
        {
            if (abs(A.Get_Matrix(max_index, k)) > abs(A.Get_Matrix(i, k)))
                max_index = k;
            else max_index = i;
        }

        if (check_null(A.Get_Matrix(max_index, k))) //���� ���� ������� ����� ����, �� ��������� �� ��������� �������
            break;

        T del;
        for (int i = 0; i < size; i++)
        {
            del = A.Get_Matrix(i, k) / A.Get_Matrix(max_index, k);
            for (int j = 0; j < size + 1; j++)
            {
                if (i != max_index)
                {
                    if (check_null(A.Get_Matrix(i, j) - A.Get_Matrix(max_index, j) * del))
                        A.new_value_matrix(i, j, 0);
                    else A.new_value_matrix(i, j, A.Get_Matrix(i, j) - A.Get_Matrix(max_index, j) * del);
                    if (j == k)
                        A.new_value_matrix(i, j, 0);
                }
            }
            del = A.Get_Matrix(max_index, k);
            for (int j = 0; j < size + 1; j++)
                A.new_value_matrix(max_index, j, A.Get_Matrix(max_index, j) / del);
        }

        if (max_index != k)
            A.swap_elem(max_index, k);
        A.print_matrix();
    }

    print_res(size, A);
}