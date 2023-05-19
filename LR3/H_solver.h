#pragma once
#include <iostream>
#include <cstdlib>
#include <locale>
#include <cmath>
using namespace std;
template <typename V>
class solver : protected matrix <V>, protected vec <V>
{
private:
	size_t line, ref_line, clmn, done = 0, m, n, j;
	int flag_zero_lines = 0, f_num = 0;
	V** matr;
	V* vector, * vec_X;
	V ref_el, factor;
public:
	solver(size_t line, size_t clmn) : matrix <V>(line, clmn), vec <V>(line, clmn)
	{
		this->line = matrix <V>::getline();
		this->clmn = matrix <V>::getclmn();
		matr = matrix <V>::getmatr();
		vector = vec <V>::getvec();
		vec_X = vec <V>::getvec_X();
	}
	void solution()
	{
		for (j = 0; done < line; j++)
		{
			ref_line = search_ref_line();
			ref_el = matr[ref_line][j];
			if (vec<V>::zero(ref_el))
				continue;
			swp_max_line();
			equal_1();
			minus_ref_line(0,done);
			minus_ref_line((done+1), line);
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
							swp_zero_line();
						}
					}
					m--;
				}
			}
			done++;
		}
	}
	void minus_ref_line(size_t m, size_t fin)
	{
		for (; m < fin; m++)
		{
			factor = (-1) * matr[m][j];
			for (n = j; n < clmn; n++)
			{
				matr[m][n] += matr[done][n] * factor;
			}
			vector[m] += vector[done] * factor;
		}
	}
	void swp_max_line()
	{
		swap(matr[done], matr[ref_line]);
		swap(vector[done], vector[ref_line]);
	}
	void swp_zero_line()
	{
		swap(matr[n], matr[n + 1]);
		swap(vector[n], vector[n + 1]);
	}
	void equal_1()
	{
		for (n = j; n < clmn; n++)
		{
			matr[done][n] /= ref_el;
		}
		vector[done] /= ref_el;
	}
	size_t search_ref_line()
	{
		size_t ref_line = done;
		size_t i;
		ref_line = done;		//поиск наибольшего
		for (i = done + 1; i < line; i++)
		{
			if (abs(matr[i][j]) > abs(matr[ref_line][j]))
				ref_line = i;
		}
		return ref_line;
	}
	void form_answer()
	{
		size_t i = 0;
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
		line = 0; ref_line = 0; clmn = 0; done = 0;
		matr = 0;
		vector = 0; vec_X = 0;
	}
};
