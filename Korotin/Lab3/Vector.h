#include <iostream>
#include <locale>
#include <cmath>

template <class T>
class Vec {
protected:
    size_t size;
    T* mas;
public:
    Vec(size_t _size = 5) {
        size = _size;
        mas = new T[size];
    }
    Vec(const Vec& v) {
        size = v.size;
        mas = new T[size];
        for (int i = 0; i < size; ++i) mas[i] = v.mas[i];
    }
    ~Vec() {
        delete[] mas;
    }
    T& operator[] (int i) {
        return mas[i];
    }
    void reSize(size_t _size) {
        T buf[size];
        for (int i = 0; i < size; ++i) buf[i] = mas[i];
        delete[] mas;
        mas = new T[_size];
        for (int i = 0; i < fmin(size, _size); ++i) mas[i] = buf[i];
        size = _size;
    }
    void setVec(size_t _size, T* arr) {
        size = _size;
        mas = arr;
    }
    size_t& GetSize() { return size; }
    T*& GetMas() { return mas; }
    Vec operator+ (const Vec& v2) {
        if (size == v2.size) {
            Vec<T> out;
            for (int i = 0; i < size; ++i) {
                out = mas[i] + v2.mas[i];
            }
            return out;
        }
    }
    Vec operator- (const Vec& v2) {
        Vec<T> out(size);
        if (size == v2.size) {
            for (int i = 0; i < size; ++i) {
                T buf = mas[i] - v2.mas[i];
                out.mas[i] = buf;
            }
            return out;
        }
    }
    Vec& operator= (Vec v2) {
        if (size = v2.size) {
            for (int i = 0; i < size; ++i) mas[i] = v2.mas[i];
            return *this;
        }
    }
    Vec& operator+= (const Vec& v2) {
        if (size == v2.size) {
            *this = *this + v2;
            return *this;
        }
    }
    Vec& operator-= (const Vec& v2) {
        if (size == v2.size) {
            *this = *this - v2;
            return *this;
        }
    }
    Vec operator* (T a) {
        Vec<T> out(size);
        for (int i = 0; i < size; ++i) out[i] = a * mas[i];
        return out;
    }
    Vec operator*= (T a) {
        *this = *this * a;
        return *this;
    }
    void swap(Vec& v2) {
        std::swap(mas, v2.mas);
    }
    template <class V>
    friend std::istream& operator>> (std::istream& in, Vec<V>& v);
    template <class V>
    friend std::ostream& operator<< (std::ostream& out, Vec<V>& v);
};
template <class V>
std::istream& operator>> (std::istream& in, Vec<V>& v) {
    for (int i = 0; i < v.size; ++i) in >> v.mas[i];
    return in;
}
template <class V>
std::ostream& operator<< (std::ostream& out, Vec<V>& v) {
    out << "( ";
    for (int i = 0; i < v.size; ++i) out << v.mas[i] << " ";
    out << ")";
    return out;
}