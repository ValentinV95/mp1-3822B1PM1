#include <iostream>
template <typename T>
class Vector
{
private:
	T* mas; //массив
	size_t size; //размер массива
public:
	Vector(size_t size = 10) //конструктор по умолчанию
	{
		mas = new T[size];
		this->size = size;
	}
	T& operator[](size_t i)
	{
		return mas[i];
	}
	Vector(const Vector& v) //конструктор копирования
	{
		size = v.size;
		mas = new T[size];
		for (int i = 0; i < size; ++i)
		{
			mas[i] = v.mas[i];
		}
	}
	~Vector() // деструктор
	{
		delete[] mas;
		size = 0;
	}
	void swap(int string1, int string2)
	{
		T temp;
		temp = mas[string1];
		mas[string1] = mas[string2];
		mas[string2] = temp;
	}
	void Print() const
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << mas[i] << " " << std::endl;
		}
	}
};
template <typename T>
class Matrix
{
private:
	T** mat; //матрица
	size_t m; //строки
	size_t n; //столбцы
public:
	Matrix() // конструктор по умолчанию
	{
		m = 0;
		n = 0;
		mat = nullptr;
	}
	Matrix(size_t m, size_t n) // конструктор по умолчанию
	{
		this->m = m;
		this->n = n;
		mat = (T**)new T * [m];
		for (int i = 0; i < m; i++)
		{
			mat[i] = (T*)new T[n];
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mat[i][j] = 0;
			}
		}
	}
	Matrix(const Matrix& a)// конструктор копирования
	{
		m = a.m;
		n = a.n;
		mat = (T**)new T * [m];
		for (int i = 0; i < m; i++)
		{
			mat[i] = (T*)new T[n];
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mat[i][j] = a.mat[i][j];
			}
		}
	}
	~Matrix() // деструктор
	{
		delete[] mat;
		m = 0;
		n = 0;
	}
	T* operator[](size_t i)
	{
		return mat[i];
	}
	void swap(int string1, int string2)
	{
		Matrix<T> matswap(m, n);
		for (int i = 0; i < n; i++)
		{
			matswap.GetValue(string1, i) = mat[string1][i];
			matswap.GetValue(string2, i) = mat[string2][i];
		}
		for (int i = 0; i < n; i++)
		{
			mat[string2][i] = matswap.GetValue(string1, i);
			mat[string1][i] = matswap.GetValue(string2, i);
		}
	}
	T& GetValue(int i, int j) const
	{
		return mat[i][j];
	}
	void Print() const
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << mat[i][j] << " "; 
			}
			std::cout << " " << std::endl;
		}
	}
};
template <typename T>
class Solver
{
private:
	Matrix<T> A;
	Vector<T> b;
	size_t n;
public:
	void GausSol(Matrix<T> A, Vector<T> b, size_t n)
	{
		for (int j = 0; j < n; j++)
		{
			int imax = j;
			T max = A[j][j];
			for (int i = j; i < n; i++) //поиск максимального элемента
			{
				if ((std::abs(max) < std::abs(A[i][j])))
				{
					max = A[i][j];
					imax = i;
				}
			}
			if (max != 0)
			{
				T mmax = max;
				A.swap(j, imax); //меняем строки местами
				b.swap(j, imax);
				for (int k = 0; k < n; k++) //делим строку на максимальный элемент
				{
					A[j][k] = A[j][k] / mmax;
				}
				b[j] = b[j] / mmax; 
				for (int c = 0; c < n; c++)
				{
					T del = A[c][j]; // делитель
					if (c == j)
					{
						continue;
					}
					else
					{
						for (int s = j; s < n; s++)
						{
							A[c][s] = A[c][s] - A[j][s] * del;
						}
						b[c] = b[c] - b[j] * del;
					}
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (std::abs(b[i]) < std::pow(10, -7))
			{
				b[i] = 0;
			}
		}
		std::cout << "Ответ: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			if (b[i] == 0)
			{
				std::cout << "Матрица вырожденная" << std::endl;
				break;
			}
			std::cout << "x" << i + 1 << " = " << b[i] << std::endl;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	int td;
	
	std::cout << "Введите размер матрицы А: " << std::endl;
	std::cin >> n;
	std::cout << "Выберите тип данных: 1. float 2. double " << std::endl;
	std::cin >> td;
	
	if (td == 1)
	{
		Matrix<float> A(n, n);
		Vector<float> b(n);
		Solver<float> solvf;
		std::cout << "Введите матрицу А: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cin >> A[i][j];
			}
		}
		std::cout << "Введите вектор b: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cin >> b[i];
		}
		std::cout << "Ваши значения: " << std::endl;
		A.Print();
		b.Print();
		solvf.GausSol(A, b, n);
	}
	if (td == 2)
	{
		Matrix<double> A(n, n);
		Vector<double> b(n);
		Solver<double> solvf;
		std::cout << "Введите матрицу А: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cin >> A[i][j];
			}
		}
		std::cout << "Введите вектор b: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cin >> b[i];
		}
		std::cout << "Ваши значения: " << std::endl;
		A.Print();
		b.Print();
		solvf.GausSol(A, b, n);
	}

	return 0;
}