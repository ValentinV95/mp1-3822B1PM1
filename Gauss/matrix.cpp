#pragma once
#include "matrix.h"
#ifndef MATRIX_H
#define MATRIX_H

template <typename T>

    matrix<T>::matrix(int _n){
        n = _n;
        arr = new T*[n];
        for (int i = 0; i< n;i++){
            arr[i] = new T[n];
        }
    }
    template<typename T>
    T &matrix<T>::operator()(int ind1, int ind2) {
        return arr[ind1][ind2];
}

    template<typename T>
    matrix<T>::matrix(const matrix <T> &A){
        n = A.n;
        arr = new T*[n];
        for (int i = 0; i< n;i++){
            arr[i] = new T[n];
        }

        for (int i = 0; i < n;i++){
            for (int j = 0; j < n;j++){
                arr[i][j] = A.arr[i][j];
            }
        }
    }


    template<typename T>
    void matrix<T>::set_matrix (int _n){
        n = _n;
        for(int i = 0; i < n;i++){
            for (int j = 0; j < n; j++){
                cin >> arr[i][j];
            }
        }
    };

    template<typename T>
    void matrix<T>:: get_matrix(int _n){
        n = _n;
        for (int i = 0; i < n;i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << "\n";
        }
    }
    template<typename T>
    matrix<T>::~matrix(){
        for (int i = 0; i < n;i++){
            delete []arr[i];
        }
        delete[] arr;
        n = 0;
    }

#endif