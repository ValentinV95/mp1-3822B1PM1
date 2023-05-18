#pragma once
#include <iostream>

using namespace std;
template <typename T>
class vec {
private:
    int n;
    T* arr;
public:
    vec(int _n);

    T& operator [](int ind);

    void set_vec(int _n);

    void get_vec(int _n);

    ~vec();
};

