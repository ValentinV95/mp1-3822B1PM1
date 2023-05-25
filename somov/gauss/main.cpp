#include "matrix.h"
#include "vector.h"
#include "solver.h"

#include <iostream>
#include <clocale>

int main()
{
	std::setlocale(LC_CTYPE, "RUSSIAN");

	size_t rows, cols;
	std::cout << "������� ����� �����������, ����� ����� ���������" << std::endl;
	std::cin >> cols >> rows;

	Matrix<double> m(rows, cols);
	Vector<double> b(rows);
	Solver s;

	std::cout << "������� �������� ������� �������" << std::endl;
	std::cin >> m;
	std::cout << "������� ������ �������������" << std::endl;
	std::cin >> b;

	std::cout << "������� ����� ����� ��������� ���:" << std::endl << m;
	std::cout << "�������� ������������:" << std::endl << b;

	Vector<double> x(m.getWidth());

	s.solve(m, x, b);
	if (s.isCompatible())
	{
		std::cout << "��������� ������� �������: " << x;
		s.check(m, x, b);
	}

	else
	{
		std::cout << "������� �� ���������" << std::endl;
	}
}