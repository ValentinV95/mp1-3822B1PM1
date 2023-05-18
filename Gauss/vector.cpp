#pragma once
#include "vector.h"
template<typename T>
    vec<T>::vec (int _n){
        n = _n;
        arr = new T[n];
        for (int i = 0; i < n; i++){
            arr[i] = -2;
        }
    }
template<typename T>
T &vec<T>::operator[](int ind) {
    return arr[ind];
}

template<typename T>
    void vec<T>::set_vec(int _n){
        n = _n;
        for (int i = 0 ; i < n;i++){
            cin >> arr[i];
        }
    }

template<typename T>
    void vec<T>:: get_vec(int _n){
        n = _n;
        for (int i = 0; i < n;i++){
            cout << "( " <<arr[i] << " )\n";
        }
    }

template<typename T>
    vec<T>::~vec(){
        delete [] arr;
        n = 0;
    }