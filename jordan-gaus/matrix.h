#pragma once
#include <iostream>
using namespace std;

template <class T1>
class matrix {
private:
    int m;
    T1** A;
public:
    matrix() {
        m = 0;
    }
    matrix(int m1) {
        m = m1;
        A = (T1**) new T1 * [m];
        for (int i = 0; i < m; i++)
            A[i] = (T1*) new T1 * [m];
        cout << "¬ведите элемнты матрицы" << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
                cin >> A[i][j];


        }
    }
    matrix(const matrix& matr) {
        m = matr.m;
        A = (T1**) new T1 * [m];
        for (int i = 0; i < m; i++)
            A[i] = (T1*) new T1 * [m];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                A[i][j] = matr.A[i][j];
    }
    ~matrix() {
        for (int i = 0; i < m; i++)
            delete[]A[i];
        delete[]A;
    }
    T1 GetM(int i, int j)
    {
        return A[i][j];
    }

    void SetM(int i, int j, T1 a)
    {
        A[i][j] = a;
    }
};
