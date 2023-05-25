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

	template<class T> void check(const Matrix<T>& m, const Vector<T>& x, const Vector<T>& b);
	template<class T> void solve(Matrix<T> m, Vector<T>& x, Vector<T> b);
	bool isCompatible() { return compatibility; }

private:
	template<class T> void getMax(T& lead, const Matrix<T>& m, size_t pos);
	template<class T> bool checkCompatibility(const Matrix<T>& m, const Vector<T>& b);

	template<class T> void toTriangle(Matrix<T>& m, Vector<T>& x, Vector<T>& b);
	template<class T> void toRowForm(Matrix<T>& m, Vector<T>& x, Vector<T>& b);
	template<class T> void fillX(Matrix<T>& m, Vector<T>& x, Vector<T>& b);

	bool compatibility;

	size_t proc_col;
	size_t proc_row;
	size_t max_col;
	size_t max_row;
};

Solver::Solver()
{
	proc_col = 0;
	proc_row = 0;
	max_row = 0;
	max_col = 0;
	compatibility = true;
}

template<class T>
void Solver::check(const Matrix<T>& m, const Vector<T>& x, const Vector<T>& b)
{
	for (size_t i = 0; i < m.getHeight(); i++)
	{
		T res = 0;

		for (size_t j = 0; j < m.getWidth(); j++)
			res += m.get(i, j) * x[j];

		std::cout << "Разница между результатом вычисления строки " << i << " и строки вектора коэффициентов: " << (res - b[i]) << std::endl;
	}
}

template<class T>
void Solver::solve(Matrix<T> m, Vector<T>& x, Vector<T> b)
{
	toTriangle(m, x, b);
	compatibility = checkCompatibility(m, b);

	if (compatibility)
	{
		toRowForm(m, x, b);
		fillX(m, x, b);
	}
}

template<class T>
void Solver::getMax(T& lead, const Matrix<T>& m, size_t pos)
{
	lead = m.get(proc_row, pos);
	max_row = proc_row;
	max_col = pos;
	for (size_t i = proc_col; i < m.getHeight(); i++)
		if (std::abs(m.get(i, pos)) > std::abs(lead))
		{
			lead = m.get(i, pos);
			max_row = i;
		}
}

// Считаем ранг матрицы системы и расширенной матрицы, чтобы проверить систему на совместность
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

	proc_col = 0;
	proc_row = 0;

	return (matrix_rows == augmented_rows) ?
		(true) : 
		(false);
}

// Переход к треугольному виду
template<class T>
void Solver::toTriangle(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	T lead = 0;
	T fact = 0;

	for (size_t row = 0; row < m.getHeight(); row++)
	{
		getMax(lead, m, proc_col);
		if (std::abs(lead) < std::numeric_limits<T>::epsilon()) continue;
		m.swap_rows(max_row, row);
		b.swap(max_row, row);
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

		proc_col++;
		proc_row++;
	}

	proc_col = 0;
	proc_row = 0;
}

// Переход от треугольного вида к простейшему
template<class T>
void Solver::toRowForm(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	T lead = 0;
	T fact = 0;

	for (size_t row = 0; row < m.getHeight(); row++)
	{
		getMax(lead, m, proc_col);
		if (std::abs(lead) < std::numeric_limits<T>::epsilon()) continue;
		m.swap_rows(max_row, row);
		b.swap(max_row, row);
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

		proc_col++;
		proc_row++;
	}

	for (size_t row = 0; row < m.getHeight(); row++)
	{
		for (size_t col = row; col < m.getWidth(); col++)
		{
			lead = m.get(row, col);
			if (std::abs(lead) > std::numeric_limits<T>::epsilon()) break;
		}

		for (size_t col = 0; col < m.getWidth(); col++)
			m.set(row, col, m.get(row, col) / lead);

		b[row] /= lead;
	}
}

// Заполняем столбец иксов
template<class T>
void Solver::fillX(Matrix<T>& m, Vector<T>& x, Vector<T>& b)
{
	proc_row = 0;
	for (size_t row = 0; row < m.getHeight(); row++)
	{
		for (size_t col = row; col < m.getWidth(); col++)
			if (std::abs(m.get(row, col)) > std::numeric_limits<T>::epsilon())
			{
				x[proc_row] = b[row];
				proc_row++;
				break;
			}
	}
}