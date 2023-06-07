#pragma once
using namespace std;
template <class T>
class matrix
{
private:
    int n;
public:T** A;
      matrix()
      {
          n = 0;
      }
      matrix(int _n)
      {
          n = _n;
          A = new T * [n];
          for (int i = 0; i < n; i++)
              A[i] = new T[n];
          for (int i = 0; i < n; i++)
              for (int j = 0; j < n; j++)
                  A[i][j] = 0;
      }
      matrix(const matrix& c)
      {
          n = c.n;
          A = new T * [n];
          for (int i = 0; i < n; i++)
              A[i] = new T[n];
          for (int i = 0; i < n; i++)
              for (int j = 0; j < n; j++)
                  A[i][j] = c.A[i][j];
      }
      T GetAij(int i, int j)
      {
          return A[i][j];
      }
      void SetAij(int i, int j, T c)
      {
          A[i][j] = c;
      }
      ~matrix()
      {
          for (int i = 0; i < n; i++)
              delete[] A[i];
          delete[]A;
      }
};

template <class T>
class vector
{
private:
    int m;
public:T* B;
      vector()
      {
          m = 0;
      }
      vector(int _m)
      {
          m = _m;
          B = new T[m];
          for (int i = 0; i < m; i++)
              B[i] = 0;
      }
      vector(const vector& c)
      {
          m = c.m;
          B = new T[m];
          for (int i = 0; i < m; i++)
              B[i] = c.B[i];
      }
      T GetBi(int i)
      {
          return B[i];
      }
      void SetBi(int i, T c)
      {
          B[i] = c;
      }
      ~vector()
      {
          delete[]B;
      }
};

template <class T>
class solver :public matrix<T>, public vector<T>
{
private:
public:
    int max(int m, int n, matrix<T>& A, vector<T>& B)
    {
        T maxi = 0;
        int maxin = 0;
        for (int i = n; i < m; i++)
        {

            if (abs(maxi) < abs(A.GetAij(i, n)))
            {
                maxi = A.GetAij(i, n);
                maxin = i;
            }

        }
        return maxin;
    }
    void swap(int m, int i, int k, matrix<T>& A, vector<T>& B) {
        T tmp = 0;
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
    void joga(int m, matrix<T>& A, vector<T>& B)
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
        for (int i = 0; i < m; i++)
        {
            int maximum = max(m, i, A, B);
            if (maximum != i)
                swap(m, maximum, i, A, B);
            for (int j = i + 1; j < m; j++)
            {
                T x = (-1) * (A.GetAij(j, i) / A.GetAij(i, i));
                T u = x * B.GetBi(i);
                T v = u + B.GetBi(j);
                if (abs(v) < 1.19e-06)
                {
                    v = 0;
                }
                B.SetBi(j, v);
                for (int k = i; k < m; k++)
                {
                    T z = x * A.GetAij(i, k);
                    T y = z + A.GetAij(j, k);
                    if (abs(y) < 1.19e-06)
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
                T x = (-1) * (A.GetAij(j, i) / A.GetAij(i, i));
                T u = x * B.GetBi(i);
                T v = u + B.GetBi(j);
                if (abs(v) < 1.19e-06)
                {
                    v = 0;
                }
                B.SetBi(j, v);
                for (int k = i; k < m; k++)
                {
                    T z = x * A.GetAij(i, k);
                    T y = z + A.GetAij(j, k);
                    if (abs(y) < 1.19e-06)
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
            T x = B.GetBi(i) / A.GetAij(i, i);
            if (abs(x) < 1.19e-06)
            {
                x = 0;
            }
            cout << x << endl;
        }
    }
};