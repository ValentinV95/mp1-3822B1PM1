#pragma once
#include <iostream>
using namespace std;

template <typename T>
class vec {
private:
    size_t size;
    T* mas;

public:
    vec(size_t size)
    {
        this->size = size;
        mas = new T[size];
        for (int i = 0; i < size; i++)
            mas[i] = 0;
    }
    vec(const vec<T>& s)
    {
        size = s.size;
        mas = new T[size];
        for (int i = 0; i < size; i++)
            mas[i] = s.mas[i];
    }
    void Set_vec()
    {
        for (int i = 0; i < size; i++)
            cin >> mas[i];
        cout << "\n";
    }
    void Set_vec(int index, T new_m)
    {
        mas[index] = new_m;
    }
    const T Get_vec(const int index)
    {
        return mas[index];
    }
    ~vec()
    {
        delete[]mas;
        size = 0;
    }


};