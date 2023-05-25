#include "matrix.h"
#include "vector.h"
#include "solver.h"

#include <iostream>
#include <clocale>

int main()
{
	std::setlocale(LC_CTYPE, "RUSSIAN");

	size_t rows, cols;
	std::cout << "Введите число неизвестных, затем число уравнений" << std::endl;
	std::cin >> cols >> rows;

	Matrix<double> m(rows, cols);
	Vector<double> b(rows);
	Solver s;

	std::cout << "Введите основную матрицу системы" << std::endl;
	std::cin >> m;
	std::cout << "Введите вектор коэффициентов" << std::endl;
	std::cin >> b;

	std::cout << "Матрица будет иметь следующий вид:" << std::endl << m;
	std::cout << "Введённые коэффициенты:" << std::endl << b;

	Vector<double> x(m.getWidth());

	s.solve(m, x, b);
	if (s.isCompatible())
	{
		std::cout << "Найденное решение системы: " << x;
		s.check(m, x, b);
	}

	else
	{
		std::cout << "Система не совместна" << std::endl;
	}
}