#include <iostream>
#include <cstdlib>
#include <locale>
#include <cmath>
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
		delete[]vector;
		vector = 0;
		delete[]vec_X;
		vec_X = 0;
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
		delete[]data;
		data = 0;
		delete[]matr;
		matr = 0;
	}
};
template <typename V>
class solver: protected matrix <V>, protected vec <V>
{
private:
	size_t line, line_et, ref_line, clmn, done = 0, m, n, i, j;
	int flag_zero_lines = 0, f_num=0;
	V** matr;
	V* vector, * vec_X;
	V ref_el, factor;
public:
	solver(size_t line, size_t clmn) : matrix <V> (line, clmn), vec <V> (line, clmn)
	{
		this->line = matrix <V>::getline();
		line_et = line;
		this->clmn = matrix <V>::getclmn();
		matr = matrix <V>::getmatr();
		vector = vec <V>::getvec();
		vec_X = vec <V>::getvec_X();
	}
	void solution()
	{
		for (j = 0; done < line; j++)
		{
			ref_line = done;		//поиск наибольшего
			for (i = done + 1; i < line; i++)
			{
				if (abs(matr[i][j]) > abs(matr[ref_line][j]))
					ref_line = i;
			}
			ref_el = matr[ref_line][j];
			if (vec<V>::zero(ref_el))
				continue;
			swap(matr[done], matr[ref_line]);
			swap(vector[done], vector[ref_line]);
			for (n = j; n < clmn; n++)
			{
				matr[done][n] /= ref_el;
			}
			vector[done] /= ref_el;
			for (m = 0; m < done; m++)
			{
				factor = (-1) * matr[m][j];
				for (n = j; n < clmn; n++)
				{
					matr[m][n] += matr[done][n] * factor;
				}
				vector[m] += vector[done] * factor;
			}
			for (m = done+1; m < line; m++)
			{
				factor = (-1) * matr[m][j];
				for (n = j; n < clmn; n++)
				{
					matr[m][n] += matr[done][n] * factor;
				}
				vector[m] += vector[done] * factor;
			}
			for (m = done + 1; m < line; m++)
			{
				for (n = j; n < clmn; n++)
				{
					if (!vec<V>::zero(matr[m][n]))
					{
						break;
					}
				}
				if (n == clmn) //a zero line found
				{
					line--;
					flag_zero_lines = 1;
					if (!vec<V>::zero(vector[m]))
						throw "Система несовместна\n";
					else
					{
						for (n = m; n < line; n++)
						{
							swap(matr[n], matr[n + 1]);
							swap(vector[n], vector[n + 1]);
						}
					}
					m--;
				}
			}
			done++;
		}
	}
	void form_answer()
	{
		i = 0;
		j = 0;
		while (j < clmn)
		{
			f_num = 0;
			while (j < clmn && (f_num != 1 || !vec<V>::zero(matr[i][j])))
			{
				if (vec<V>::zero(matr[i][j]) || f_num == 1)
				{
					vec_X[j] = 0;
					j++;
				}
				else
				{
					vec_X[j] = vector[i];
					j++;
					f_num = 1;
				}
			}
			i++;
		}
	}
	void out()
	{
		//matrix <V> ::out();
		//vec <V> ::out();
		vec <V> ::out_X(flag_zero_lines);
	}
	~solver()
	{
		vec_X = 0;
		vector = 0;
	}
};
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