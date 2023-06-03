#pragma once

template <typename T>
class Matrix
{
private:
	T** mat; //матрица
	size_t m; //строки
	size_t n; //столбцы
public:
	Matrix() { // конструктор по умолчанию
		m = 0;
		n = 0;
		mat = nullptr;
	}
	Matrix(size_t m, size_t n) { // конструктор по умолчанию
		this->m = m;
		this->n = n;
		mat = new T * [m];
		for (int i = 0; i < m; i++) {
			mat[i] = new T[n];
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = 0;
			}
		}
	}
	Matrix(const Matrix& a) {// конструктор копировани€
		m = a.m;
		n = a.n;
		mat = new T * [m];
		for (int i = 0; i < m; i++) {
			mat[i] = new T[n];
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = a.mat[i][j];
			}
		}
	}
	~Matrix() {// диструктор
		for (int i = 0; i < n; i++) {
			delete(mat[i]);
		}
		delete(mat);
		m = 0;
		n = 0;
	}

	void Swap(int m1, int m2) {
		Matrix mat1(m, n);
		for (int i = 0; i < n; i++) {
			mat1.GetValue(m1, i) = mat[m1][i];
			mat1.GetValue(m2, i) = mat[m2][i];
		}
		for (int i = 0; i < n; i++) {
			mat[m1][i] = mat1.GetValue(m2, i);
			mat[m2][i] = mat1.GetValue(m1, i);
		}

	}

	void Scan() {
		T a;
		//std::cout << "¬вод матрицы" << std::endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cin >> a;
				mat[i][j] = a;
			}
		}
	}

	void Print()
	{
		for (int i = 0; i < m; i++)
		{
			std::cout << "( ";
			for (int j = 0; j < n; j++)
			{
				std::cout << mat[i][j] << " ";
			}
			std::cout << ")" << std::endl;
		}
	}

	T* operator[](size_t i)
	{
		return mat[i];
	}

	/*T& operator()(int ind1, int ind2) {
        return arr[ind1][ind2];
    }*/

	T& GetValue(int i, int j) { return mat[i][j]; }
	void SetValue(int i, int j, T value) { mat[i][j] = value; }
	size_t GetM() { return m; }
	size_t GetN() { return n; }
};
