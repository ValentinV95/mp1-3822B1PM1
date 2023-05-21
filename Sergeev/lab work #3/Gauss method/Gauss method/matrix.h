#pragma once
const double MAXM = 100000;
const double MINM = -100000;

template <class T>
class matrix
{
protected:
    int size;
    T* arr;
public:

    matrix(int _size = 3)
    {
        size = _size;
        arr = new T[size * size];

        #pragma omp parallel for
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                arr[i * size + j] = static_cast<T>(0.0);
    }
    ~matrix()
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
    T& operator[](int i)
    {
        return arr[i];
    }
    void fill(int mod)//auto-random or manual filling matrix (MAX & MIN in vector.h)   
    {
        if (mod)
        {
            //"#pragma omp parallel for" will fill matrix equal rows
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    arr[i * size + j] = static_cast<T>((static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * (MAXM - MINM) + MINM);
        }
        else
        {
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    std::cin >> arr[i * size + j];
        }
    }
    int get_size()
    {
        return size;
    }
    matrix& operator=(matrix& _m)
    {
        if (size == _m.get_size())
        {
            #pragma omp parallel for
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    arr[i * size + j] = _m[i * size + j];

            return *this;
        }
        else throw "not equal sizes";
    }
    matrix& operator=(const matrix& _m)
    {
        if (size == _m.get_size())
        {
            #pragma omp parallel for
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    arr[i * size + j] = _m[i * size + j];

            return *this;
        }
        else throw "not equal sizes";
    }
};

template <class T>
std::istream& operator>> (std::istream& in, matrix<T>& m)
{
    for (int i = 0; i < m.get_size(); i++)
        for (int j = 0; j < m.get_size(); j++)
            in >> m[i * m.get_size() + j];
    return in;
}

template <class T>
std::ostream& operator<< (std::ostream& out, matrix<T>& m)
{
    for (int i = 0; i < m.get_size(); i++)
    {
        for (int j = 0; j < m.get_size(); j++)
            out << m[i * m.get_size() + j] << " ";

        out << "\n";
    }
    return out;
}