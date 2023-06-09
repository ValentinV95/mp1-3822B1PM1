#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Vector {
    size_t size;
    T* mas;
public:
    Vector(size_t size)
    {
        this->size = size;
        mas = new T[size];
        for (int i = 0; i < size; i++)
            mas[i] = 0;
    }

    Vector(const Vector<T>& v)
    {
        size = v.size;
        mas = new T[size];
        for (int i = 0; i < size; i++)
            mas[i] = v.mas[i];
    }

    void Set_Vector()
    {
        for (int i = 0; i < size; i++)
            cin >> mas[i];
        cout << "\n";
    }

    T Get_Vector(const int ind)
    {
        return mas[ind];
    }

    ~Vector()
    {
        delete[]mas;
        size = 0;
    }
};
