#pragma once
#include <iostream>
#include <cstdlib>
#include <locale>
using namespace std;
template <class T>
class vec
{
private:
	T* vector, * vec_X;
	size_t len, clmn, i;
public:
	vec(size_t line, size_t clmn)
	{
		len = line;
		this->clmn = clmn;
		vector = new T[len];
		vec_X = new T[clmn];
		cout << "Введите вектор по компонентам: ";
		for (size_t i = 0; i < len; i++)
		{
			cin >> vector[i];
		}
	}
	bool zero(T num)
	{
		return (num == 0);
	}
	void out()
	{
		cout << "Вектор значений:" << endl;
		for (i = 0; i < len; i++)
		{
			if (!zero(vector[i]))
				cout << vector[i] << endl;
			else cout << '0' << endl;
		}
		cout << endl;
	}
	void out_X(int flag_zero_lines)
	{
		if (flag_zero_lines)
			cout << "Система вырожденная, будет выведено одно из решений:\n";
		cout << "Вектор Х:" << endl;
		for (i = 0; i < clmn; i++)
		{
			if (!zero(vec_X[i]))
				cout << vec_X[i] << endl;
			else cout << '0' << endl;
		}
	}
	T* getvec()
	{
		return vector;
	}
	T* getvec_X()
	{
		return vec_X;
	}
	~vec()
	{
		delete vector;
		vector = 0;
		delete vec_X;
		vec_X = 0;
		len = 0;
		clmn = 0;
		i = 0;
	}
};
template<>
bool vec <double>::zero(double d)
{
	return abs(d) < 1e-14;
}
template<>
bool vec <float>::zero(float f)
{
	return abs(f) < 1e-5;
}