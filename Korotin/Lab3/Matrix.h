#pragma once
#include "Vector.h"
template <class T>
class Matrix {
    size_t size;
    T* cap;
public:
    Matrix(size_t _size = 5) {
        size = _size;
        cap = new T[_size * _size];
    }
    void reSize(size_t _size) {
        delete[] cap;
        size = _size;
        cap = new T[_size * _size];
    }
    ~Matrix() {
        delete[] cap;
    }
    size_t GetSize() {
        return size;
    }
    T& operator[] (int i) { return cap[i]; }
    template <class V>
    friend std::ostream& operator<< (std::ostream& out, Matrix<V>& A);
    template <class V>
    friend std::istream& operator>> (std::istream& in, Matrix<V>& A);
};
template <class V>
std::ostream& operator<< (std::ostream& out, Matrix<V>& A) {
    for (int i = 0; i < A.size; i++) {
        out << "( ";
        for (int j = 0; j < A.size; ++j) out << A.cap[i * A.size + j] << " ";
        out << ")" << std::endl;
    }
    return out;
}
template <class V>
std::istream& operator>> (std::istream& in, Matrix<V>& A) {
    for (int i = 0; i < A.size * A.size; ++i) in >> A.cap[i];
    return in;
}
