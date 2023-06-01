#pragma once

#include <iostream>
#include <algorithm>
#include <random>

#define RANGE 100000000
#define MIN -100000000

template <class T>
class Vector
{
public:
	Vector(size_t h);
	Vector(const Vector<T>& v);
	~Vector();

	T& operator[](size_t pos);
	size_t getHeight();
	T& operator[](size_t pos) const;
	size_t getHeight() const;

	void swapRows(size_t pos1, size_t pos2);
	void randFill();

	template<class V> friend std::ostream& operator<<(std::ostream& o, const Vector<V>& v);
	template<class V> friend std::istream& operator>>(std::istream& in, Vector<V>& v);

private:
	size_t height;
	T* data;
};

template<class T>
Vector<T>::Vector(size_t h)
{
	height = h;
	data = new T[height]();
}

template<class T>
Vector<T>::Vector(const Vector<T>& v)
{
	height = v.height;
	data = new T[height];
	for (size_t i = 0; i < height; i++)
		data[i] = v.data[i];
}

template<class T>
Vector<T>::~Vector()
{
	delete[] data;
}

template<class T>
size_t Vector<T>::getHeight()
{
	return height;
}

template<class T>
T& Vector<T>::operator[](size_t pos)
{
	return data[pos];
}

template<class T>
size_t Vector<T>::getHeight() const
{
	return height;
}

template<class T>
T& Vector<T>::operator[](size_t pos) const
{
	return data[pos];
}

template<class T>
void Vector<T>::swapRows(size_t pos1, size_t pos2)
{
	std::swap(data[pos1], data[pos2]);
}

template<class T>
void Vector<T>::randFill()
{
	std::srand(std::time(nullptr));
	for (size_t r = 0; r < height; r++)
		data[r] = std::rand() % RANGE - MIN;
}

template<class T>
std::ostream& operator<<(std::ostream& o, const Vector<T>& v)
{
	for (size_t i = 0; i < v.height; i++)
		o << "v[" << i+1 << "]=" << v.data[i] << std::endl;
	return o;
}

template<class T>
std::istream& operator>>(std::istream& in, Vector<T>& v)
{
	for (size_t i = 0; i < v.height; i++)
		in >> v.data[i];
	return in;
}