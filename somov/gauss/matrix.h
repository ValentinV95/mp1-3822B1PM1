#pragma once

#include <iostream>
#include <algorithm>

template<class T>
class Matrix
{
public:
	Matrix(size_t h, size_t w);
	Matrix(const Matrix<T>& m);
	~Matrix();

	void set(size_t posx, size_t posy, T t);
	void swap_rows(size_t row1, size_t row2);

	T& get(size_t posx, size_t posy);
	size_t getWidth();
	size_t getHeight();

	T& get(size_t posx, size_t posy) const;
	size_t getWidth() const;
	size_t getHeight() const;

	template <class V> friend std::ostream& operator<<(std::ostream& o, const Matrix<V>& m);
	template <class V> friend std::istream& operator>>(std::istream& in, Matrix<V>& m);
private:
	size_t width, height;
	T** data;
};

template<class T>
Matrix<T>::Matrix(size_t h, size_t w)
{
	width = w;
	height = h;
	data = new T * [height];

	for (size_t i = 0; i < height; i++)
		data[i] = new T[width]();
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
	width = m.width;
	height = m.height;
	data = new T * [height];

	for (size_t i = 0; i < height; i++)
	{
		data[i] = new T[width];
		for (size_t j = 0; j < width; j++)
			data[i][j] = m.data[i][j];
	}
}

template<class T>
Matrix<T>::~Matrix()
{
	for (size_t i = 0; i < height; i++)
		delete data[i];
	delete data;
}

template<class T>
void Matrix<T>::set(size_t posx, size_t posy, T t)
{
	data[posx][posy] = t;
}

template<class T>
void Matrix<T>::swap_rows(size_t row1, size_t row2)
{
	std::swap(data[row1], data[row2]);
}

template<class T>
T& Matrix<T>::get(size_t posx, size_t posy)
{
	return data[posx][posy];
}

template<class T>
size_t Matrix<T>::getWidth()
{
	return width;
}

template<class T>
size_t Matrix<T>::getHeight()
{
	return height;
}

template<class T>
T& Matrix<T>::get(size_t posx, size_t posy) const
{
	return data[posx][posy];
}

template<class T>
size_t Matrix<T>::getWidth() const
{
	return width;
}

template<class T>
size_t Matrix<T>::getHeight() const
{
	return height;
}

template<class T>
std::ostream& operator<<(std::ostream& o, const Matrix<T>& m)
{
	for (size_t row = 0; row < m.height; row++)
	{
		for (size_t col = 0; col < m.width; col++)
			o << m.data[row][col] << " ";
		o << std::endl;
	}
	return o;
}

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& m)
{
	for (size_t row = 0; row < m.height; row++)
		for (size_t col = 0; col < m.width; col++)
			in >> m.data[row][col];

	return in;
}