#pragma once

#include "matrix.h"
#include "vector.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

class Solver
{
public:
	Solver();

	template<class T> void evaluate(const Matrix<T>& m, const Vector<T>& x, const Vector<T>& b);
	template<class T> Vector<T> solve(Matrix<T> m, Vector<T> b);
	bool isCompatible() { return compatible; }

private:
	// Поиск строки с наибольшим элементом 
	template<class T> T getMax(const Matrix<T>& m, size_t pos);
	// Проверка системы на совместность с помощью т. Кронекера-Капелли 
	template<class T> bool checkCompatibility(const Matrix<T>& m, const Vector<T>& b);

	// Переход к треугольному виду
	template<class T> void toTriangle(Matrix<T>& m, Vector<T>& x, Vector<T>& b);
	// Переход от треугольного вида к простейшему
	template<class T> void toRowForm(Matrix<T>& m, Vector<T>& x, Vector<T>& b);
	// Заполнение вектора решения
	template<class T> void fillX(Matrix<T>& m, Vector<T>& x, Vector<T>& b);

	bool compatible;

	size_t processed;
	size_t max_col;
	size_t max_row;
};

Solver::Solver()
{
	processed = 0;
	max_row = 0;
	max_col = 0;
	compatible = true;
}

template<class T>
void Solver::evaluate(const Matrix<T>& m, const Vector<T>& x, const Vector<T>& b)
{
	std::cout << "Относительная и абсолютная разница между полученным и ожидаемым результатом" << std::endl;
	for (size_t i = 0; i < m.getHeight(); i++)
	{
		T res = 0;

		for (size_t j = 0; j < m.getWidth(); j++)
			res += m.get(i, j) * x[j];

		std::cout << "Строка " << i+1 << ": " << res - b[i] << ", " << (res - b[i])/b[i] << std::endl;
	}
}

template<class T>
Vector<T> Solver::solve(Matrix<T> m, Vector<T> b)
{
	Vector<T> x(m.getWidth());
	toTriangle(m, x, b);
	compatible = checkCompatibility(m, b);

	if (compatible)
	{
		toRowForm(m, x, b);
		fillX(m, x, b);
	}

	return x;
}

template<class T>
T Solver::getMax(const Matrix<T>& m, size_t pos)
{
	T lead = m.get(processed, pos);
	max_row = processed;
	max_col = pos;
	for (size_t i = processed; i < m.getHeight(); i++)
		if (std::abs(m.get(i, pos)) > std::abs(lead))
		{
			lead = m.get(i, pos);
			max_row = i;
		}

	return lead;
}

template<class T>
bool Solver::checkCompatibility(const Matrix<T>& m, const Vector<T>& b)
{
	bool nonzero_row = false;
	size_t matrix_rows = 0;
	size_t augmented_rows = 0;

	for (size_t row = 0; row < m.getHeight(); row++)
	{
		nonzero_row = false;

		for (size_t col = 0; col < m.getWidth(); col++)
		{
			if (std::abs(m.get(row, col)) > std::numeric_limits<T>::epsilon())
			{
				matrix_rows++;
				augmented_rows++;
				nonzero_row = true;
				break;
			}
		}

		if (nonzero_row) continue;

		if (std::abs(b[row]) > std::numeric_limits<T>::epsilon())
			augmented_rows++;

	}

	return (matrix_rows == augmented_rows) ?
		(true) : 
		(false);
}

template<class T>
void Solver::toTriangle(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	T lead = 0;
	T fact = 0;

	for (size_t row = 0; row < m.getHeight() && processed < m.getWidth(); row++, processed++)
	{
		lead = getMax(m, processed);
		if (std::abs(lead) < std::numeric_limits<T>::epsilon())
		{
			processed++;
			continue;
		}
		m.swapRows(max_row, row);
		b.swapRows(max_row, row);
		max_row = row;
		for (size_t i = row + 1; i < m.getHeight(); i++)
		{
			fact = m.get(i, max_row) / lead;
			for (size_t j = 0; j < m.getWidth(); j++)
			{
				if (j == max_col)
					m.set(i, j, T(0));
				else
					m.set(i, j, m.get(i, j) - fact * m.get(max_row, j));
			}
			b[i] -= fact * b[max_row];
		}
	}

	processed = 0;
}

template<class T>
void Solver::toRowForm(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	T lead = 0;
	T fact = 0;

	for (size_t row = 0; row < m.getHeight() && processed < m.getWidth(); row++, processed++)
	{
		lead = getMax(m, processed);
		if (std::abs(lead) < std::numeric_limits<T>::epsilon())
		{
			processed++;
			continue;
		}
		
		m.swapRows(max_row, row);
		b.swapRows(max_row, row);
		max_row = row;
		for (size_t i = 0; i < row; i++)
		{
			fact = m.get(i, max_row) / lead;
			for (size_t j = 0; j < m.getWidth(); j++)
			{
				if (j == max_col)
					m.set(i, j, T(0));
				else
					m.set(i, j, m.get(i, j) - fact * m.get(max_row, j));
			}
			b[i] -= fact * b[max_row];
		}
	}

	for (size_t row = 0; row < m.getHeight(); row++)
	{
		for (size_t col = row; col < m.getWidth(); col++)
		{
			lead = m.get(row, col);
			if (std::abs(lead) > std::numeric_limits<T>::epsilon()) break;
		}

		if (std::abs(lead) < std::numeric_limits<T>::epsilon()) continue;

		for (size_t col = 0; col < m.getWidth(); col++)
			m.set(row, col, m.get(row, col) / lead);

		b[row] /= lead;
	}

	processed = 0;
}

template<class T>
void Solver::fillX(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	for (size_t row = 0; row < m.getWidth() && row < b.getHeight(); row++)
		x[row] = b[row];
}