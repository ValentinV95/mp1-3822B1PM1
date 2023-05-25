#include "iostream"
#include "Matrix.h"
#include "Solver.h"
#include "Vector.h"

int main() {
	setlocale(LC_ALL, "Russian");
	int choice, n;
	std::cout << "Введите размер квадратной матрицы: ";
	std::cin >> n;
	std::cout << "Выберите тип данных: float-1, float-2: ";
	std::cin >> choice;
	try
	{
		switch (choice) {
		case 1: {
			Matrix<float> A(n,n);
			Vector<float> b(n), x(n);
			Solver<float> s;
			std::cout << "Введите элементы матрицы A" << std::endl;
			A.Scan();
			std::cout << "Введите элементы матрицы b" << std::endl;
			b.Scan();
			s.Gaus(A, b, x);
			std::cout << "Ответ" << std::endl;
			x.Print();
			break;
		}
		case 2: {
			Matrix<double> A(n, n);
			Vector<double> b(n), x(n);
			Solver<double> s;
			std::cout << "Введите элементы матрицы A" << std::endl;
			A.Scan();
			std::cout << "Введите элементы матрицы b" << std::endl;
			b.Scan();
			s.Gaus(A, b, x);
			x.Print();
			break;
		}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
