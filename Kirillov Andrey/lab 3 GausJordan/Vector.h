#pragma once

template <class T>
class Vector {
private:
	T* array;
	size_t size;
public:
	Vector(size_t size = 10) {//конструктор создани€
		this->size = size;
		array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = 0;
		}
	}
	Vector(const Vector& v) { //конструктор копирровани€
		size = v.GetSize();
		array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = v.GetValue(i);
		}
	}
	~Vector() {//диструкор
		delete(array);
		size = 0;
	}
	T& operator[](size_t size) {
		return array[size];
	}

	Vector& operator=(const Vector& v) {
		if (this->array != nullptr) {
			delete(array);
		}
		this->size = v.GetSize();
		array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = v.GetValue(i);
		}
		return (*this);
	}

	void Swap(int m1, int m2) {
		T tmp;
		tmp = array[m1];
		array[m1] = array[m2];
		array[m2] = tmp;
	}

	void Print() {
		for (int i = 0; i < size; i++) {
			std::cout << "( " << array[i] << " )" << std::endl;
		}
	}

	void Scan() {
		T a;
		//std::cout << "¬вод матрицы" << std::endl;
		for (int i = 0; i < size; i++) {
			std::cin >> a;
			array[i] = a;
		}
	}

	void SetValue(int i, T value) { array[i] = value; };
	T GetValue(int i) const { return array[i]; };
	size_t GetSize() const { return size; };
	size_t GetSize() { return size; };
	size_t SetSize(size_t size) { this->size = size; };

};
