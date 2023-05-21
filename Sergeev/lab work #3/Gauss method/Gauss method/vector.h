#pragma once

static double MAX = 100000;
static double MIN = -100000;

template <class T>
class vector
{
protected:
    int size;
    T* arr;
public:
    vector(int _size = 3)
    {
        size = _size;
        arr = new T[size];
        for (int i = 0; i < size; i++)
            arr[i] = static_cast<T>(0.0);
    }
    ~vector()
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
    T& operator [](int i)
    {
        return arr[i];
    }
    const T& operator [](int i) const
    {
        return arr[i];
    }
    void fill(int mod)//auto-random or manual filling vector
    {
        if (mod)
        {
            for (int i = 0; i < size; i++)
                arr[i] = static_cast<T>((static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * (MAX - MIN) + MIN);
        }
        else
        {
            for (int i = 0; i < size; i++)
                std::cin >> arr[i];
        }
    }
    int get_size()
    {
        return size;
    }
    int get_size() const
    {
        return size;
    }
    vector& operator=(vector& _v)
    {
        if (size != _v.get_size()) throw "not equal sizes";
        for (int i = 0; i < size; i++)
            arr[i] = _v[i];
        return *this;
    }
    vector& operator=(const vector& _v)
    {
        if (size != _v.get_size()) throw "not equal sizes";
        for (int i = 0; i < size; i++)
            arr[i] = _v[i];
        return *this;
    }
    vector operator-(vector& _v)
    {
        if (size != _v.get_size()) throw "not equal sizes";
        vector<T> res(size);
        for (int i = 0; i < size; i++)
            res[i] = arr[i] - _v[i];
        return res;
    }
};

template <class T>
std::istream& operator>> (std::istream& in, vector<T>& v)
{
    for (int i = 0; i < v.get_size(); i++)
        in >> v[i];
    return in;
}

template <class T>
std::ostream& operator<< (std::ostream& out, vector<T>& v)
{
    for (int i = 0; i < v.get_size(); i++)
        out << v[i] << "\n";
    return out;
}