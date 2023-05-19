#include <iostream>
#include <cstdlib>
#include <locale>
#include <cmath>
#include "H_vec.h"
#include "H_matrix.h"
#include "H_solver.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	size_t line,clmn;
	int action;
	cout << "Введите размер матрицы:\nСтрок:";
	cin >> line;
	cout << "Столбцов:";
	cin >> clmn;
	cout << "Выберите тип данных:\n1)Float\n2)Double\n";
	cin >> action;
	switch (action)
	{
	case 1:
	{
		try {
			solver <float> s(line, clmn);
			s.solution();
			s.form_answer();
			s.out();
		}
		catch (const char*)
		{
			cout << "Система несовместна!";
		}
		break;
	}
	case 2:
	{
		try {
			solver <double> s(line, clmn);
			s.solution();
			s.form_answer();
			s.out();
		}
		catch (const char*)
		{
			cout << "Система несовместна!";
		}
		break;
	}
	}
	return 0;
}