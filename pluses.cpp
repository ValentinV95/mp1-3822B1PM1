#include <iostream>#include <algorithm>
#include <stdlib.h>
using namespace std;


class complex {
private:
    double im, re;
public:
    complex() {
        im = 0;
        re = 0;
    }
    complex(double _im,double _re) {
        if (_im == 0) {
            re = _re;
        }
        else {
            re = _re;
            im = _im;
        }
    }

    complex operator + (complex A) {
        complex res;
        res.im = im + A.im;
        res.re = re + A.re;
    }

    complex operator - (complex A) {
        complex res;
        res.im = im - A.im;
        res.re = re - A.re;
    }

    complex operator * (complex A) {
        complex res;
        res.im = re * A.im + im * A.re;
        res.re = re*A.re - im*A.im;
    }

    complex& operator = (complex &A) {
        return (*this);
    }
    

};

template<typename T>
class Vec {
private:
    int n;
    T* arr;
public:
    Vec(int _n) {
        _n = n;
        arr = new T[n];
    };

    T& operator [] (int i) {
        return arr[i];
    }

    Vec<T> operator() (const Vec& vec1, const Vec& vec2) {
        Vec A(vec1.n);
        for (int i = 0; i < vec1.n; i++) {
            A.arr[i] = vec1.arr[i] * vec2.arr[i];
        }
    }

    void Set_vec() {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }


    ~Vec() {
        delete[] arr;
        n = 0;
    }
};


template<typename T>
class matrix {
private:
    T** arr;
    int n, m; //размерность
public:
    matrix(int _n, int _m) {
        n = _n;
        m = _m;
        arr = new T * [m];
        for (int i = 0; i < m; i++) {
            arr[i] = new T[n];
        }
    }

    T& operator()(int ind1, int ind2) {
        return arr[ind1][ind2];
    }


    void set_matrix(int _n, int _m) {  ///НАДО РАНДОМОМ
        n = _n;
        m = _m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> arr[i][j];
            }
        }
    }

    void get_matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Vec<T> operator () (matrix<T> M,Vec<T> A) {
        Vec<T> B(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                B[i] += M.arr[i][j];
            }
        }
        return B;
    }

    ~matrix() {
        for (int i = 0; i < n; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        n = 0;
    }
};



int main()
{
    int n, m;
    cin >> n >> m;
    matrix<complex> A(n, m);
    Vec<complex> B(n);
    A.set_matrix(n, m);
    B.Set_vec();
    Vec<complex>C = (A, B);

}

