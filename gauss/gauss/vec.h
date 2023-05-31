#pragma once
#include <iostream>

using namespace std;
template<typename T>
class vec {
private:
    int n;
    T* arr;
public:
    vec(int _n) {
        n = _n;
        arr = new T[n];
        for (int i = 0; i < n; i++) {
            arr[i] = -2;
        }
    }

    T& operator[](int ind) {
        return arr[ind];
    }

    void set_vec(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }

    void get_vec(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            cout << "( " << arr[i] << " )\n";
        }
    }

    ~vec() {
        delete[] arr;
        n = 0;
    }
};
