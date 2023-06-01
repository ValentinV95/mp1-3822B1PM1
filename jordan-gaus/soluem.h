#pragma once
#include"matrix.h"
#include"vector.h"
#include <cmath>
using namespace std;

template <class T3>
class soluem :public matrix<T3>
{
private:

public:

    int mx(int m, int n, matrix <T3>& A, vector <T3>& B) {
        int mxn = 0;
        T3 mxm = 0;
        for (int i = n; i < m; i++)
        {

            if (mxm < abs(A.GetM(i, n)))
            {
                mxm = A.GetM(i, n);
                mxn = i;
            }


        }
        return mxn;
    }
    void swapline(int m, int i, int k, matrix <T3>& A, vector <T3>& B) {
        T3 tmp = 0;
        for (int j = k; j < m; j++)
        {
            tmp = A.GetM(i, j);
            A.SetM(i, j, A.GetM(k, j));
            A.SetM(k, j, tmp);
        }
        tmp = B.GetV(i);
        B.SetV(i, B.GetV(k));
        B.SetV(k, tmp);

    }
    void zero(int m, matrix <T3> A, vector <T3> B) {

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < m; j++)
            {
                cout << A.GetM(i, j) << " ";

            }
            cout << "|" << B.GetV(i);
            cout << endl;
        }


        for (int i = 0; i < m; i++)
        {
            int maximum = mx(m, i, A, B);

            if (maximum != i)
                swapline(m, maximum, i, A, B);
            for (int j = i + 1; j < m; j++) {

                T3 x = (-1) * (A.GetM(j, i) / A.GetM(i, i));
                T3 vz = x * B.GetV(i);
                T3 vy = vz + B.GetV(j);
                if (abs(vy) < 1.19e-06) {
                    vy = 0;
                }
                B.SetV(j, vy);

                for (int k = i; k < m; k++) {

                    T3 z = x * A.GetM(i, k);
                    T3 y = z + A.GetM(j, k);
                    if (abs(y) < 1.19e-06) {
                        y = 0;
                    }
                    A.SetM(j, k, y);
                }


            }


        }
        for (int i = 1; i < m; i++)
        {
            for (int j = 0; j < i; j++) {
                T3 x = (-1) * (A.GetM(j, i) / A.GetM(i, i));
                T3 vz = x * B.GetV(i);
                T3 vy = vz + B.GetV(j);
                if (abs(vy) < 1.19e-06) {
                    vy = 0;
                }
                B.SetV(j, vy);
                for (int k = i; k <= (m - 1); k++) {
                    T3 z = x * A.GetM(i, k);
                    T3 y = z + A.GetM(j, k);
                    if (abs(y) < 1.19e-06) {
                        y = 0;
                    }
                    A.SetM(j, k, y);
                }

            }
        }

        for (int i = 0; i < m; i++) {

            cout << "Решение :" << endl;
            T3 x = B.GetV(i) / A.GetM(i, i);
            if (abs(x) < 1.19e-06) {
                x = 0;
            }
            cout << x << endl;

        }
    }

};