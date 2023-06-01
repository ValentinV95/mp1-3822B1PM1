#include "matrix.h"
#include "vector.h"
#include "solver.h"

#include <iostream>
#include <clocale>
#include <limits>

int main()
{
	std::setlocale(LC_CTYPE, "RUSSIAN");

	size_t rows;
	size_t cols;
	int ch;
	bool validInput = true;

	std::cout << "Введите число неизвестных, затем число уравнений." << std::endl;
	std::cin >> cols >> rows;

	Matrix<double> m(rows, cols);
	Vector<double> b(rows);
	Solver s;

	std::cout << "Выберите режим работы:\n1. Ввод матрицы СЛУ вручную.\n2. Автоматически создать матрицу СЛУ." << std::endl;
	std::cin >> ch;

	switch (ch)
	{
	case 1:
		std::cout << "Введите основную матрицу системы" << std::endl;
		std::cin >> m;
		std::cout << "Введите вектор коэффициентов" << std::endl;
		std::cin >> b;

		std::cout << "Матрица будет иметь следующий вид:" << std::endl << m;
		std::cout << "Введённые коэффициенты:" << std::endl << b;
		break;
	case 2:
		m.randFill();
		b.randFill();
		break;
	default:
		std::cout << "Выбор не распознан." << std::endl;
		validInput = false;
		break;
	}

	if (validInput)
	{
		Vector<double> x = s.solve(m, b);
		if (s.isCompatible())
		{
			std::cout << "Найденное решение системы:\n" << x;
			s.evaluate(m, x, b);
		}

		else
		{
			std::cout << "Система не совместна" << std::endl;
		}
	}
}