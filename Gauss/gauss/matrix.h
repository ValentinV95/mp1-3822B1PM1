#pragma once
#include <iostream>
using namespace std;
template<typename T>
class matrix {
private:
    T **arr;
    int n; //размерность
public:
    matrix(int _n) {
        n = _n;
        arr = new T *[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new T[n];
        }
    }

    T &operator()(int ind1, int ind2) {
        return arr[ind1][ind2];
    }

    matrix(const matrix<T> &A) {
        n = A.n;
        arr = new T *[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new T[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = A.arr[i][j];
            }
        }
    }


    void set_matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }
    };

    void get_matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << "\n";
        }
    }

    ~matrix(){
        for (int i = 0; i < n;i++){
            delete[] arr[i];
        }
        delete[] arr;
        n = 0;
    }
};





