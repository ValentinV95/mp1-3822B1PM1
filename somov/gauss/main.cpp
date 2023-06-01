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

	std::cout << "������� ����� �����������, ����� ����� ���������." << std::endl;
	std::cin >> cols >> rows;

	Matrix<double> m(rows, cols);
	Vector<double> b(rows);
	Solver s;

	std::cout << "�������� ����� ������:\n1. ���� ������� ��� �������.\n2. ������������� ������� ������� ���." << std::endl;
	std::cin >> ch;

	switch (ch)
	{
	case 1:
		std::cout << "������� �������� ������� �������" << std::endl;
		std::cin >> m;
		std::cout << "������� ������ �������������" << std::endl;
		std::cin >> b;

		std::cout << "������� ����� ����� ��������� ���:" << std::endl << m;
		std::cout << "�������� ������������:" << std::endl << b;
		break;
	case 2:
		m.randFill();
		b.randFill();
		break;
	default:
		std::cout << "����� �� ���������." << std::endl;
		validInput = false;
		break;
	}

	if (validInput)
	{
		Vector<double> x = s.solve(m, b);
		if (s.isCompatible())
		{
			std::cout << "��������� ������� �������:\n" << x;
			s.evaluate(m, x, b);
		}

		else
		{
			std::cout << "������� �� ���������" << std::endl;
		}
	}
}