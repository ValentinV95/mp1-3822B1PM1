#pragma once
#include "vector.h"
#include "square_matrix.h"
#include <iostream>

const double EPS = 1.0E-30;

template <class T>
class solver
{
protected:

    int size;
    vector<T> v;
    square_matrix<T> m;

public:

    solver(square_matrix<T>& _m, vector<T>& _v, int _size) : m(_size), v(_size)
    {
        if (_m.get_size() != _v.get_size()) throw "not equal sizes";
        if (_m.get_size() != _size) throw "not equal sizes";

        size = _size;
        m = _m;
        v = _v;
    }

    int max(int j, bool flag) //return number of row with biggest element in j-column, if this row is under j-row or if (this row above j-row) and (flag = 1) and (contains zeros only in 0,...,j-1 columns)
    {
        int k = j;
        double max = std::abs(static_cast<double>(m[j * size + j]));

        for (int i = j + 1; i < size; i++)
        {
            if (max < std::abs(static_cast<double>(m[i * size + j])))
            {
                max = static_cast<double>(m[i * size + j]);
                k = i;
            }
        }

        if (flag)
        {
            for (int i = 0; i < j; i++)
            {
                bool flag1=1;

                #pragma omp parallel for
                for (int s = 0; s < j; s++)
                    if (static_cast<double>(m[i * size + s]) > EPS) flag1 = 0;

                if (flag1) 
                {
                    if (max < std::abs(static_cast<double>(m[i * size + j]))) 
                    { 
                        max = static_cast<double>(m[i * size + j]); 
                        k = i; 
                    }
                }
            }
        }
        return k;
    }

    void swap(int i, int j) //swap i-row with j-row in matrix and i-element with j-element in vector
    {
        for (int k = 0; k < size; k++)
            std::swap(m[i * size + k], m[j * size + k]);
        std::swap(v[j], v[i]);
    }

    int solution() //solving Ax=b (mx=v) //2 - det=0 & no solutions, 1 - det=0 & infinity solutions, 0 - the only one solution (v) 
    {
        bool flag = false;  //presence of zero-row in matrix
        for (int i = 0; i < size; i++)
        {
            bool flag2 = true;
            int tmp = max(i, flag);
            if (i != tmp) swap(i, tmp);

            if (std::abs(static_cast<double>(m[i * size + i])) < EPS) 
            { 
            flag = true; 
            flag2 = false; 
            }

            if (flag2)
            {
                #pragma omp parallel for    // Project / Properties / C/C++ / Laguage / OpenMP Support
                for (int j = 0; j < size; j++)
                {
                    if ((std::abs(static_cast<double>(m[j * size + i])) > EPS) && (j != i))
                    {
                        v[j] += -v[i] / m[i * size + i] * m[j * size + i];

                        for (int k = size - 1; k > i - 1; k--)
                        {
                            m[j * size + k] += -m[i * size + k] / m[i * size + i] * m[j * size + i];
                        }
                    }
                }
                v[i] /= m[i * size + i];

                for (int k = size - 1; k > i - 1; k--)
                    m[i * size + k] /= m[i * size + i];
            }
        }
        if (flag)//if zero-row in matrix  
        {
            for (int i = 0; i < size; i++)// if every zero-row in matrix A is zero-row in matrix|vector A|b
            {
                if ((std::abs(static_cast<double>(m[i * size + i])) < EPS) && (std::abs(static_cast<double>(v[i])) > EPS)) return 2;
            }
            return 1;
        }

        return 0;
    }
    vector<T>& get_v() 
    {
        return v;
    }
};