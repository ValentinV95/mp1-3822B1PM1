#pragma once
#include <iostream>
#include "vec.h"
using namespace std;

template <typename T>
class matrix {
private:
    T** mat;
    size_t size;
public:
    matrix(size_t size)
    {
        this->size = size;
        mat = new T * [size];

        for (int i = 0; i < size; i++)
            mat[i] = new T[size + 1];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size + 1; j++)
                mat[i][j] = 0;
    }
    matrix(const matrix<T>& M)//конструктор копирования
    {
        size = M.size;
        mat = new T * [size];

        for (int i = 0; i < size; i++)
            mat[i] = new T[size + 1];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size + 1; j++)
                mat[i][j] = M.mat[i][j];
    }

    // методы доступа для задания матрицы и расширенной матрицы
    void Set_matrix()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                cin >> mat[i][j];
    }

    void Set_matrix(vec<T> b)
    {
        for (int i = 0; i < size; i++)
            mat[i][size] = b.Get_vec(i);
    }

    void Set_matrix(int i, int j, T new_m)
    {
        mat[i][j] = new_m;
    }

    T Get_matrix(int i, int j)
    {
        return mat[i][j];
    }

    /*void myswap(int i, int j)
    {
        T* tmp = mat[i];
        mat[i] = mat[j];
        mat[j] = tmp;

    }*/
    void myswap(int i1, int i2)
    {
        T t;
        for (int j = 0; j < size + 1; j++)
        {
            t = mat[i1][j];
            mat[i1][j] = mat[i2][j];
            mat[i2][j] = t;
        }
    }

    ~matrix()
    {
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
                delete[] mat[i];
            delete[] mat;
            size = 0;
        }
    }

    void print_matrix()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << "|" << mat[i][size] << "\n";
        }
        cout << "\n";
    }
};
