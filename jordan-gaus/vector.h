#pragma once
#include <iostream>
template <class T2>
class vector {
private:
    T2* B;
    int m;
public:
    vector()
    {
        m = 0;
    }
    vector(int m1)
    {
        m = m1;
        B = (T2*) new T2 * [m];
        cout << "¬ведите элемнты вектора" << endl;
        for (int i = 0; i < m; i++)
        {
            cin >> B[i];

        }
    }
    vector(const vector& v)
    {
        m = v.m;
        B = (T2*)new T2 * [m];
        for (int i = 0; i < m; i++)
        {
            B[i] = v.B[i];

        }

    }
    ~vector()
    {
        delete[]B;
    }
    T2 GetV(int i)
    {
        return B[i];
    }

    void SetV(int i, T2 v)
    {
        B[i] = v;
    }
};