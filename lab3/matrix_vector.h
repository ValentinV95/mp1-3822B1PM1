#pragma once
template <class T1>
class matrix
{
private:
    int n;
    //T1** A;
public:T1** A;
      matrix()
      {
          n = 0;
      }
      matrix(int _n)
      {
          n = _n;
          A = (T1**)new T1[n];
          for (int i = 0; i < n; i++)
              A[i] = (T1*)new T1[n];
          /* for (int i = 0; i < n; i++)
           {
               for (int j = 0; j < n; j++)
               {
                   A[i][j] = ((T1)rand() / ((T1)RAND_MAX));
                   cout << A[i][j] << " ";
               }
               cout << endl;
           }*/
          for (int i = 0; i < n; i++)
              for (int j = 0; j < n; j++)
                  A[i][j] = 0;
      }
      matrix(const matrix& c)
      {
          n = c.n;
          A = (T1**) new T1 * [n];
          for (int i = 0; i < n; i++)
              A[i] = (T1*) new T1[n];
          for (int i = 0; i < n; i++)
              for (int j = 0; j < n; j++)
                  A[i][j] = c.A[i][j];
      }
      ~matrix()
      {
          for (int i = 0; i < n; i++)
              delete[] A[i];
          delete[] A;
      }
      T1 GetAij(int i, int j)
      {
          return A[i][j];
      }
      void SetAij(int i, int j, T1 c)
      {
          A[i][j] = c;
      }
};

template <class T2>
class vector
{
private:
    //T2* B;
    int m;
public:T2* B;
      vector()
      {
          m = 0;
      }
      vector(int _m)
      {
          m = _m;
          B = (T2*)new T2[m];
          /*for (int i = 0; i < m; i++)
          {
              B[i] = ((T2)rand() / ((T2)RAND_MAX));
              cout <<"  "<< B[i] << " ";
              cout << endl;
          }*/
          for (int i = 0; i < m; i++)
              B[i] = 0;
      }
      vector(const vector& c)
      {
          m = c.m;
          B = (T2*)new T2[m];
          for (int i = 0; i < m; i++)
              B[i] = c.B[i];
      }
      ~vector()
      {
          delete[]B;
      }
      T2 GetBi(int i)
      {
          return B[i];
      }
      void SetBi(int i, T2 c)
      {
          B[i] = c;
      }
};