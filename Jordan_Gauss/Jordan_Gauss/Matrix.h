#pragma once
#include<iostream>
#include "Vector.h"

using namespace std;

template <typename T>
class Matrix {
    T** mas;
    size_t size;
public:
    Matrix(size_t size)
    {
        this->size = size;
        mas = new T * [size];

        for (int i = 0; i < size; i++)
            mas[i] = new T[size + 1];
    }

    Matrix(const Matrix<T>& m)
    {
        size = m.size;
        mas = new T * [size];

        for (int i = 0; i < size; i++)
            mas[i] = new T[size + 1];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size + 1; j++)
                mas[i][j] = m.mas[i][j];
    }


    void Set_Matrix()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                cin >> mas[i][j];
    }

    T Get_Matrix(int i, int j)
    {
        return mas[i][j];
    }

    void extended_matrix(Vector<T> b)  //создание расширенной матрицы
    {
        for (int i = 0; i < size; i++)
            mas[i][size] = b.Get_Vector(i);
    }

    void new_value_matrix(int i, int j, T new_val) //присвоить новое значение
    {
        mas[i][j] = new_val;
    }

    void swap_elem(int i1, int i2)
    {
        T w;
        for (int j = 0; j < size + 1; j++)
        {
            w = mas[i1][j];
            mas[i1][j] = mas[i2][j];
            mas[i2][j] = w;
        }
    }

    void print_matrix()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
            {
                cout <<  mas[i][j] << " ";
            }
            cout << "|" << mas[i][size] << "\n";
        }
        cout << "\n";
    }

    ~Matrix()
    {
        if (size > 0) {
            for (int i = 0; i < size; i++)
                delete[] mas[i];
            delete[] mas;
            size = 0;
        }
    }
};
