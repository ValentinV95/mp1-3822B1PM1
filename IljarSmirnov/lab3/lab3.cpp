#include <iostream>
#include <exception>
#include "vector_matrix.h"
#include "Gauss_solver.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	int choicef;
	char fl1 = 1;
	std::cout << "Введите размер квадратной матрицы одним числом" << std::endl;
	std::cin >> n;
	std::cout<<"Введите тип элементов в матрице 1 - для float, 2 - для double"<<std::endl;
	do {
		std::cin>>choicef;
		if ((choicef != 1) && (choicef != 2)) {
			std::cout<<"Неверный ввод. Попробуйте снова."<<std::endl;;
		}
		else fl1 = 0;
	} while (fl1);
	try {
		switch (choicef) {
		case 1: {
			matrix<float> A(n, n);
			vector <float>b(n);
			vector<float>x(n);
			solver<float>solv;
			std::cout << "Введите матрицу А по одному числу" << std::endl;
			for (int i = 0; i < n * n; i++) {
				std::cin >> A.mas[i];
			}
			std::cout << "Введите матрицу b по одному числу" << std::endl;
			for (int i = 0; i < n; i++) {
				std::cin >> b.mas[i];
			}
			solv.JG(A, b, x);
			for (int i = 0; i < n; i++) {
				std::cout << x.mas[i] << std::endl;
			}
			break;
		}
		case 2: {
			matrix<double> A(n, n);
			vector <double>b(n);
			vector<double>x(n);
			solver<double>solv;
			std::cout << "Введите матрицу А по одному числу" << std::endl;
			for (int i = 0; i < n * n; i++) {
				std::cin >> A.mas[i];
			}
			std::cout << "Введите матрицу b по одному числу" << std::endl;
			for (int i = 0; i < n; i++) {
				std::cin >> b.mas[i];
			}
			solv.JG(A, b, x);
			std::cout << "Ответ: " << std::endl;
			for (int i = 0; i < n; i++) {
				std::cout << x.mas[i] << std::endl;
			}
			break;
		
		}
		}

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
}

