#pragma once
template <class T>
class matrix {
public:
	T* mas;
	int m;
	int n;
	matrix(int m_, int n_) {
		m = m_;
		n = n_;
		mas = new T[n * m];
	}
	~matrix() {
		m = 0, n = 0;
		delete mas;
	}
};
template <class T>
class vector {
public:
	T* mas;
	int m;
	vector(int m_) {
		m = m_;
		mas = new T[m];
	}
	~vector() {
		m = 0;
		delete mas;
	}
};