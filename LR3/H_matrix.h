#pragma once
#include <iostream>
#include <cstdlib>
#include <locale>
using namespace std;
template <class U>
class matrix
{
private:
	U** matr;
	U* data;
	size_t line, clmn;
public:
	matrix(size_t line, size_t clmn)
	{
		this->line = line;
		this->clmn = clmn;
		data = new U[line * clmn];
		matr = new U * [line];
		for (size_t i = 0; i < line; i++)
		{
			matr[i] = &data[i * clmn];
		}
		cout << "Введите матрицу по строкам: ";
		for (size_t i = 0; i < line; i++)
		{
			for (size_t j = 0; j < clmn; j++)
			{
				cin >> matr[i][j];
			}
		}
	}
	void out()
	{
		cout << "Матрица:" << endl;
		for (size_t i = 0; i < line; i++)
		{
			for (size_t j = 0; j < clmn; j++)
			{
				cout << matr[i][j] << ' ';
			}
			cout << endl;
		}
	}
	size_t getline()
	{
		return line;
	}
	size_t getclmn()
	{
		return clmn;
	}
	U** getmatr()
	{
		return matr;
	}
	~matrix()
	{
		delete data;
		data = 0;
		delete matr;
		matr = 0;
		line = 0;
		clmn = 0;
	}
};