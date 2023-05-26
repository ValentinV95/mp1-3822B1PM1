#pragma once
template <class V>
void swap(matrix<V>& A, vector<V>& b, int i, int j) {
	matrix<V> si(A.m, 1), sj(A.m, 1);
	float temb = b.mas[i];
	b.mas[i] = b.mas[j];
	b.mas[j] = temb;
	for (int k = 0; k < A.n; k++) {
		si.mas[k] = A.mas[i * A.n + k];
		sj.mas[k] = A.mas[j * A.n + k];
	}

	for (int k = 0; k < A.n; k++) {
		A.mas[i * A.n + k] = sj.mas[k];
		A.mas[j * A.n + k] = si.mas[k];
	}
}
template <class U>
class solver {
public:
	void JG(matrix<U>& A, vector<U>& b, vector<U>& x) { 
		for (int i = 0; i < A.m; i++) {
			U maxel = A.mas[i * A.n + i];
			int maxs = i;
			for (int j = 0; j < A.n - i; j++) {
				if (abs(A.mas[A.n * (i + j) + i]) > maxel) {
					maxel = A.mas[A.n * (i + j) + i];
					maxs = i + j;
				}

			}
			if (maxel == 0) {
				if (b.mas[i] == 0) {
					continue;
				}
				else {
					throw std::logic_error("Ðåøåíèé íå ñóøåñòâóåò");
				}

			}



			if (maxel != 0) {
				swap(A, b, i, maxs);
				U del = A.mas[i * A.n + i];
				for (int j = 0; j < A.n; j++) {
					A.mas[i * A.n + j] /= del;
				}
				b.mas[i] /= del;

				int k = 1;
				while ((i - k) >= 0) { 
					U mul = A.mas[A.n * (i - k) + i];
					for (int j = i; j < A.n; j++) {
						A.mas[A.n * (i - k) + j] -= mul * A.mas[i * A.n + j];
					}
					b.mas[i - k] -= b.mas[i] * mul;
					k++;
				}
				k = 1;
				while (i + k < A.m) { 
					U mul = A.mas[A.n * (i + k) + i];
					for (int j = i; j < A.n; j++) {
						A.mas[A.n * (i + k) + j] -= mul * A.mas[i * A.n + j];
					}
					b.mas[i + k] -= b.mas[i] * mul;
					k++;
				}


			}
		}
		for (int l = 0; l < A.n; l++) {
			x.mas[l] = b.mas[l];
		}
	}
};
