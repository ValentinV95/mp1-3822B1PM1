#pragma once
using namespace std;
template <class T3>
class solver :public matrix<T3>, public vector<T3>
{
private:
public:
    int max(int m, int n, matrix<T3>& A, vector<T3>& B)
    {
        T3 maxi = 0;
        int maxin = 0;
        for (int i = n; i < m; i++)
        {

            if (maxi < abs(A.GetAij(i, n)))
            {
                maxi = A.GetAij(i, n);
                maxin = i;
            }

        }
        return maxin;
    }
    void swap(int m, int i, int k, matrix<T3>& A, vector<T3>& B) {
        T3 tmp = 0;
        for (int j = k; j < m; j++)
        {
            tmp = A.GetAij(i, j);
            A.SetAij(i, j, A.GetAij(k, j));
            A.SetAij(k, j, tmp);
        }
        tmp = B.GetBi(i);
        B.SetBi(i, B.GetBi(k));
        B.SetBi(k, tmp);
        cout << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << A.GetAij(i, j) << " ";
            }
            cout << "|" << B.GetBi(i) << " ";
            cout << endl;
        }

    }
    void joga(int m, matrix<T3>& A, vector<T3>& B)
    {
        cout << "процесс:" << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << A.GetAij(i, j) << " ";

            }
            cout << "|" << B.GetBi(i) << " ";
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < m; i++)
        {
            int maximum = max(m, i, A, B);
            if (maximum != i)
                swap(m, maximum, i, A, B);
            for (int j = i + 1; j < m; j++)
            {
                T3 x = (-1) * (A.GetAij(j, i) / A.GetAij(i, i));
                T3 u = x * B.GetBi(i);
                T3 v = u + B.GetBi(j);
                if (abs(v) < 1.19e-07)
                {
                    v = 0;
                }
                B.SetBi(j, v);
                for (int k = i; k < m; k++)
                {
                    T3 z = x * A.GetAij(i, k);
                    T3 y = z + A.GetAij(j, k);
                    if (abs(y) < 1.19e-07)
                    {
                        y = 0;
                    }
                    A.SetAij(j, k, y);
                }

            }
            cout << endl;
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << A.GetAij(i, j) << " ";

            }
            cout << "|" << B.GetBi(i) << " ";
            cout << endl;
        }
        cout << endl;
        for (int i = 1; i < m; i++)
        {
            for (int j = 0; j < i; j++)
            {
                T3 x = (-1) * (A.GetAij(j, i) / A.GetAij(i, i));
                T3 u = x * B.GetBi(i);
                T3 v = u + B.GetBi(j);
                if (abs(v) < 1.19e-07)
                {
                    v = 0;
                }
                B.SetBi(j, v);
                for (int k = i; k < m; k++)
                {
                    T3 z = x * A.GetAij(i, k);
                    T3 y = z + A.GetAij(j, k);
                    if (abs(y) < 1.19e-07)
                    {
                        y = 0;
                    }
                    A.SetAij(j, k, y);
                }
            }

        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << A.GetAij(i, j) << " ";

            }
            cout << "|" << B.GetBi(i) << " ";
            cout << endl;
        }
        cout << "Решения: " << endl;
        for (int i = 0; i < m; i++)
        {
            T3 x = B.GetBi(i) / A.GetAij(i, i);
            if (abs(x) < 1.19e-07)
            {
                x = 0;
            }
            cout << x << endl;
        }
    }
};