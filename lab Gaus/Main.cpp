#include "iostream"
#include "Matrix.h"
#include "Solver.h"
#include "Vector.h"

template <typename T>
void rand_slou(Matrix<T>& A, Vector<T>& b);

int main() {
	setlocale(LC_ALL, "Russian");
	int choice, n, choice_rand;
	std::cout << "Введите размер квадратной матрицы: ";
	std::cin >> n;
	std::cout << "Выберите тип данных: float-1, double-2: ";
	std::cin >> choice;
	std::cout << "Выберите тип заполнения: рандом-1, самостоятельно-2: ";
	std::cin >> choice_rand;
	try
	{
		switch (choice) {
		case 1: {
			Matrix<float> A(n,n);
			Vector<float> b(n), x(n);
			Solver<float> s;
			if (choice_rand == 1) {
				rand_slou(A, b);
				A.Print();
				b.Print();
			}
			else {
				std::cout << "Введите элементы матрицы A" << std::endl;
				A.Scan();
				std::cout << "Введите элементы матрицы b" << std::endl;
				b.Scan();
			}
			s.Gaus(A, b, x);
			std::cout << "Ответ" << std::endl;
			x.Print();
			break;
		}
		case 2: {
			Matrix<double> A(n, n);
			Vector<double> b(n), x(n);
			Solver<double> s;
			if (choice_rand == 1) {
				rand_slou(A, b);
				A.Print();
				b.Print();
			}
			else {
				std::cout << "Введите элементы матрицы A" << std::endl;
				A.Scan();
				std::cout << "Введите элементы матрицы b" << std::endl;
				b.Scan();
			}
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

template <typename T>
void rand_slou(Matrix<T>& A, Vector<T>& b) {
	for (int i = 0; i < A.GetM(); i++) {
		for (int j = 0; j < A.GetN(); j++) {
			A.SetValue(i, j, ((T)rand()) / 100);
		}
		b.SetValue(i, ((T)rand()) / 100);
	}
}