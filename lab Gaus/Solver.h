#pragma once
#include "Matrix.h"
#include "Vector.h"

template <class T>
class Solver {
public:
	void Gaus(Matrix<T>& A, Vector<T>& b, Vector<T>& x) {
		double eps = 10e-7;
		if (sizeof(T) == 8) {
			eps = 10e-16;
		}
		for (int i = 0; i < A.GetM(); i++) {
			T largest_el = A.GetValue(i, i);
			int m_largest = i;
			for (int j = i; j < A.GetN(); j++) {
				if (std::abs(A.GetValue(j, i)) > std::abs(largest_el)) {
					largest_el = A.GetValue(j, i);
					m_largest = j;
				}
			}
			if (std::abs(largest_el) < eps) {
				if (b.GetValue(m_largest) < eps) {
					b.SetValue(m_largest, 0);
				}
				A.SetValue(m_largest, i, 0);
				continue;
			}
			if (largest_el != 0) {
				T divider = largest_el;
				b.Swap(i, m_largest);
				A.Swap(i, m_largest);

				for (int j = 0; j < A.GetN(); j++) {
					A.SetValue(i, j, A.GetValue(i, j) / divider);
				}
				b.SetValue(i, b.GetValue(i) / divider);
			}
			
			for (int j = 0; j < A.GetM(); j++) {
				T mult = A.GetValue(j, i);//mnozhitel
				if (j == i) {
					continue;
				}
				else {
					for (int k = i; k < A.GetN(); k++) {
						A.SetValue(j, k, A.GetValue(j, k) - A.GetValue(i, k) * mult);
					}
					b.SetValue(j, b.GetValue(j) - b.GetValue(i) * mult);
				}
			}
		}

		for (int i = 0; i < b.GetSize(); i++) {
			x[i] = b[i];
		}

		for (int i = 0; i < A.GetM(); i++) {
			if ((A.GetValue(i, i) == 0) && (x.GetValue(i)==0)) {
				throw std::exception("СЛОУ имеет бесконечно много решений");
			}
		}
		for (int i = 0; i < A.GetM(); i++) {
			if (A.GetValue(i, i) == 0) {
				throw std::exception("СЛОУ не имеет решений");
			}
		}
	}
};
