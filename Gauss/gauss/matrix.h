#pragma once
#include <iostream>
using namespace std;
template <typename T>
class matrix {
private:
    T** arr;
    int n; //размерность
public:
    matrix(int _n);

    T& operator () (int ind1, int ind2);

    matrix(const matrix <T>& A);




    void set_matrix(int _n);

    void get_matrix(int _n);

    ~matrix();
};
